#pragma once

#include "skse64/GameRTTI.h"  // RTTI_TrainingMenu

#include "RE/ActorValues.h"  // ActorValue
#include "RE/BSTEvent.h"  // BSTEventSink
#include "RE/GFxValue.h"  // GFxValue
#include "RE/IMenu.h"  // IMenu


namespace RE
{
	class MenuOpenCloseEvent;


	class TrainingMenu :
		public IMenu,							// 00
		public BSTEventSink<MenuOpenCloseEvent>	// 30
	{
	public:
		inline static const void* RTTI = RTTI_TrainingMenu;


		virtual ~TrainingMenu();																									// 00

		// override (IMenu)
		virtual void		Accept(CallbackProcessor* a_cbReg) override;															// 01
		virtual Result		ProcessMessage(UIMessage* a_message) override;															// 04

		// override (BSTEventSink<MenuOpenCloseEvent>)
		virtual	EventResult	ReceiveEvent(MenuOpenCloseEvent* a_event, BSTEventSource<MenuOpenCloseEvent>* a_eventSource) override;	// 01


		// members
		void*		unk38;				// 38 - smart ptr
		ActorValue	skill;				// 40
		UInt32		unk44;				// 44
		GFxValue	trainingMenuObj;	// 48 - MovieClip
		GFxValue	skillName;			// 60 - TextField
		GFxValue	skillMeter;			// 78 - Components.Meter
		GFxValue	trainerSkill;		// 90 - TextField
		GFxValue	timesTrained;		// A8 - TextField
		GFxValue	trainCost;			// C0 - TextField
		GFxValue	currentGold;		// D8 - TextField
	};
	STATIC_ASSERT(sizeof(TrainingMenu) == 0xF0);
}
