#include "RE/BSScript/Struct.h"

#include "RE/BSScript/Internal/VirtualMachine.h"  // BSScript::Internal::VirtualMachine
#include "RE/BSScript/IComplexType.h"  // BSScript::IComplexType
#include "RE/BSScript/IObjectHandlePolicy.h"  // BSScript::IObjectHandlePolicy
#include "RE/Offset.h"
#include "REL/Relocation.h"


namespace RE
{
	namespace BSScript
	{
		StructTypeInfo* Struct::GetTypeInfo()
		{
			return typeInfo.get();
		}

		const StructTypeInfo* Struct::GetTypeInfo() const
		{
			return typeInfo.get();
		}

		UInt32 Struct::GetNumProperties() const
		{
			return typeInfo->members.size();
		}

		Variable* Struct::GetPropertyIter()
		{
			return reinterpret_cast<Variable*>(&variable[0]);
		}

		const Variable* Struct::GetPropertyIter() const
		{
			return reinterpret_cast<const Variable*>(&variable[0]);
		}

		Struct::~Struct()
		{
			dtor();
		}
		
		void Struct::dtor() const
		{
			using func_t = function_type_t<decltype(&Struct::dtor)>;
			REL::Offset<func_t*> func(Offset::BSScript::Struct::Dtor);
			return func(this);
		}
	}
}
