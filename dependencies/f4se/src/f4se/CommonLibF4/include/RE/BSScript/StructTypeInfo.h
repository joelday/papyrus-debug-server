#pragma once

#include "f4se/GameRTTI.h"  // RTTI_BSScript__StructTypeInfo
#include "RE/BSScript/IComplexType.h"
#include "RE/BSTSmartPointer.h"
#include "RE/BSScript/IFunction.h"
#include "RE/BSScript/Variable.h"
#include "RE/BSTHashMap.h"
#include "RE/BSTArray.h"

namespace RE
{
	namespace BSScript
	{
		class StructTypeInfo : public IComplexType
		{
		public:
			inline static const void* RTTI = RTTI_BSScript__StructTypeInfo;

			const char* StructTypeInfo::GetName() const;
			
			struct StructData
			{
				UInt64	unk00;		// 00
				UInt64	unk08;		// 08
				UInt64	type;		// 10
				void*	unk18;		// 18
				UInt64	unk20;		// 20
			};

			BSFixedString name;							// 10
			ObjectTypeInfo* parent;						// 18
			BSTArray<StructData> data;					// 20
			BSTHashMap<BSFixedString, UInt32> members;
		};

		STATIC_ASSERT(offsetof(StructTypeInfo, name) == 0x10);
		STATIC_ASSERT(offsetof(StructTypeInfo, data) == 0x20);
		
	}
}
