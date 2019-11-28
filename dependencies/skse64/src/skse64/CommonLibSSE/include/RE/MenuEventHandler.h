#pragma once

#include "skse64/GameRTTI.h"  // RTTI_MenuEventHandler

#include "RE/BSIntrusiveRefCounted.h"  // BSIntrusiveRefCounted


namespace RE
{
	class ButtonEvent;
	class InputEvent;
	class KinectEvent;
	class MouseMoveEvent;
	class ThumbstickEvent;


	class MenuEventHandler : public BSIntrusiveRefCounted
	{
	public:
		inline static const void* RTTI = RTTI_MenuEventHandler;


		MenuEventHandler() = default;
		virtual ~MenuEventHandler() = default;							// 00

		virtual bool	CanProcess(InputEvent* a_event) = 0;			// 01
		virtual bool	ProcessKinect(KinectEvent* a_event);			// 02 - { return false; }
		virtual bool	ProcessThumbstick(ThumbstickEvent* a_event);	// 03 - { return false; }
		virtual bool	ProcessMouseMove(MouseMoveEvent* a_event);		// 04 - { return false; }
		virtual bool	ProcessButton(ButtonEvent* a_event);			// 05 - { return false; }


		// members
		bool	registered;	// 0C
		UInt8	unk0D;		// 0D
		UInt16	pad0E;		// 0E
	};
	STATIC_ASSERT(sizeof(MenuEventHandler) == 0x10);
}
