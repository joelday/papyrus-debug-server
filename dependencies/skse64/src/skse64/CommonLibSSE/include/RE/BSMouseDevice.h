#pragma once

#include "skse64/GameRTTI.h"  // RTTI_BSMouseDevice

#include "RE/BSInputDevice.h"  // BSInputDevice


namespace RE
{
	class BSMouseDevice : public BSInputDevice
	{
	public:
		inline static const void* RTTI = RTTI_BSMouseDevice;


		virtual ~BSMouseDevice();	// 00

		// add
		virtual void Unk_09(void);	// 09 - { return; }


		// members
		bool	backgroundMouse;	// 70
		UInt8	unk71;				// 71
		UInt16	unk72;				// 72
		UInt32	unk74;				// 74
	};
	STATIC_ASSERT(sizeof(BSMouseDevice) == 0x78);
}
