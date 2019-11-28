#pragma once

#include "skse64/GameRTTI.h"  // RTTI_JournalMenu

#include "RE/BSTEvent.h"  // BSTEventSink
#include "RE/IMenu.h"  // IMenu
#include "RE/Journal_QuestsTab.h"  // Journal_QuestsTab
#include "RE/Journal_StatsTab.h"  // Journal_StatsTab
#include "RE/Journal_SystemTab.h"  // Journal_SystemTab
#include "RE/MenuEventHandler.h"  // MenuEventHandler


namespace RE
{
	class BSSystemEvent;


	class JournalMenu :
		public IMenu,						// 00
		public MenuEventHandler,			// 30
		public BSTEventSink<BSSystemEvent>	// 40
	{
	public:
		inline static const void* RTTI = RTTI_JournalMenu;


		virtual ~JournalMenu();																								// 00

		// override (IMenu)
		virtual void	Accept(CallbackProcessor* a_processor) override;													// 01
		virtual Result	ProcessMessage(UIMessage* a_message) override;														// 04
		virtual void	NextFrame(float a_arg1, UInt32 a_currentTime) override;												// 05
		virtual void	Render() override;																					// 06

		// override (MenuEventHandler)
		virtual bool	CanProcess(InputEvent* a_event) override;															// 01
		virtual bool	ProcessThumbstick(ThumbstickEvent* a_event) override;												// 03

		// override (BSTEventSink<BSSystemEvent>)
		virtual	EventResult	ReceiveEvent(BSSystemEvent* a_event, BSTEventSource<BSSystemEvent>* a_eventSource) override;	// 01


		// members
		Journal_QuestsTab	questsTab;	// 48
		Journal_StatsTab	statsTab;	// 80
		Journal_SystemTab	systemTab;	// 98
		UInt64				unkD0;		// D0
		UInt64				unkD8;		// D8
		UInt64				unkE0;		// E0
	};
	STATIC_ASSERT(sizeof(JournalMenu) == 0xE8);
}
