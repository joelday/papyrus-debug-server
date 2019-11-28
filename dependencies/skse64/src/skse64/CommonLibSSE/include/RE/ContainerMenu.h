#pragma once

#include "skse64/GameRTTI.h"  // RTTI_ContainerMenu

#include "RE/BSTArray.h"  // BSTArray
#include "RE/GFxValue.h"  // GFxValue
#include "RE/IMenu.h"  // IMenu


namespace RE
{
	struct BottomBar;
	struct ItemCard;
	struct ItemList;


	class ContainerMenu : public IMenu
	{
	public:
		inline static const void* RTTI = RTTI_ContainerMenu;


		virtual ~ContainerMenu();											// 00

		// override (IMenu)
		virtual void	Accept(CallbackProcessor* a_processor) override;	// 01
		virtual Result	ProcessMessage(UIMessage* a_message) override;		// 04
		virtual void	Render() override;									// 06


		// members
		GFxValue		root;				// 30 - "Menu_mc"
		ItemList*		list;				// 48
		ItemCard*		itemCard;			// 50
		BottomBar*		bottomBar;			// 58
		BSTArray<void*>	unk60;				// 60
		BSTArray<void*>	unk78;				// 78
		UInt64			unk90;				// 90
		UInt64			unk98;				// 98
		UInt64			unkA0;				// A0
		UInt8			unkA8;				// A8
		UInt8			padA9;				// A9
		UInt16			padAA;				// AA
		UInt32			padAC;				// AC
		SInt32			value;				// B0
		UInt32			unkB4;				// B4
		UInt8			unkB8;				// B8
		bool			pcControlsReady;	// B9
		UInt16			padBA;				// BA
		UInt32			padBC;				// BC
	};
	STATIC_ASSERT(sizeof(ContainerMenu) == 0xC0);
}
