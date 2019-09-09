#include "RE/BSScript/StructTypeInfo.h"

#include "f4se/PapyrusVM.h"  // VMObjectTypeInfo


namespace RE
{
	namespace BSScript
	{
		const char* StructTypeInfo::GetName() const
		{
			return name.c_str();
		}
	}
}
