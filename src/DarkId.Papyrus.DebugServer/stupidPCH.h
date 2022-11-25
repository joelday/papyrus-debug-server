// fuck everything about this
#pragma once
#if SKYRIM
#include <SKSE/Impl/PCH.h>
#undef GetObject // Have to do this because PCH pulls in spdlog->winbase.h->windows.h->wingdi.h, which redfines GetObject
#undef GetObjectA
#include <RE/Skyrim.h>
#include <SKSE/SKSE.h>
#include <SKSE/API.h>
#include <SKSE/Logger.h>
#include <spdlog/sinks/basic_file_sink.h>

namespace DarkId::Papyrus::DebugServer
{
  using namespace std::literals;
  namespace XSE = SKSE;
  namespace logger = SKSE::log;
}

#elif FALLOUT
#include <F4SE/Impl/PCH.h>
#undef GetObject // Have to do this because PCH pulls in spdlog->winbase.h->windows.h->wingdi.h, which redfines GetObject
#undef GetObjectA
#include <RE/Fallout.h>
namespace DarkId::Papyrus::DebugServer
{
  using namespace std::literals;
  namespace XSE = F4SE;
  namespace logger = F4SE::log;
}
#endif