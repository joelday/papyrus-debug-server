#include "RE/BSScript/Type.h"
#include "RE/BSScript/IComplexType.h"
#include "RE/BSScript/Internal/VirtualMachine.h"

namespace RE
{
	namespace BSScript
	{
		Type::Type() :
			type(VMTypeID::kNone)
		{}

		Type::Type(VMTypeID a_type) :
			type(a_type)
		{}

		Type::Type(const Type& a_rhs) :
			type(a_rhs.type)
		{}

		VMTypeID Type::GetTypeID() const
		{
			return type;
		}

		void Type::SetTypeID(VMTypeID a_type)
		{
			type = a_type;
		}

		VMTypeID Type::GetUnmangledType() const
		{
			if (type < VMTypeID::kArrayEnd)
			{
				return type;
			}
			
			if (IsObject())
			{
				return VMTypeID::kObject;
			}
			
			if (IsObjectArray())
			{
				return VMTypeID::kObjectArray;
			}
			
			if (IsStruct())
			{
				return VMTypeID::kStruct;
			}
			
			if (IsStructArray())
			{
				return VMTypeID::kStructArray;
			}

			return VMTypeID::kNone;
		}

		IComplexType* Type::GetComplexType() const
		{
			return IsComplexType() ? reinterpret_cast<IComplexType*>(type & ~static_cast<VMTypeID>(1)) : 0;
		}

		StructTypeInfo* Type::GetStructType() const
		{
			return IsStructOrStructArray() ? reinterpret_cast<StructTypeInfo*>(GetComplexType()) : 0;
		}

		bool Type::IsComplexType() const
		{
			return type >= VMTypeID::kArrayEnd;
		}

		bool Type::IsStruct() const
		{
			return IsStructOrStructArray() && !IsComplexTypeArray();
		}

		bool Type::IsVariable() const
		{
			return type == VMTypeID::kVariable;
		}

		bool Type::IsComplexTypeArray() const
		{
			return (type >= VMTypeID::kArrayEnd && (type & VMTypeID::kObject) != VMTypeID::kNone);
		}

		bool Type::IsStructArray() const
		{
			return IsStructOrStructArray() && IsComplexTypeArray();
		}

		bool Type::IsVariableArray() const
		{
			return type == VMTypeID::kVariableArray;
		}

		bool Type::IsObjectOrObjectArray() const
		{
			return (IsComplexType() || IsComplexTypeArray()) && !IsStructOrStructArray();
		}

		bool Type::IsStructOrStructArray() const
		{
			const auto typeInfo = reinterpret_cast<StructTypeInfo*>(GetComplexType());
			if (!typeInfo)
			{
				return false;
			}
			
			auto vm = Internal::VirtualMachine::GetSingleton();

			BSTSmartPointer<StructTypeInfo> structTypeInfo;
			return vm->GetStructTypeInfo(typeInfo->GetName(), structTypeInfo);
		}

		ObjectTypeInfo* Type::GetScriptClass() const
		{
			return IsObjectOrObjectArray() ? reinterpret_cast<ObjectTypeInfo*>(GetComplexType()) : 0;
		}

		bool Type::IsInt() const
		{
			return type == VMTypeID::kInt;
		}

		bool Type::IsFloat() const
		{
			return type == VMTypeID::kFloat;
		}

		bool Type::IsString() const
		{
			return type == VMTypeID::kString;
		}

		bool Type::IsBool() const
		{
			return type == VMTypeID::kBool;
		}

		bool Type::IsObject() const
		{
			return IsObjectOrObjectArray() && !IsComplexTypeArray();
		}
		
		bool Type::IsObjectArray() const
		{
			return IsObjectOrObjectArray() && IsComplexTypeArray();
		}

		bool Type::IsLiteralArray() const
		{
			return type > VMTypeID::kObjectArray && type < VMTypeID::kStructArray;
		}

		bool Type::IsArray() const
		{
			return IsLiteralArray() || IsComplexTypeArray();
		}
	}
}
