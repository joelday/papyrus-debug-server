#include "f4se/PluginAPI.h"
#include "f4se_common/BranchTrampoline.h"
#include "f4se_common/f4se_version.h"

#include <shlobj.h>

#include "DebugServer.h"
#include "RuntimeEvents.h"

using namespace DarkId::Papyrus::DebugServer;

const char* g_pluginName = "DarkId.Papyrus.DebugServer";

UInt32 g_version = 1;
PluginHandle g_pluginHandle = kPluginHandle_Invalid;

const F4SEInterface* g_f4se;
F4SEMessagingInterface* g_messaging;
F4SETaskInterface* g_tasks;

DebugServer* g_debugServer;

void F4SEMessageHandler(F4SEMessagingInterface::Message* msg)
{
    switch (msg->type)
    {
        case F4SEMessagingInterface::kMessage_GameLoaded:
        {
            RuntimeEvents::Internal::CommitHooks();

            g_debugServer->Listen();
            _MESSAGE("Listening for connections from adapter messaging proxy...");

            break;
        }
    }
}

extern "C"
{
    bool F4SEPlugin_Query(const F4SEInterface* f4se, PluginInfo* info)
    {
        _MESSAGE("Registering debug server plugin...");

        gLog.OpenRelative(CSIDL_MYDOCUMENTS, ("\\My Games\\Fallout4\\F4SE\\" + std::string(g_pluginName) + ".log").c_str());

        // populate info structure
        info->infoVersion = PluginInfo::kInfoVersion;
        info->name = g_pluginName;
        info->version = g_version;

        // store plugin handle so we can identify ourselves later
        g_pluginHandle = f4se->GetPluginHandle();

        // Check game version
        if (f4se->runtimeVersion != CURRENT_RELEASE_RUNTIME) {
            char versionMessage[512];
            sprintf_s(versionMessage, sizeof(versionMessage), "Your game version: v%d.%d.%d.%d\nExpected version: v%d.%d.%d.%d\n%s will be disabled.",
                GET_EXE_VERSION_MAJOR(f4se->runtimeVersion),
                GET_EXE_VERSION_MINOR(f4se->runtimeVersion),
                GET_EXE_VERSION_BUILD(f4se->runtimeVersion),
                GET_EXE_VERSION_SUB(f4se->runtimeVersion),
                GET_EXE_VERSION_MAJOR(CURRENT_RELEASE_RUNTIME),
                GET_EXE_VERSION_MINOR(CURRENT_RELEASE_RUNTIME),
                GET_EXE_VERSION_BUILD(CURRENT_RELEASE_RUNTIME),
                GET_EXE_VERSION_SUB(CURRENT_RELEASE_RUNTIME),
                g_pluginName
            );

            MessageBoxA(nullptr, versionMessage, g_pluginName, MB_OK | MB_ICONEXCLAMATION);
            return false;
        } 

        g_messaging = (F4SEMessagingInterface*)f4se->QueryInterface(kInterface_Messaging);
        g_tasks = (F4SETaskInterface*)f4se->QueryInterface(kInterface_Task);

        return true;
    }

    bool F4SEPlugin_Load(const F4SEInterface * f4se)
    {
        _MESSAGE("Initializing debug server...");

        if (!g_branchTrampoline.Create(1024 * 64))
        {
            _ERROR("Couldn't create branch trampoline. This is fatal. Skipping remainder of init process.");
            return false;
        }

        if (!g_localTrampoline.Create(1024 * 64, nullptr))
        {
            _ERROR("Couldn't create codegen buffer. This is fatal. Skipping remainder of init process.");
            return false;
        }

        g_debugServer = new DebugServer(g_tasks);
        g_messaging->RegisterListener(g_pluginHandle, "F4SE", F4SEMessageHandler);

        _MESSAGE("Waiting for GameLoaded event...");

        return true;
    }

};