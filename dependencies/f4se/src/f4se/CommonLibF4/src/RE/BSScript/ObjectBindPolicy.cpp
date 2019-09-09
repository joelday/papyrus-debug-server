#include "RE/BSScript/ObjectBindPolicy.h"

#include "f4se/PapyrusInterfaces.h"  // ObjectBindPolicy


namespace RE
{
	namespace BSScript
	{
		void ObjectBindPolicy::BindObject(BSTSmartPointer<Object>& a_objectPtr, VMHandle a_handle)
		{
			using func_t = function_type_t<decltype(&ObjectBindPolicy::BindObject)>;
			func_t* func = EXTRACT_F4SE_MEMBER_FN_ADDR(::IObjectBindPolicy, BindObject, func_t*);
			return func(this, a_objectPtr, a_handle);
		}
	}
}
