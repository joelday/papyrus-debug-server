#pragma once

#include "RE/BSFixedString.h"  // BSFixedString
#include "RE/BSTSmartPointer.h"  // BSTSmartPointer
#include "RE/BSIntrusiveRefCounted.h"  // BSIntrusiveRefCounted

namespace RE
{

	namespace BSScript
	{
		class StructTypeInfo;
		class Variable;
		
		// first 2 bits on this ptr used as flags
		class Struct : public BSIntrusiveRefCounted
		{
		public:
			StructTypeInfo*			GetTypeInfo();
			const StructTypeInfo*	GetTypeInfo() const;

			UInt32					GetNumProperties() const;
			Variable*				GetPropertyIter();
			const Variable*			GetPropertyIter() const;
			
			~Struct();
			
			UInt32				unk04;					// 04
			UInt64				unk08;					// 08
			BSTSmartPointer<StructTypeInfo> typeInfo;	// 10
			UInt8				unk18;					// 18 - set to 1 if unk19 is 1 (3EFCF27952D674A8FA959AABC29A0FE3E726FA91)
			UInt8				unk19;					// 19 - set to 1 when type+0x68 == 3
			UInt16				unk1A;					// 1A
			UInt32				unk1C;					// 1C
			char				variable[0];			// 20
			
		private:
			void dtor() const;
		};
		STATIC_ASSERT(sizeof(Struct) == 0x20);
	}
}
