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
#include "f4se/GameForms.h"

#endif