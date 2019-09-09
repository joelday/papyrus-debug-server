#pragma once

#include "f4se/GameRTTI.h"  // RTTI_BSScript__IComplexType
#include "RE/BSIntrusiveRefCounted.h"
#include "RE/BSFixedString.h"

namespace RE
{
	namespace BSScript
	{
		class IComplexType : public BSIntrusiveRefCounted
		{
		public:
			inline static const void* RTTI = RTTI_BSScript__IComplexType;

			virtual ~IComplexType() = default;	// 00
			virtual VMTypeID	GetTypeID() const = 0;
		};
	}
}
