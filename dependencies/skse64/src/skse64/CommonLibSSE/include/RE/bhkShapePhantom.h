#pragma once

#include "skse64/GameRTTI.h"  // RTTI_bhkShapePhantom
#include "skse64/NiRTTI.h"  // NiRTTI_bhkShapePhantom

#include "RE/bhkPhantom.h"  // bhkPhantom


namespace RE
{
	class bhkShapePhantom : public bhkPhantom
	{
	public:
		inline static const void* RTTI = RTTI_bhkShapePhantom;
		inline static const void* Ni_RTTI = NiRTTI_bhkShapePhantom;


		virtual ~bhkShapePhantom();											// 00

		// override (bhkPhantom)
		virtual const NiRTTI*	GetRTTI() const override;					// 02
		virtual void			LinkObject(NiStream& a_stream) override;	// 19 - { bhkWorldObject::LinkObject(a_stream); }
	};
	STATIC_ASSERT(sizeof(bhkShapePhantom) == 0x30);
}
