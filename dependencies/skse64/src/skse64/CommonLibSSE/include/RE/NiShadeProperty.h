#pragma once

#include "skse64/GameRTTI.h"  // RTTI_NiShadeProperty
#include "skse64/NiRTTI.h"  // NiRTTI_NiShadeProperty

#include "RE/NiProperty.h"  // NiProperty


namespace RE
{
	class NiShadeProperty : public NiProperty
	{
	public:
		inline static const void* RTTI = RTTI_NiShadeProperty;
		inline static const void* Ni_RTTI = NiRTTI_NiShadeProperty;


		virtual ~NiShadeProperty();													// 00

		// override (NiProperty)
		virtual const NiRTTI*	GetRTTI() const override;							// 02
		virtual NiObject*		CreateClone(NiCloningProcess& a_cloning) override;	// 17
		virtual void			LoadBinary(NiStream& a_stream) override;			// 18 - { NiProperty::LoadBinary(a_stream); }
		virtual void			LinkObject(NiStream& a_stream) override;			// 19 - { NiProperty::LinkObject(a_stream); }
		virtual bool			RegisterStreamables(NiStream& a_stream) override;	// 1A - { return NiProperty::RegisterStreamables(a_stream); }
		virtual void			SaveBinary(NiStream& a_stream) override;			// 1B - { NiProperty::SaveBinary(a_stream); }
		virtual bool			IsEqual(NiObject* a_object) override;				// 1C - { return NiProperty::IsEqual(a_object); }
		virtual Type			GetType() const override;							// 25 - { return Type::kShade; }

		// add
		virtual void			Unk_27(void);										// 27 - { return 1; }
		virtual void			Unk_28(void);										// 28 - { return 1; }
		virtual void			Unk_29(void);										// 29 - { return; }
	};
	STATIC_ASSERT(sizeof(NiShadeProperty) == 0x30);
}
