#pragma once

#include "skse64/GameRTTI.h"  // RTTI_MainMenu

#include "RE/BSTEvent.h"  // BSTEventSink
#include "RE/GFxFunctionHandler.h"  // GFxFunctionHandler
#include "RE/ImageData.h"  // ImageData
#include "RE/IMenu.h"  // IMenu


namespace RE
{
	class BSSaveDataEvent;
	class BSSystemEvent;


	class MainMenu :
		public IMenu,							// 00
		public BSTEventSink<BSSystemEvent>,		// 30
		public BSTEventSink<BSSaveDataEvent>,	// 38
		public GFxFunctionHandler				// 40
	{
	public:
		inline static const void* RTTI = RTTI_MainMenu;


		virtual ~MainMenu();																									// 00

		// override (IMenu)
		virtual void	Accept(CallbackProcessor* a_processor) override;														// 01
		virtual Result	ProcessMessage(UIMessage* a_message) override;															// 04
		virtual void	NextFrame(float a_arg1, UInt32 a_currentTime) override;													// 05

		// override (BSTEventSink<BSSystemEvent>)
		virtual	EventResult	ReceiveEvent(BSSystemEvent* a_event, BSTEventSource<BSSystemEvent>* a_eventSource) override;		// 01

		// override (BSTEventSink<BSSaveDataEvent>)
		virtual	EventResult	ReceiveEvent(BSSaveDataEvent* a_event, BSTEventSource<BSSaveDataEvent>* a_eventSource) override;	// 01

		// override (GFxFunctionHandler)
		virtual void Call(Params& a_params) override;																			// 01


		// members
		ImageData	unk50;	// 50
		UInt32		unk68;	// 68
		UInt8		unk6C;	// 6C
		UInt8		unk6D;	// 6D
		UInt8		unk6E;	// 6E
		UInt8		pad6F;	// 6F
	};
	STATIC_ASSERT(sizeof(MainMenu) == 0x70);
}
