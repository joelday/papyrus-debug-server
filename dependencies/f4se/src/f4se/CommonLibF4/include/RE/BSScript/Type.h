#pragma once

namespace RE
{
	namespace BSScript
	{
		class IComplexType;
		class ObjectTypeInfo;
		class StructTypeInfo;
		
		class Type
		{
		public:
			Type();
			explicit Type(VMTypeID a_type);
			explicit Type(const Type& a_rhs);

			VMTypeID		GetTypeID() const;
			void			SetTypeID(VMTypeID a_type);
			VMTypeID		GetUnmangledType() const;
			
			IComplexType*	GetComplexType() const;
			ObjectTypeInfo*	GetClass() const;
			StructTypeInfo* GetStructType() const;
			
			bool			IsComplexType() const;
			bool			IsObject() const;
			bool			IsStruct() const;
			
			
			bool 			IsInt() const;
			bool 			IsFloat() const;
			bool 			IsString() const;
			bool 			IsBool() const;
			bool			IsVariable() const;
			
			bool 			IsComplexTypeArray() const;
			bool 			IsObjectArray() const;
			bool 			IsStructArray() const;
			bool 			IsLiteralArray() const;
			bool 			IsArray() const;
			bool			IsVariableArray() const;

		protected:
			// members
			VMTypeID type;	// 00

			bool			IsObjectOrObjectArray() const;
			bool			IsStructOrStructArray() const;
		};
		STATIC_ASSERT(sizeof(Type) == 0x8);
	}
}
