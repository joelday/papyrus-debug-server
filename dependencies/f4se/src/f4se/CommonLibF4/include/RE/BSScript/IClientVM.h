#pragma once

#include "f4se/GameRTTI.h"  // RTTI_BSScript__IClientVM


namespace RE
{
	namespace BSScript
	{
		class IClientVM
		{
		public:
			inline static const void* RTTI = RTTI_BSScript__IClientVM;
			
			virtual void	Unk_01(void) = 0;
			virtual void	Unk_02(void) = 0;
		};
	}
}