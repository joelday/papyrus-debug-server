#pragma once

#include "f4se/GameRTTI.h"  // RTTI_BSScript__IObjectHandlePolicy

#include "RE/FormTypes.h"  // FormType


namespace RE
{
	class BSFixedString;
	class TESForm;


	namespace BSScript
	{
		struct IObjectHandlePolicy
		{
		public:
			inline static const void* RTTI = RTTI_BSScript__IObjectHandlePolicy;


			virtual ~IObjectHandlePolicy();														// 00

			virtual bool	IsType(FormType32 a_typeID, VMHandle a_handle) = 0;
			virtual bool	Unk_02(UInt64 unk1, FormType32* formType) = 0;
			virtual bool	IsValidHandle(VMHandle a_handle) = 0; // TODO: Guessing
			virtual bool	HasBoundGameObject(VMHandle a_handle) = 0;
			virtual bool	Unk_05(UInt64 a_unk1) = 0;
			virtual UInt64	GetInvalidHandle() = 0;
			virtual UInt64	GetHandle(FormType32 a_typeID, const TESForm* a_srcData) = 0;
			virtual bool	IsREFR(VMHandle a_handle) = 0;	// return IsType(TESObjectREFR::kTypeID, handle);
			virtual UInt64	Unk_09(UInt64 a_unk1) = 0;
			virtual UInt32	Unk_0A(UInt64 a_unk1) = 0;
			virtual UInt32	Unk_0B(UInt64 a_unk1) = 0;
			virtual void*	Resolve(FormType32 a_typeID, VMHandle a_handle) = 0;
			virtual void	AddRef(VMHandle a_handle) = 0;
			virtual void	Release(VMHandle a_handle) = 0;
			virtual void	ToString(VMHandle a_handle, BSFixedString& a_strOut) = 0;

			bool		IsType(FormType a_typeID, VMHandle a_handle);
			VMHandle	GetHandle(FormType a_typeID, const TESForm* a_srcData);
			void*		Resolve(FormType a_typeID, VMHandle a_handle);
		};
		STATIC_ASSERT(sizeof(IObjectHandlePolicy) == 0x8);
	}
}
