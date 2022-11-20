#if SKYRIM
#include <skse64_common/skse_version.h>  // RUNTIME_VERSION
#include <skse64_common/BranchTrampoline.h>
#include <SKSE/API.h>
#include <SKSE/Logger.h>

namespace XSE = SKSE;

#elif FALLOUT
#include <f4se_common/f4se_version.h>  // RUNTIME_VERSION
#include <f4se_common/BranchTrampoline.h>
#include <F4SE/Logger.h>
#include <F4SE/API.h>

namespace XSE = F4SE;

#endif

#include "version.h"  // VERSION_VERSTRING, VERSION_MAJOR

#include "DebugServer.h"
#include "RuntimeEvents.h"

using namespace DarkId::Papyrus::DebugServer;
//TODO: Logger completely changed in SKSE/logger.h, Logger class no longer exists, fix it
DebugServer* g_debugServer;

void MessageHandler(XSE::MessagingInterface::Message* msg)
{
	switch (msg->type)
	{
#if SKYRIM
	case SKSE::MessagingInterface::kDataLoaded :
#elif FALLOUT
	case F4SE::MessagingInterface::kGameLoaded :
#endif
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
#if SKYRIM
	bool SKSEPlugin_Query(const XSE::QueryInterface* a_xse, XSE::PluginInfo* a_info)
#elif FALLOUT
	bool F4SEPlugin_Query(const XSE::QueryInterface* a_xse, XSE::PluginInfo* a_info)
#endif
	{
#if SKYRIM
		XSE::Logger::OpenRelative(FOLDERID_Documents, L"\\My Games\\Skyrim Special Edition\\SKSE\\DarkId.Papyrus.DebugServer.log");
		XSE::Logger::UseLogStamp(true);

#elif FALLOUT
		XSE::Logger::OpenRelative(FOLDERID_Documents, L"\\My Games\\Fallout 4\\F4SE\\DarkId.Papyrus.DebugServer.log");
#endif

		XSE::Logger::SetPrintLevel(XSE::Logger::Level::kDebugMessage);
		XSE::Logger::SetFlushLevel(XSE::Logger::Level::kDebugMessage);
		
		_MESSAGE("Papyrus Debug Server v%s", DIDPDS_VERSION_VERSTRING);

		a_info->infoVersion = 1;

		a_info->name = "Papyrus Debug Server";
		a_info->version = DIDPDS_VERSION_MAJOR;

		if (a_xse->IsEditor()) {
			_FATALERROR("Loaded in editor, marking as incompatible!\n");
			return false;
		}
		
		switch (a_xse->RuntimeVersion()) {
		case CURRENT_RELEASE_RUNTIME:
			break;
		default:
			_FATALERROR("Unsupported runtime version %08X!\n", a_xse->RuntimeVersion());
			return false;
		}

		return true;
	}

#if SKYRIM
	bool SKSEPlugin_Load(const XSE::LoadInterface* a_xse)
#elif FALLOUT
	bool F4SEPlugin_Load(const XSE::LoadInterface* a_xse)
#endif
		
	{
		_MESSAGE("Papyrus Debug Server loaded");

//#if _DEBUG
//		_MESSAGE("Waiting for debugger to attach");
// 
//		while (!IsDebuggerPresent())
//		{
//			Sleep(10);
//		}
// 
//		Sleep(1000 * 2);
//#endif

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

		g_debugServer = new DebugServer();

		if (!Init(a_xse))
		{
			return false;
		}

#if SKYRIM
		XSE::GetMessagingInterface()->RegisterListener("SKSE", MessageHandler);
#elif FALLOUT
		XSE::GetMessagingInterface()->RegisterListener("F4SE", MessageHandler);
#endif 

		return true;
	}
};
