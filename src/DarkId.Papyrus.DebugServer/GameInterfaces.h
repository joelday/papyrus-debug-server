#pragma once

#if SKYRIM
#include "RE/Skyrim.h"

namespace RE
{
	namespace BSScript
	{
		typedef Class ObjectTypeInfo;
	}
}

#elif FALLOUT
#include "RE/Fallout.h"
#endif