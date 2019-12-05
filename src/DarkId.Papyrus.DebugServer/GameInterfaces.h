#pragma once

#if SKYRIM
#include "skse64/GameTypes.h"
#include "RE/Skyrim.h"

namespace RE
{
	namespace BSScript
	{
		typedef Class ObjectTypeInfo;
	}
}

#elif FALLOUT
#include "f4se/GameTypes.h"
#include "RE/Fallout.h"
#endif