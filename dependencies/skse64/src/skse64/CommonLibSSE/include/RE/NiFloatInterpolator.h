#pragma once

#include "skse64/GameRTTI.h"  // RTTI_NiFloatInterpolator
#include "skse64/NiRTTI.h"  // NiRTTI_NiFloatInterpolator

#include "RE/NiKeyBasedInterpolator.h"  // NiKeyBasedInterpolator
#include "RE/NiSmartPointer.h"  // NiPointer


namespace RE
{
	class NiFloatData;


	class NiFloatInterpolator : public NiKeyBasedInterpolator
	{
	public:
		inline static const void* RTTI = RTTI_NiFloatInterpolator;
		inline static const void* Ni_RTTI = NiRTTI_NiFloatInterpolator;


		virtual ~NiFloatInterpolator();																					// 00

		// override (NiKeyBasedInterpolator)
		virtual const NiRTTI*	GetRTTI() const override;																// 02
		virtual NiObject*		CreateClone(NiCloningProcess& a_cloning) override;										// 17
		virtual void			LoadBinary(NiStream& a_stream) override;												// 18
		virtual void			LinkObject(NiStream& a_stream) override;												// 19 - { NiKeyBasedInterpolator::LinkObject(a_stream); }
		virtual bool			RegisterStreamables(NiStream& a_stream) override;										// 1A
		virtual void			SaveBinary(NiStream& a_stream) override;												// 1B
		virtual bool			IsEqual(NiObject* a_object) override;													// 1C
		virtual bool			Update(float a_time, NiObjectNET* a_interpTarget, NiQuatTransform* a_value) override;	// 25 - { return NiInterpolator::UpdateTransform(a_time, a_interpTarget, a_value); }
		virtual bool			Update(float a_time, NiObjectNET* a_target, NiColorA* a_value) override;				// 26 - { return NiInterpolator::UpdateTransform(a_time, a_interpTarget, a_value); }
		virtual bool			Update(float a_time, NiObjectNET* a_interpTarget, NiPoint3* a_value) override;			// 27 - { return NiInterpolator::UpdateTransform(a_time, a_interpTarget, a_value); }
		virtual bool			Update(float a_time, NiObjectNET* a_interpTarget, NiQuaternion* a_value) override;		// 28 - { return NiInterpolator::UpdateTransform(a_time, a_interpTarget, a_value); }
		virtual bool			Update(float a_time, NiObjectNET* a_interpTarget, float* a_value) override;				// 29
		virtual bool			Update(float a_time, NiObjectNET* a_interpTarget, bool* a_value) override;				// 2A - { return NiInterpolator::UpdateTransform(a_time, a_interpTarget, a_value); }
		virtual bool			IsFloatValueSupported() const override;													// 2C - { return true; }
		virtual void			Collapse() override;																	// 31
		virtual void			GuaranteeTimeRange(float a_start, float a_end) override;								// 33
		virtual NiInterpolator*	GetSequenceInterpolator(float a_start, float a_end) override;							// 34
		virtual UInt16			GetKeyChannelCount() const override;													// 39 - { return 1; }
		virtual UInt32			GetKeyCount(UInt16 a_channel) const override;											// 3A - { return floatData ? floatData->numKeys : 0; }
		virtual KeyContent		GetKeyContent(UInt16 a_channel) const override;											// 3B - { KeyContent::kFloat; }
		virtual KeyType			GetKeyType(UInt16 a_channel) const override;											// 3C - { return floatData ? floatData->type : 0; }
		virtual void*			GetKeyArray(UInt16 a_channel) const override;											// 3D - { return floatData ? floatData->keys : 0; }
		virtual UInt8			GetKeyStride(UInt16 a_channel) const override;											// 3E - { return floatData ? floatData->keySize : 0; }
		virtual bool			GetChannelPosed(UInt16 a_channel) const override;										// 3F - { return !floatData && floatValue != -3.4028235e38; }


		// members
		float					floatValue;	// 18
		UInt32					pad1C;		// 1C
		NiPointer<NiFloatData>	floatData;	// 20
		UInt32					lastIndex;	// 28
		UInt32					pad2C;		// 2C
	};
	STATIC_ASSERT(sizeof(NiFloatInterpolator) == 0x30);
}
