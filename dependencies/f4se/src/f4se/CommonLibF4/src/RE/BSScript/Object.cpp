#include "RE/BSScript/Object.h"

#include "RE/BSScript/Internal/VirtualMachine.h"  // BSScript::Internal::VirtualMachine
#include "RE/BSScript/IComplexType.h"  // BSScript::IComplexType
#include "RE/BSScript/IObjectHandlePolicy.h"  // BSScript::IObjectHandlePolicy

namespace RE
{
	namespace BSScript
	{
		ObjectTypeInfo* Object::GetClass()
		{
			return classPtr.get();
		}


		const ObjectTypeInfo* Object::GetClass() const
		{
			return classPtr.get();
		}


		UInt32 Object::GetFlags() const
		{
			return pun_bits(flags1, flags2, flags3);
		}


		UInt32 Object::GetNumProperties() const
		{
			return pun_bits(numProperties01, numProperties02, numProperties03, numProperties04, numProperties05, numProperties06, numProperties07, numProperties08, numProperties09, numProperties10, numProperties11, numProperties12, numProperties13, numProperties14, numProperties15, numProperties16, numProperties17, numProperties18, numProperties19);
		}


		void* Object::Resolve(FormType32 a_typeID) const
		{
			auto vm = Internal::VirtualMachine::GetSingleton();
			auto policy = vm->GetHandlePolicy();
			if (policy->IsType(a_typeID, handle) && policy->IsValidHandle(handle)) {
				return policy->Resolve(a_typeID, handle);
			} else {
				return 0;
			}
		}


		void Object::IncRefCount()
		{
			reinterpret_cast<VMIdentifier*>(this)->IncrementLock();
		}


		SInt32 Object::DecRefCount()
		{
			return reinterpret_cast<VMIdentifier*>(this)->DecrementLock();
		}


		Variable* Object::GetProperty(const BSFixedString& a_name)
		{
			if (!classPtr) {
				return 0;
			}
			
			auto idx = classPtr->GetPropertyIndex(a_name);
			if (idx == static_cast<UInt32>(-1)) {
				return 0;
			}

			return &variables[idx];
		}


		const Variable*	Object::GetProperty(const BSFixedString& a_name) const
		{
			if (!classPtr) {
				return 0;
			}
			
			auto idx = classPtr->GetPropertyIndex(a_name);
			if (idx == static_cast<UInt32>(-1)) {
				return 0;
			}

			return &variables[idx];
		}
	}
}
