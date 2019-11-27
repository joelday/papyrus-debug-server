#pragma once

#include "f4se_common/Utilities.h"
#include "f4se_common/Relocation.h"

#include "f4se/GameInput.h"
#include "f4se/GameTypes.h"
#include "f4se/GameUtilities.h"
#include "f4se/ScaleformAPI.h"
#include "f4se/ScaleformCallbacks.h"
#include "f4se/ScaleformValue.h"

typedef GFxValue* (*_GetChildElement)(GFxValue * parent, GFxValue & child, const char * path);
extern RelocAddr<_GetChildElement>	GetChildElement;

enum MessageType
{
	kMessage_Refresh = 0,
	kMessage_Open,
	kMessage_Close = 3,
	kMessage_Scaleform = 5,//keydown/up
	kMessage_Message,
	kMessage_Platform = 11
};

class UIMessage
{
public:
	virtual ~UIMessage();

	BSFixedString				name;		// 08
	UInt32						type;		// 10
};

class UIMessageManager
{
public:
	MEMBER_FN_PREFIX(UIMessageManager);
	DEFINE_MEMBER_FN(SendUIMessage, void, 0x0204CB90, BSFixedString& menuName, UInt32 type);
	// 325A22C9C57B8175C01F1E071B4E272401994375+CB
	DEFINE_MEMBER_FN(SendUIMessageEx, void, 0x012BAA10, BSFixedString& menuName, UInt32 type, UIMessage * pExtraData);
};
extern RelocPtr<UIMessageManager*>	g_uiMessageManager;

class IMenu : 
	public SWFToCodeFunctionHandler,
	public BSInputEventUser
{
public:
	enum
	{
		//Confirmed
		kFlag_PauseGame = 0x01,
		kFlag_DoNotDeleteOnClose = 0x02,
		kFlag_ShowCursor = 0x04,
		kFlag_EnableMenuControl = 0x08, // 1, 2
		kFlag_ShaderdWorld = 0x20,
		kFlag_Open = 0x40,//set it after open.
		kFlag_DoNotPreventGameSave = 0x800,
		kFlag_ApplyDropDownFilter = 0x8000, //
		kFlag_BlurBackground = 0x400000,

		//Unconfirmed
		kFlag_Modal = 0x10,
		kFlag_PreventGameLoad = 0x80,
		kFlag_Unk0100 = 0x100,
		kFlag_HideOther = 0x200,
		kFlag_DisableInteractive = 0x4000,
		kFlag_UpdateCursorOnPlatformChange = 0x400,
		kFlag_Unk1000 = 0x1000,
		kFlag_ItemMenu = 0x2000,
		kFlag_Unk10000 = 0x10000,	// mouse cursor
		kFlag_Unk800000 = 0x800000
	};
	virtual UInt32	ProcessMessage(UIMessage * msg) = 0;//???
	virtual void	DrawNextFrame(float unk0, void * unk1) = 0; //210E8C0
	virtual void *	Unk_05(void) { return nullptr; }; //return 0;
	virtual void *	Unk_06(void) { return nullptr; }; //return 0;
	virtual bool	Unk_07(UInt32 unk0, void * unk1) = 0;
	virtual void	Unk_08(UInt8 unk0) = 0;
	virtual void	Unk_09(BSFixedString & menuName, bool unk1) = 0;            //UInt64 = 0;            //UInt64
	virtual void	Unk_0A(void) = 0;
	virtual void	Unk_0B(void) = 0;
	virtual void	Unk_0C(void) = 0;
	virtual bool	Unk_0D(bool unk0) = 0;
	virtual bool	Unk_0E(void) { return false; };
	virtual bool	CanProcessControl(BSFixedString & controlID) { return false; };
	virtual bool	Unk_10(void) = 0;
	virtual void	Unk_11(void) = 0;
	virtual void	Unk_12(void * unk0) = 0;

	GFxValue		stage;			// 20
	GFxMovieView	* movie;		// 40
	BSFixedString	unk48;			// 48
	BSFixedString	menuName;		// 50
	UInt32			flags;			// 58

	/*
							A A A A A A A A B B B B B B B B C C C C C C C C D D D D D D D D
	LoadingMenu				0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 1 0 0 0 1 0 1 0 1 1 0 0 0 0 0 1		depth: 000E		context: 0003
	Console					0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 1 0 0 0 1 1 0 0 0 1 1 1		depth: 0013		context: 0006
	LevelUpMenu				0 0 0 0 0 1 0 0 0 0 0 0 1 1 0 1 0 0 0 0 0 1 0 0 1 1 0 0 0 1 1 1		depth: 0009		context: 0022
	FaderMenu				0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 1 0 0 0 0 1 0 0 0 0 1 0		depth: 0006		context: 0022
	CursorMenu				0 0 0 0 0 0 1 0 1 0 0 0 0 0 0 0 0 0 0 0 1 0 0 0 0 1 0 0 0 0 0 0		depth: 0014		context: 0022
	VignetteMenu			0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 1 0 0 0 0 1 0 0 0 0 0 0		depth: 0003		context: 0022
	MessageBoxMenu			0 0 0 0 1 0 0 0 0 0 0 0 0 0 0 1 1 0 0 0 0 1 0 0 1 1 0 1 1 1 0 1		depth: 000A		context: 0022
	ContainerMenu			0 0 0 0 1 0 0 0 0 0 0 0 1 1 0 1 1 0 1 0 0 1 0 1 0 1 0 0 1 1 0 1		depth: 0006		context: 0022
	ExamineMenu				0 0 0 0 1 0 0 0 0 0 0 0 1 1 0 0 1 0 1 0 0 1 0 1 0 1 0 0 0 1 0 1		depth: 0009		context: 0022
	CookingMenu				0 0 0 0 1 0 0 0 0 0 0 0 1 1 0 0 1 0 1 0 0 1 0 1 0 1 0 0 0 1 0 0		depth: 0009		context: 0022
	ExamineConfirmMenu		0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 1 0 0 0 0 1 0 0 0 1 0 1 1 1 0 1		depth: 0011		context: 0022
	RobotModMenu			0 0 0 0 1 0 0 0 0 0 0 0 1 1 0 0 1 0 1 0 0 1 0 1 0 1 0 0 0 1 0 0		depth: 0009		context: 0022
	PowerArmorModMenu		0 0 0 0 1 0 0 0 0 0 0 0 1 1 0 0 1 0 1 0 0 1 0 1 0 1 0 0 0 1 0 0		depth: 0009		context: 0022
	WorkshopMenu			0 0 0 0 0 0 0 0 0 0 0 0 1 1 0 0 1 0 0 0 0 0 0 1 0 1 0 0 0 0 0 0		depth: 0006		context: 0010
	PromptMenu				0 0 0 0 0 0 0 0 1 0 0 0 0 1 0 0 1 1 0 0 1 0 0 0 0 1 0 0 0 0 0 0		depth: 0005		context: 0022
	SitWaitMenu				0 0 0 0 0 0 0 0 1 0 0 0 1 1 0 0 1 1 0 0 1 0 0 0 0 1 0 0 0 0 0 0		depth: 0006		context: 0012
	SleepWaitMenu			0 0 0 0 1 0 0 0 0 1 0 0 1 1 0 1 1 0 0 0 1 0 0 1 1 1 0 0 1 1 0 1		depth: 000A		context: 0022
	DialogueMenu			0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 1 1 0 0 0 1 0 0 0 0 1 0 0 0 0 0 0		depth: 0006		context: 0022
	BarterMenu				0 0 0 0 1 0 0 0 0 0 0 0 1 1 0 1 1 0 1 0 0 1 0 1 0 1 0 0 1 1 0 1		depth: 0006		context: 0022
	LockpickingMenu			0 0 0 0 0 0 0 0 0 1 0 0 1 1 0 0 1 0 0 0 0 0 0 0 0 1 1 0 0 0 0 1		depth: 0006		context: 000C
	BookMenu				0 0 0 0 1 0 0 0 0 1 1 0 1 1 0 0 1 0 0 0 0 0 0 1 0 1 1 0 1 0 0 1		depth: 0009		context: 0008
	SPECIALMenu				0 0 0 0 1 0 0 0 0 1 0 0 1 1 0 1 1 0 0 0 0 1 0 0 1 1 1 0 1 1 0 1		depth: 0006		context: 0022
	FavoritesMenu			0 0 0 0 1 0 0 0 0 0 0 0 0 0 0 1 1 0 1 0 0 0 0 0 0 1 0 0 0 0 0 0		depth: 0006		context: 0001
	HUDMenu					0 0 0 0 0 0 0 0 1 0 0 0 0 0 0 0 1 1 0 0 1 0 0 0 0 1 0 0 0 0 0 0		depth: 0005		context: 0022
	PowerArmorHUDMenu		0 0 0 0 0 0 0 0 1 0 0 0 0 0 0 0 1 1 0 0 1 0 0 0 0 1 0 0 0 0 0 0		depth: 0005		context: 0022
	PauseMenu				0 0 0 0 1 0 0 0 0 1 0 0 1 1 0 0 1 0 0 0 1 1 1 0 0 1 0 1 1 1 0 1		depth: 000B		context: 0022
	VATSMenu				0 0 0 0 0 0 0 0 1 0 0 0 1 1 0 1 1 0 0 0 0 1 0 0 0 1 0 0 0 1 0 0		depth: 0006		context: 000D
	PipboyMenu				0 0 0 0 0 0 0 0 1 0 1 0 1 1 0 0 1 0 1 0 0 0 0 1 0 1 0 0 0 1 0 1		depth: 0008		context: 0022
	PipboyHolotapeMenu		0 0 0 0 1 0 0 0 0 0 1 0 0 0 0 0 1 0 0 0 0 0 0 0 0 1 0 0 1 0 0 1		depth: 0009		context: 0022
	*/

	UInt32			unk5C;			// 5C
	UInt32			unk60;			// 60	init'd as DWord then Byte
	UInt8			depth;			// 64   defalut is 6.
	UInt32			context;		// 68	init'd in IMenu::IMenu
	UInt32			pad6C;			// 6C
};
STATIC_ASSERT(offsetof(IMenu, movie) == 0x40);
STATIC_ASSERT(offsetof(IMenu, flags) == 0x58);

// E0
class GameMenuBase : public IMenu
{
public:
	GameMenuBase();
	virtual ~GameMenuBase();

	// BSInputEventUser overrides
	virtual void OnButtonEvent(ButtonEvent * inputEvent) override { Impl_OnGameMenuBaseButtonEvent(inputEvent); };

	// IMenu overrides
	virtual void	Invoke(Args * args) override { }
	virtual void	RegisterFunctions() override { }
	virtual UInt32	ProcessMessage(UIMessage * msg) override { return Impl_ProcessMessage(msg); };//???
	virtual void	DrawNextFrame(float unk0, void * unk1) override { return Impl_DrawNextFrame(unk0, unk1); }; //render,HUD menu uses this function to update its HUD components.
	virtual bool	Unk_07(UInt32 unk0, void * unk1) override { return Impl_Unk07(unk0, unk1); };
	virtual void	Unk_08(UInt8 unk0) override { return Impl_Unk08(unk0); };
	virtual void	Unk_09(BSFixedString & menuName, bool unk1)  override { return Impl_Unk09(menuName, unk1); };            //UInt64
	virtual void	Unk_0A(void) override { return Impl_Unk0A(); };
	virtual void	Unk_0B(void) override { return Impl_Unk0B(); }
	virtual void	Unk_0C(void) override { return Impl_Unk0C(); };
	virtual bool	Unk_0D(bool unk0) override { return Impl_Unk0D(unk0); }
	virtual bool	Unk_0E(void) override { return false; };
	virtual bool	CanProcessControl(BSFixedString & controlID) override { return false; };
	virtual bool	Unk_10(void) override { return Impl_Unk10(); } //90 - E0
	virtual void	Unk_11(void) override { return Impl_Unk11(); };
	virtual void	Unk_12(void * unk0) override { return Impl_Unk12(unk0); }
	virtual void	Unk_13(void * unk0, void * unk1) { return Impl_Unk13(unk0, unk1); }

	tArray<BSGFxDisplayObject*>		subcomponents;					// 70
	BSGFxShaderFXTarget				* shaderTarget;					// 88
	void							* unk90;						// 90
	UInt64							unk98[(0xE0 - 0x98) >> 3];		// 98

	DEFINE_STATIC_HEAP(ScaleformHeap_Allocate, ScaleformHeap_Free)
private:
	// ??_7GameMenuBase@@6B@

	DEFINE_MEMBER_FN_0(Impl_ctor, void *, 0x00B324E0);
	DEFINE_MEMBER_FN_0(Impl_dtor, void *, 0x00B325A0);
	DEFINE_MEMBER_FN_2(Impl_DrawNextFrame, void, 0x0210EED0, float unk0, void * unk1);
	DEFINE_MEMBER_FN_1(Impl_ProcessMessage, UInt32, 0x0210EE50, UIMessage * msg);
	DEFINE_MEMBER_FN_2(Impl_Unk07, bool, 0x0210F310, UInt32 unk0, void * unk1);
	DEFINE_MEMBER_FN_1(Impl_Unk08, void, 0x00B32A50, UInt8 unk0);
	DEFINE_MEMBER_FN_2(Impl_Unk09, void, 0x0210F550, BSFixedString & menuName, bool unk1);
	DEFINE_MEMBER_FN_0(Impl_Unk0A, void, 0x00B32AC0);
	DEFINE_MEMBER_FN_0(Impl_Unk0B, void, 0x00B32B80);
	DEFINE_MEMBER_FN_0(Impl_Unk0C, void, 0x00B32BC0)
	DEFINE_MEMBER_FN_1(Impl_Unk0D, bool, 0x0210F6A0, bool unk0);
	DEFINE_MEMBER_FN_0(Impl_Unk10, bool, 0x00B32870);
	DEFINE_MEMBER_FN_0(Impl_Unk11, void, 0x00B32900);
	DEFINE_MEMBER_FN_1(Impl_Unk12, void, 0x00B32970, void * unk0);
	DEFINE_MEMBER_FN_2(Impl_Unk13, void, 0x00B329C0, void * unk0, void * unk1);
};
STATIC_ASSERT(offsetof(GameMenuBase, shaderTarget) == 0x88);

// 218
class LooksMenu : public GameMenuBase
{
public:
	BSTEventSink<ChargenCharacterUpdateEvent> eventSink; // E0
	UInt64	unkE8;	// E8
	void	* unkF0; // F0 - LooksInputRepeatHandler
	UInt64 unkF8[(0x150-0xF8)/8];
	UInt32	nextBoneID;			// 150
	UInt32	currentBoneID;		// 154
	UInt64	unk158[(0x1E0-0x158)/8];
	UInt32	unk1E0;				// 1E0
	UInt32	unk1E4;				// 1E4
	UInt64	unk1E8[(0x218-0x1E8)/8];

	DEFINE_MEMBER_FN_0(LoadCharacterParameters, void, 0x00B41580); // This function updates all the internals from the current character
																 // It's followed by a call to onCommitCharacterPresetChange
};
STATIC_ASSERT(offsetof(LooksMenu, nextBoneID) == 0x150);

// 20
template <class T>
class HUDContextArray
{
public:
	T			* entries;	// 00
	UInt32		count;		// 08
	UInt32		unk0C;		// 0C
	UInt32		flags;		// 10
	UInt32		unk14;		// 14
	UInt32		unk18;		// 18
	bool		unk1C;		// 1C
};

// F8
class HUDComponentBase : public BSGFxShaderFXTarget
{
public:
	HUDComponentBase(GFxValue * parent, const char * componentName, HUDContextArray<BSFixedString> * contextList);
	virtual ~HUDComponentBase();

	virtual bool Unk_02(void * unk1) { return false; }
	virtual void Unk_03() { }
	virtual void UpdateComponent() { Impl_UpdateComponent(); } // Does stuff
	virtual void UpdateVisibilityContext(void * unk1);
	virtual void ColorizeComponent();
	virtual bool IsVisible() { return Impl_IsVisible(); }
	virtual bool Unk_08() { return contexts.unk1C; }

	UInt64							unkB0;			// B0
	UInt64							unkB8;			// B8
	UInt64							unkC0;			// C0
	HUDContextArray<BSFixedString>	contexts;		// C8
	float							unkE8;			// E8
	UInt32							unkEC;			// EC
	UInt8							unkF0;			// F0
	UInt8							unkF1;			// F1
	bool							isWarning;		// F2 - This chooses the warning color over the default color
	UInt8							padF3[5];		// F3

	MEMBER_FN_PREFIX(HUDComponentBase);
	DEFINE_MEMBER_FN_3(Impl_ctor, HUDComponentBase *, 0x00A22A70, GFxValue * parent, const char * componentName, HUDContextArray<BSFixedString> * contextList);
	DEFINE_MEMBER_FN_0(Impl_IsVisible, bool, 0x00A22DB0);
	DEFINE_MEMBER_FN_0(Impl_UpdateComponent, void, 0x00A22B10);
	
};
STATIC_ASSERT(offsetof(HUDComponentBase, contexts) == 0xC8);
STATIC_ASSERT(offsetof(HUDComponentBase, unkE8) == 0xE8);
STATIC_ASSERT(sizeof(HUDComponentBase) == 0xF8);

typedef bool (* _HasHUDContext)(HUDContextArray<BSFixedString> * contexts, void * unk1);
extern RelocAddr <_HasHUDContext> HasHUDContext;


// 110
class HUDComponents
{
public:
	UInt64								unk00;					// 00
	HUDComponentBase					* components[0x1E];		// 08
	UInt64								unk98;					// 98
	UInt64								unk100;					// 100
	UInt32								numComponents;			// 108 - 0x1E
};

// 220
class HUDMenu : public GameMenuBase
{
public:
	BSTEventSink<UserEventEnabledEvent> inputEnabledSink;		// E0
	BSTEventSink<RequestHUDModesEvent>	requestHudModesSink;	// E8
	HUDComponents						children;				// F0
	UInt64								unk200;					// 200
	UInt64								unk208;					// 208
	UInt64								unk210;					// 210
	UInt64								unk218;					// 218
};
STATIC_ASSERT(offsetof(HUDMenu, unk200) == 0x200);

// 18
class PipboySubMenu : public BSTEventSink<struct PipboyValueChangedEvent>
{
public:

	virtual ~PipboySubMenu();

	virtual	void Unk02();	// Pure, called by PipboySubMenu::ReceiveEvent

	GFxValue	*value;
	UInt64		unk10;
};

// 18
class PipboyQuestMenu : public PipboySubMenu
{
public:

	virtual ~PipboyQuestMenu();	
};


// 18 
class PipboyValue
{
public:
	virtual ~PipboyValue();
	virtual	void Unk01();	// Sets unk0C to 0
	virtual void Unk02();	// pure
	virtual void Unk03(void *arg1);
	virtual void Unk04();	// pure

	UInt32		unk08;	// 08 - init'd to incremental variable
	UInt8		unk0C;	// 0C - init'd to 1
	UInt8		unk0D;	// 0D - init'd to 1
	UInt16		pad0E;	// 0E
	PipboyValue	*unk10;	// 10
};

template <class T>
class PipboyPrimitiveValue : public PipboyValue
{
public:

	T	value;	// 18	
};
STATIC_ASSERT(offsetof(PipboyPrimitiveValue<bool>, value) == 0x18);

class PipboyObject : public PipboyValue
{
public:
	struct PipboyTableItem
	{
		BSFixedString	key;
		PipboyValue		*value;

		bool operator==(const BSFixedString & a_name) const { return key == a_name; }
		operator BSFixedString() const { return key; }

		static inline UInt32 GetHash(BSFixedString * key)
		{
			UInt32 hash;
			CalculateCRC32_64(&hash, (UInt64)key->data, 0);
			return hash;
		}
	};


	virtual ~PipboyObject();

	tHashSet<PipboyTableItem, BSFixedString>	table;	// 18
	//...
};
STATIC_ASSERT(offsetof(PipboyObject, table) == 0x18);

// 00C
class MenuTableItem
{
public:
	typedef IMenu * (*CallbackType)(void);
	BSFixedString	name;				// 000
	IMenu			* menuInstance;		// 008	0 if the menu is not currently open
	CallbackType	menuConstructor;	// 010
	void			* unk18;			// 018

	bool operator==(const MenuTableItem & rhs) const	{ return name == rhs.name; }
	bool operator==(const BSFixedString a_name) const	{ return name == a_name; }
	operator UInt64() const								{ return (UInt64)name.data->Get<char>(); }

	static inline UInt32 GetHash(BSFixedString * key)
	{
		UInt32 hash;
		CalculateCRC32_64(&hash, (UInt64)key->data, 0);
		return hash;
	}

	void Dump(void)
	{
		_MESSAGE("\t\tname: %s", name.data->Get<char>());
		_MESSAGE("\t\tinstance: %08X", menuInstance);
	}
};

// 250 ?
class UI
{
public:
	virtual ~UI();

	virtual void	Unk_01(void);

	typedef IMenu*	(*CreateFunc)(void);
	typedef tHashSet<MenuTableItem,BSFixedString> MenuTable;

	bool	IsMenuOpen(const BSFixedString & menuName);
	IMenu * GetMenu(BSFixedString & menuName);
	IMenu * GetMenuByMovie(GFxMovieView * movie);
	void	Register(const char* name, CreateFunc creator)
	{
		CALL_MEMBER_FN(this, RegisterMenu)(name, creator, 0);
	}
	bool IsMenuRegistered(BSFixedString & menuName);

	template<typename T>
	void ForEachMenu(T & menuFunc)
	{
		g_menuTableLock->LockForReadAndWrite();
		menuTable.ForEach(menuFunc);
		g_menuTableLock->Release();
	}

	bool UnregisterMenu(BSFixedString & name, bool force = false);

	UInt64									unk08;						// 08
	UInt64									unk10;						// 10
	BSTEventDispatcher<MenuOpenCloseEvent>	menuOpenCloseEventSource;	// 70
	UInt64									unk70[(0x190 - 0x70) / 8];
	tArray<IMenu*>							menuStack;		// 190
	MenuTable								menuTable;		// 1A8
	UInt64									unk1D8;         // 1D8
	UInt32									numPauseGame;   // 1E0 isInMenuMode
	volatile	SInt32						numFlag2000;	// 1E4
	volatile	SInt32						numFlag80;		// 1E8
	UInt32									numFlag20;		// 1EC
	// ...

protected:
	MEMBER_FN_PREFIX(UI);
	DEFINE_MEMBER_FN(RegisterMenu, void, 0x02043CF0, const char * name, CreateFunc creator, UInt64 unk1);
	DEFINE_MEMBER_FN(IsMenuOpen, bool, 0x02042160, const BSFixedString & name);
};

extern RelocPtr <BSReadWriteLock> g_menuTableLock;
extern RelocPtr <UI*> g_ui;
