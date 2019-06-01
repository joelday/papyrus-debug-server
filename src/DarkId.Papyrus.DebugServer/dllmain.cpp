#include "f4se/PluginAPI.h"
#include "f4se_common/f4se_version.h"

#include <string>

#include <shlobj.h>

const char* g_pluginName = "TestPlugin";

UInt32 g_version = 1;

PluginHandle			    g_pluginHandle = kPluginHandle_Invalid;

F4SEPapyrusInterface* g_papyrus = nullptr;

extern "C"
{

    bool F4SEPlugin_Query(const F4SEInterface* f4se, PluginInfo* info)
    {
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

        // get the papyrus interface and query its version
        g_papyrus = (F4SEPapyrusInterface*)f4se->QueryInterface(kInterface_Papyrus);
        if (!g_papyrus)
        {
            _MESSAGE("couldn't get papyrus interface");
            return false;
        }
        else {
            _MESSAGE("got papyrus interface");
        }

        return true;
    }

    bool F4SEPlugin_Load(const F4SEInterface * f4se)
    {
        _MESSAGE("load");

        if (g_papyrus)
        {
            _MESSAGE("Papyrus Register Succeeded");
        }

        return true;
    }

};