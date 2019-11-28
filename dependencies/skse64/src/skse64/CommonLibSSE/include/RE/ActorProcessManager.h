#pragma once

#include "RE/BSFixedString.h"  // BSFixedString
#include "RE/BSIntrusiveRefCounted.h"  // BSIntrusiveRefCounted
#include "RE/BSTArray.h"  // BSTArray
#include "RE/BSTHashMap.h"  // BSTHashMap
#include "RE/BSTList.h"  // BSSimpleList
#include "RE/BSTSmartPointer.h"  // BSTSmartPointer
#include "RE/NiSmartPointer.h"  // NiPointer
#include "RE/PackageData.h"  // PackageData


namespace RE
{
	class Actor;
	class ActorKnowledge;
	class BGSAttackData;
	class DetectionListener;
	class MiddleProcess;
	class NiRefObject;
	class RunActionAnimationLoadedCallback;
	class TESForm;


	class ActorProcessManager
	{
	public:
		struct Hands
		{
			enum Hand : UInt32
			{
				kLeft,
				kRight,
				kTotal
			};
		};
		using Hand = Hands::Hand;


		enum class Flag : UInt8
		{
			kNone = 0,
			kUnk01 = 1 << 0,
			kUnk02 = 1 << 1,
			kUnk03 = 1 << 2,
			kDrawHead = 1 << 3,
			kMobile = 1 << 4,
			kReset = 1 << 5
		};


		struct Data010
		{
			struct ActorKnowledgeData
			{
				FormID			formID;		// 00
				UInt32			pad04;		// 04
				ActorKnowledge*	knowledge;	// 08
			};
			STATIC_ASSERT(sizeof(ActorKnowledgeData) == 0x10);


			struct Data190 : public BSIntrusiveRefCounted
			{
				struct Data
				{
					struct UnkData
					{
						UInt64	unk00;	// 00
						UInt64	unk08;	// 08
						UInt64	unk10;	// 10
						UInt64	unk18;	// 18
						UInt64	unk20;	// 20
						UInt64	unk28;	// 28
						UInt64	unk30;	// 30
						UInt64	unk38;	// 38
						UInt64	unk40;	// 40
						UInt64	unk48;	// 48
						UInt64	unk50;	// 50
						UInt64	unk58;	// 58
						UInt64	unk60;	// 60
						UInt64	unk68;	// 68
						UInt64	unk70;	// 70
						UInt64	unk78;	// 78
					};
					STATIC_ASSERT(sizeof(UnkData) == 0x80);


					UnkData*	unk00;	// 00
					UInt64		unk08;	// 08
				};
				STATIC_ASSERT(sizeof(Data) == 0x10);


				UInt32				unk04;	// 00
				BSTSmallArray<Data>	unk08;	// 08
				UInt64				unk28;	// 28
			};
			STATIC_ASSERT(sizeof(Data190) == 0x30);


			struct Data208
			{
				UInt64		unk00;	// 00
				UInt64		unk08;	// 08
				UInt64		unk10;	// 10
				UInt64		unk18;	// 18
				UInt64		unk20;	// 20
				UInt64		unk28;	// 28
				Data208*	next;	// 30
			};
			STATIC_ASSERT(sizeof(Data208) == 0x38);


			struct Data2FC
			{
				UInt32	unk0;	// 0
				UInt32	unk4;	// 4
				UInt32	unk8;	// 8
			};
			STATIC_ASSERT(sizeof(Data2FC) == 0xC);


			struct Data360 : public BSIntrusiveRefCounted
			{
				struct Data
				{
					void*			unk00;	// 00
					UInt64			unk08;	// 08
					UInt64			unk10;	// 10
					BSFixedString	unk18;	// 18
					UInt64			unk20;	// 20
					UInt64			unk28;	// 28
					UInt64			unk30;	// 30
					UInt64			unk38;	// 38
				};
				STATIC_ASSERT(sizeof(Data) == 0x40);


				UInt32				unk04;	// 00
				BSSimpleList<Data*>	unk08;	// 08
				UInt64				unk18;	// 18
				UInt64				unk20;	// 20
				UInt64				unk28;	// 28
				UInt64				unk30;	// 30
				UInt64				unk38;	// 38
				void*				unk40;	// 40
			};
			STATIC_ASSERT(sizeof(Data360) == 0x48);


			struct Data3C8
			{
				UInt64					unk00;	// 00
				UInt64					unk08;	// 08
				NiPointer<NiRefObject>	unk10;	// 10
				NiPointer<NiRefObject>	unk18;	// 18
				NiPointer<NiRefObject>	unk20;	// 20
				UInt64					unk28;	// 28
				UInt64					unk30;	// 30
				UInt64					unk38;	// 38
			};
			STATIC_ASSERT(sizeof(Data3C8) == 0x40);


			struct Data3D8
			{
				UInt64	unk00;	// 00
				UInt64	unk08;	// 08
				UInt64	unk10;	// 10
			};
			STATIC_ASSERT(sizeof(Data3D8) == 0x18);


			UInt64												unk000;				// 000
			UInt64												unk008;				// 008
			SInt32												shoutLevel;			// 010
			UInt32												unk014;				// 014
			UInt64												unk018;				// 018
			UInt64												unk020;				// 020
			UInt64												unk028;				// 028
			BSTArray<UInt64>									unk030;				// 030
			UInt64												unk048;				// 048
			UInt32												unk050;				// 050
			UInt32												pad054;				// 054
			BSTHashMap<BSFixedString, UnkValue>					unk058;				// 058
			UInt64												unk088;				// 088
			UInt64												unk090;				// 090
			UInt64												unk098;				// 098
			UInt64												unk0A0;				// 0A0
			UInt64												unk0A8;				// 0A8
			UInt64												unk0B0;				// 0B0
			UInt64												unk0B8;				// 0B8
			UInt64												unk0C0;				// 0C0
			UInt64												unk0C8;				// 0C8
			UInt64												unk0D0;				// 0D0
			UInt64												unk0D8;				// 0D8
			UInt64												unk0E0;				// 0E0
			UInt64												unk0E8;				// 0E8
			BSFixedString										dialogueText;		// 0F0
			float												unk0F8;				// 0F8
			float												unk0FC;				// 0FC
			float												unk100;				// 100
			float												unk104;				// 104
			float												unk108;				// 108
			float												unk10C;				// 10C
			float												unk110;				// 110
			float												unk114;				// 114
			float												unk118;				// 118
			float												unk11C;				// 11C
			float												unk120;				// 120
			float												unk124;				// 124
			float												unk128;				// 128
			float												unk12C;				// 12C
			UInt64												unk130;				// 130
			UInt64												unk138;				// 138
			UInt64												unk140;				// 140
			UInt64												unk148;				// 148
			UInt64												unk150;				// 150
			UInt64												unk158;				// 158
			float												unk160;				// 160
			UInt32												unk164;				// 164
			UInt64												unk168;				// 168
			UInt64												unk170;				// 170
			UInt64												unk178;				// 178
			void*												unk180;				// 180 - BSTSmartPointer
			void*												unk188;				// 188 - BSTSmartPointer
			BSTSmartPointer<Data190>							unk190;				// 190
			BSTSmartPointer<Data190>							unk198;				// 198
			float												unk1A0;				// 1A0
			float												unk1A4;				// 1A4
			float												unk1A8;				// 1A8
			UInt32												unk1AC;				// 1AC
			UInt64												unk1B0;				// 1B0
			UInt64												unk1B8;				// 1B8
			UInt64												unk1C0;				// 1C0
			UInt64												unk1C8;				// 1C8
			UInt64												unk1D0;				// 1D0
			UInt64												unk1D8;				// 1D8
			float												unk1E0;				// 1E0
			float												unk1E4;				// 1E4
			NiPointer<NiRefObject>								unk1E8;				// 1E8
			UInt32												unk1F0;				// 1F0
			float												unk1F4;				// 1F4
			UInt32												unk1F8;				// 1F8
			float												unk1FC;				// 1FC
			float												unk200;				// 200
			UInt32												pad204;				// 204
			Data208*											unk208;				// 208
			UInt64												unk210;				// 210
			BSFixedString										unk218;				// 218
			BSTArray<ActorKnowledgeData>						knowledgeData;		// 220
			mutable BSReadWriteLock								knowledgeDataLock;	// 238
			BSTArray<void*>										unk240;				// 240
			NiPointer<BGSAttackData>							attackData;			// 258
			UInt64												unk260;				// 260
			UInt64												unk268;				// 268
			UInt64												unk270;				// 270
			float												unk278;				// 278
			UInt32												unk27C;				// 27C
			UInt64												unk280;				// 280
			float												unk288;				// 288
			UInt32												unk28C;				// 28C
			UInt64												unk290;				// 290
			float												unk298;				// 298
			float												unk29C;				// 29C
			float												unk2A0;				// 2A0
			float												unk2A4;				// 2A4
			UInt64												unk2A8;				// 2A8
			float												unk2B0;				// 2B0
			UInt32												unk2B4;				// 2B4
			UInt64												unk2B8;				// 2B8
			UInt64												unk2C0;				// 2C0
			UInt64												unk2C8;				// 2C8
			UInt64												unk2D0;				// 2D0
			UInt64												unk2D8;				// 2D8
			UInt64												unk2E0;				// 2E0
			UInt64												unk2E8;				// 2E8
			UInt64												unk2F0;				// 2F0
			UInt32												unk2F8;				// 2F8
			Data2FC												unk2FC[2];			// 2FC
			UInt32												unk314;				// 314
			UInt32												unk318;				// 318
			float												unk31C;				// 31C
			UInt32												unk320;				// 320
			float												unk324;				// 324
			UInt64												unk328;				// 328
			UInt64												unk330;				// 330
			UInt64												unk338;				// 338
			UInt64												unk340;				// 340
			UInt64												unk348;				// 348
			UInt64												unk350;				// 350
			UInt64												unk358;				// 358
			BSTSmartPointer<Data360>							unk360;				// 360
			UInt64												unk368;				// 368
			void*												unk370;				// 370 - facegen preprocessed head?
			UInt64												unk378;				// 378
			NiPointer<NiRefObject>								unk380;				// 380
			float												unk388;				// 388
			UInt32												unk38C;				// 38C
			BSSimpleList<void*>									unk390;				// 390
			UInt32												unk3A0;				// 3A0
			float												unk3A4;				// 3A4
			float												lightLevel;			// 3A8
			float												unk3AC;				// 3AC
			float												unk3B0;				// 3B0
			UInt32												pad3B4;				// 3B4
			void*												unk3B8;				// 3B8
			UInt64												unk3C0;				// 3C0
			Data3C8*											unk3C8;				// 3C8
			UInt32												unk3D0;				// 3D0
			UInt32												pad3D4;				// 3D4
			Data3D8*											unk3D8;				// 3D8
			NiPointer<DetectionListener>						detectionListener;	// 3E0
			UInt64												unk3E8;				// 3E8
			UInt64												unk3F0;				// 3F0
			UInt64												unk3F8;				// 3F8
			BSTSmallArray<UInt64>								unk400;				// 400
			UInt64												unk418;				// 418
			UInt64												unk420;				// 420
			UInt64												unk428;				// 428
			BSTSmartPointer<RunActionAnimationLoadedCallback>	unk430;				// 430
			UInt64												unk438;				// 438
			UInt64												unk440;				// 440
			UInt64												unk448;				// 448
			UInt64												unk450;				// 450
			UInt64												unk458;				// 458
			UInt64												unk460;				// 460
			UInt64												unk468;				// 468
			UInt64												unk470;				// 470
		};
		STATIC_ASSERT(offsetof(Data010, knowledgeData) == 0x220);
		STATIC_ASSERT(offsetof(Data010, lightLevel) == 0x3A8);
		STATIC_ASSERT(sizeof(Data010) == 0x478);


		struct Data050
		{
			enum class Flag2 : UInt32
			{
				kNone = 0,
				kGhost = 1 << 20
			};


			UInt64			unk00;	// 00
			UInt64			unk08;	// 08
			UInt64			unk10;	// 10
			UInt64			unk18;	// 18
			UInt64			unk20;	// 20
			UInt32			flags1;	// 28
			Flag2			flags2;	// 2C
			BSTArray<void*>	unk30;	// 30
			BSTArray<void*>	unk48;	// 48
		};
		STATIC_ASSERT(sizeof(Data050) == 0x60);


		struct Data060
		{
			UInt64	unk00;	// 00
			UInt64	unk08;	// 08
			UInt64	unk10;	// 10
			UInt64	unk18;	// 18
			UInt64	unk20;	// 20
		};
		STATIC_ASSERT(sizeof(Data060) == 0x28);


		struct Data080
		{
			UInt64	unk00;	// 00
			UInt64	unk08;	// 08
			UInt64	unk10;	// 10
			UInt64	unk18;	// 18
			UInt64	unk20;	// 20
		};
		STATIC_ASSERT(sizeof(Data080) == 0x28);


		struct Data0B8
		{
			void*		unk00;	// 00
			Data0B8*	unk08;	// 08
			void*		unk10;	// 10
			void*		unk18;	// 18
			UInt64		unk20;	// 20
			void*		unk28;	// 28
			UInt32		unk30;	// 30
			UInt32		pad34;	// 34
		};
		STATIC_ASSERT(sizeof(Data0B8) == 0x38);


		void		SetEquipFlag(Flag a_flag);
		void		UpdateEquipment(Actor* a_actor);
		void		SetDataFlag(float a_flag);
		void		UpdateEquipment_Hooked(Actor* a_actor);
		TESForm*	GetEquippedLeftHand();
		TESForm*	GetEquippedRightHand();
		bool		IsGhost() const;


		// members
		UInt32*					unk000;							// 000
		MiddleProcess*			middleProcess;					// 008
		Data010*				unk010;							// 010
		PackageData				unk018;							// 018
		float					unk048;							// 048
		UInt32					unk04C;							// 04C
		Data050*				unk050;							// 050
		UInt32					unk058;							// 058
		UInt32					pad05C;							// 05C
		BSSimpleList<Data060*>	unk060;							// 060
		BSSimpleList<void*>		unk070;							// 070
		Data080*				unk080;							// 080
		Data080*				unk088;							// 088
		UInt32					unk090;							// 090
		float					timeOfDeath;					// 094 - GetTimeDead = (GameDaysPassed * 24) - timeOfDeath
		float					unk098;							// 098 - related with above
		UInt32					pad09C;							// 09C
		BSTArray<TESForm*>		forms;							// 0A0
		Data0B8					unk0B8;							// 0B8
		TESForm*				equippedObjects[Hand::kTotal];	// 0F0
		UInt64					unk100;							// 100
		UInt64					unk108;							// 108
		UInt32					unk110;							// 110
		RefHandle				unk114;							// 114
		UInt64					unk118;							// 118
		UInt64					unk120;							// 120
		UInt64					unk128;							// 128
		UInt32					unk130;							// 130
		UInt16					unk134;							// 134
		UInt8					unk136;							// 136
		SInt8					unk137;							// 137
		UInt8					unk138;							// 138
		UInt8					unk139;							// 139
		UInt8					unk13A;							// 13A
		UInt8					unk13B;							// 13B
		UInt32					pad13C;							// 13C
	};
	STATIC_ASSERT(sizeof(ActorProcessManager) == 0x140);
}
