#pragma once

#include "f4se/GameRTTI.h"  // RTTI_BSScript__ICachedErrorMessage
#include "RE/BSFixedString.h"

namespace RE
{
	namespace BSScript
	{
		class ICachedErrorMessage
		{
		public:

			inline static const void* RTTI = RTTI_BSScript__ICachedErrorMessage;

			virtual ~ICachedErrorMessage();

			virtual void Unk_01(UInt64* unk1);

			UInt64* unk_08;
			BSFixedString text;
		}; 

		STATIC_ASSERT(sizeof(ICachedErrorMessage) == 0x18);
	}
}