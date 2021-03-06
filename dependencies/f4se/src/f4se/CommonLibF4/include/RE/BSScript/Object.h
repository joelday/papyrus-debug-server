#pragma once

#include "RE/BSScript/Variable.h"  // BSScript::Variable
#include "RE/BSFixedString.h"  // BSFixedString
#include "RE/BSTSmartPointer.h"  // BSTSmartPointer
#include "RE/Memory.h"  // TES_HEAP_REDEFINE_NEW

namespace RE
{
	namespace SkyrimScript
	{
		class HandlePolicy;
	}


	namespace BSScript
	{
		class ObjectTypeInfo;


		// first 2 bits on this ptr used as flags
		class Object
		{
		public:
			ObjectTypeInfo*			GetClass();
			const ObjectTypeInfo*	GetClass() const;
			UInt32					GetFlags() const;
			UInt32					GetNumProperties() const;

			void* Resolve(FormType32 a_typeID) const;

			void	IncRefCount();
			SInt32	DecRefCount();

			Variable*		GetProperty(const BSFixedString& a_name);
			const Variable*	GetProperty(const BSFixedString& a_name) const;

			FO_HEAP_REDEFINE_NEW();

			// members
			bool					flags1 : 1;				// 00 - 0
			bool					flags2 : 1;				// 00 - 1
			bool					flags3 : 1;				// 00 - 2
			bool					numProperties01 : 1;	// 00 - 3
			bool					numProperties02 : 1;	// 00 - 4
			bool					numProperties03 : 1;	// 00 - 5
			bool					numProperties04 : 1;	// 00 - 6
			bool					numProperties05 : 1;	// 00 - 7

			bool					numProperties06 : 1;	// 01 - 0
			bool					numProperties07 : 1;	// 01 - 1
			bool					numProperties08 : 1;	// 01 - 2
			bool					numProperties09 : 1;	// 01 - 3
			bool					numProperties10 : 1;	// 01 - 4
			bool					numProperties11 : 1;	// 01 - 5
			bool					numProperties12 : 1;	// 01 - 6
			bool					numProperties13 : 1;	// 01 - 7

			bool					numProperties14 : 1;	// 02 - 0
			bool					numProperties15 : 1;	// 02 - 1
			bool					numProperties16 : 1;	// 02 - 2
			bool					numProperties17 : 1;	// 02 - 3
			bool					numProperties18 : 1;	// 02 - 4
			bool					numProperties19 : 1;	// 02 - 5
			bool					unk02_6 : 1;			// 02 - 6
			bool					unk02_7 : 1;			// 02 - 7

			UInt8					pad03;					// 03
			UInt32					pad04;					// 04
			BSTSmartPointer<ObjectTypeInfo>	classPtr;		// 08
			BSFixedString			currentState;			// 10
			UInt32*					unk0C;					// 18 - some ref count, first bit used as flag
			volatile VMHandle		handle;					// 20
			volatile SInt32			refCount;				// 28
			UInt32					pad2C;					// 2C
			Variable				variables[0];			// 30 - size == classPtr->GetTotalNumVariables()
		};
		STATIC_ASSERT(sizeof(Object) == 0x30);
	}
}
