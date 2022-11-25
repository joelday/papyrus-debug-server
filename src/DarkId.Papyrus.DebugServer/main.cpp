#if SKYRIM
#include <SKSE/Version.h>
#include <SKSE/Trampoline.h>
#include <SKSE/API.h>
#include <SKSE/Logger.h>
#include <ShlObj.h>
#include <string_view>
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

DebugServer* g_debugServer;
using namespace std::literals;

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
			logger::info("Listening for connections from adapter messaging proxy...");

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
		auto path = logger::log_directory();
		if (!path) {
			//stl::report_and_fail("Failed to find standard logging directory"sv); // Doesn't work in VR
		}
		*path += "DarkId.Papyrus.DebugServer.log"sv;
		auto sink = std::make_shared<spdlog::sinks::basic_file_sink_mt>(path->string(), true);

		auto log = std::make_shared<spdlog::logger>("global log"s, std::move(sink));
		log->set_level(spdlog::level::debug);
		log->flush_on(spdlog::level::debug);

		logger::info("Papyrus Debug Server v{}"sv, DIDPDS_VERSION_VERSTRING);

		a_info->infoVersion = 1;

		a_info->name = "Papyrus Debug Server";
		a_info->version = DIDPDS_VERSION_MAJOR;

		if (a_xse->IsEditor()) {
			logger::critical("Loaded in editor, marking as incompatible!\n");
			return false;
		}
		auto result = a_xse->RuntimeVersion().compare(SKSE::RUNTIME_SSE_LATEST);
		if (result == std::strong_ordering::greater){
			logger::critical("Unsupported runtime version {}!\n"sv, a_xse->RuntimeVersion().string());
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
		logger::info("Papyrus Debug Server loaded");

//#if _DEBUG
//		logger::info("Waiting for debugger to attach");
// 
//		while (!IsDebuggerPresent())
//		{
//			Sleep(10);
//		}
// 
//		Sleep(1000 * 2);
//#endif
	//SKSE::GetTrampoline().
	
		// if (!g_branchTrampoline.Create(1024 * 64))
		// {
		// 	logger::error("Couldn't create branch trampoline. This is fatal. Skipping remainder of init process.");
		// 	return false;
		// }

		// if (!g_localTrampoline.Create(1024 * 64, nullptr))
		// {
		// 	logger::error("Couldn't create codegen buffer. This is fatal. Skipping remainder of init process.");
		// 	return false;
		// }

		g_debugServer = new DebugServer();
		Init(a_xse);

#if SKYRIM
		XSE::GetMessagingInterface()->RegisterListener("SKSE", MessageHandler);
#elif FALLOUT
		XSE::GetMessagingInterface()->RegisterListener("F4SE", MessageHandler);
#endif 

		return true;
	}
};
