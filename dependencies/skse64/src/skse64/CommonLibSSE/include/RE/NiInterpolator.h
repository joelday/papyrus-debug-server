#pragma once

#include "skse64/GameRTTI.h"  // RTTI_NiInterpolator
#include "skse64/NiRTTI.h"  // NiRTTI_NiInterpolator

#include "RE/NiObject.h"  // NiObject


namespace RE
{
	class NiAVObjectPalette;
	class NiColorA;
	class NiObjectNET;
	class NiPoint3;
	class NiQuaternion;
	class NiQuatTransform;


	class NiInterpolator : public NiObject
	{
	public:
		inline static const void* RTTI = RTTI_NiInterpolator;
		inline static const void* Ni_RTTI = NiRTTI_NiInterpolator;


		virtual ~NiInterpolator();																				// 00

		// override (NiObject)
		virtual const NiRTTI*	GetRTTI() const override;														// 02
		virtual void			LoadBinary(NiStream& a_stream) override;										// 18 - { NiObject::LoadBinary(a_stream); }
		virtual void			LinkObject(NiStream& a_stream) override;										// 19 - { NiObject::LinkObject(a_stream); }
		virtual bool			RegisterStreamables(NiStream& a_stream) override;								// 1A - { return NiObject::RegisterStreamables(a_stream); }
		virtual void			SaveBinary(NiStream& a_stream) override;										// 1B - { NiObject::SaveBinary(a_stream); }
		virtual bool			IsEqual(NiObject* a_object) override;											// 1C - { return NiObject::IsEqual(a_stream); }

		// add
		virtual bool			Update(float a_time, NiObjectNET* a_interpTarget, NiQuatTransform* a_value);	// 25 - { return false; }
		virtual bool			Update(float a_time, NiObjectNET* a_interpTarget, NiColorA* a_value);			// 26 - { return false; }
		virtual bool			Update(float a_time, NiObjectNET* a_interpTarget, NiPoint3* a_value);			// 27 - { return false; }
		virtual bool			Update(float a_time, NiObjectNET* a_interpTarget, NiQuaternion* a_value);		// 28 - { return false; }
		virtual bool			Update(float a_time, NiObjectNET* a_interpTarget, float* a_value);				// 29 - { return false; }
		virtual bool			Update(float a_time, NiObjectNET* a_interpTarget, bool* a_value);				// 2A - { return false; }
		virtual bool			IsBoolValueSupported() const;													// 2B - { return false; }
		virtual bool			IsFloatValueSupported() const;													// 2C - { return false; }
		virtual bool			IsQuaternionValueSupported() const;												// 2D - { return false; }
		virtual bool			IsPoint3ValueSupported() const;													// 2E - { return false; }
		virtual bool			IsColorAValueSupported() const;													// 2F - { return false; }
		virtual bool			IsTransformValueSupported() const;												// 30 - { return false; }
		virtual void			Collapse();																		// 31 - { return; }
		virtual void			GetActiveTimeRange(float& a_beginKeyTime, float& a_endKeyTime) const;			// 32 - { a_beginKeyTime = 0.0; a_endKeyTime = 0.0; }
		virtual void			GuaranteeTimeRange(float a_startTime, float a_endTime);							// 33 - { return; }
		virtual NiInterpolator*	GetSequenceInterpolator(float a_startTime, float a_endTime);					// 34
		virtual bool			ResolveDependencies(NiAVObjectPalette* a_palette);								// 35 - { return true; }
		virtual bool			SetUpDependencies();															// 36 - { return true; }
		virtual bool			AlwaysUpdate() const;															// 37 - { return false; }
		virtual void			Unk_38(void);																	// 38 - { return 0; }


		// members
		float	lastTime;	// 10
		UInt32	pad14;		// 14
	};
	STATIC_ASSERT(sizeof(NiInterpolator) == 0x18);
}
