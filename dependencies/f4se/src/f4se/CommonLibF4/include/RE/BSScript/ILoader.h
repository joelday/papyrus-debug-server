#pragma once

#include "f4se/GameRTTI.h"  // RTTI_BSScript__ILoader


namespace RE
{
	namespace BSScript
	{
		struct ILoader
		{
		public:
			inline static const void* RTTI = RTTI_BSScript__ILoader;


			virtual ~ILoader();					// 00

			// add
			virtual void	Unk_01(void) = 0;	// 01
			virtual void	Unk_02(void) = 0;	// 02
		};
		STATIC_ASSERT(sizeof(ILoader) == 0x8);
	}
}
