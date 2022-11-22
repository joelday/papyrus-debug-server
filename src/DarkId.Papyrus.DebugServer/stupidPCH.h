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
#include <common/IPrefix.h>
#endif