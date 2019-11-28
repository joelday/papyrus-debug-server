#pragma once

#include "skse64/GameRTTI.h"  // RTTI_PlayerCamera

#include "RE/BSTArray.h"  // BSTSmallArray
#include "RE/BSTSingleton.h"  // BSTSingletonSDM
#include "RE/BSTSmartPointer.h"  // BSTSmartPointer
#include "RE/BSLock.h"  // BSUniqueLock
#include "RE/NiPoint3.h"  // NiPoint3
#include "RE/TESCamera.h"  // TESCamera


namespace RE
{
	class bhkRigidBody;
	class bhkSimpleShapePhantom;
	class NiRefObject;
	class TESCameraState;


	class PlayerCamera :
		public TESCamera,						// 000
		public BSTSingletonSDM<PlayerCamera>	// 038
	{
	public:
		inline static const void* RTTI = RTTI_PlayerCamera;


		struct CameraStates
		{
			enum CameraState : UInt32
			{
				kFirstPerson = 0,
				kAutoVanity,
				kVATS,
				kFree,
				kIronSights,
				kFurniture,
				kTransition,
				kTweenMenu,
				kThirdPerson1,
				kThirdPerson2,
				kHorse,
				kBleedout,
				kDragon,

				kTotal
			};
		};
		using CameraState = CameraStates::CameraState;


		struct Unk120
		{
			NiPointer<bhkSimpleShapePhantom*>	unk00;	// 00
			NiPointer<bhkSimpleShapePhantom*>	unk08;	// 08
		};
		STATIC_ASSERT(sizeof(Unk120) == 0x10);


		virtual ~PlayerCamera();									// 00

		// override (TESCamera)
		virtual void SetNode(NiPointer<NiNode> a_node) override;	// 01

		static PlayerCamera* GetSingleton();

		void UpdateThirdPerson(bool a_weaponDrawn);


		// members
		UInt8												pad039;								// 039
		UInt16												pad03A;								// 03A
		RefHandle											handle;								// 03C
		BSTSmallArray<TESCameraState*, CameraState::kTotal>	unk040;								// 040
		BSTSmartPointer<TESCameraState>						cameraStates[CameraState::kTotal];	// 0B8
		Unk120*												unk120;								// 120
		NiPointer<bhkRigidBody>								rigidBody;							// 128
		RefHandle											objectFadeHandle;					// 130
		mutable BSUniqueLock								lock;								// 134
		float												worldFOV;							// 13C
		float												firstPersonFOV;						// 140
		NiPoint3											pos;								// 144
		float												idleTimer;							// 150
		float												yaw;								// 154 - in radians
		UInt32												unk158;								// 158
		UInt32												unk15C;								// 15C
		bool												allowAutoVanity;					// 160
		bool												isBowZoom;							// 161
		bool												isWeapSheathed;						// 162
		bool												isProcessed;						// 163
		UInt8												unk164;								// 164
		UInt8												unk165;								// 165
		UInt16												pad166;								// 166
	};
	STATIC_ASSERT(offsetof(PlayerCamera, cameraStates) == 0x0B8);
	STATIC_ASSERT(offsetof(PlayerCamera, worldFOV) == 0x13C);
	STATIC_ASSERT(offsetof(PlayerCamera, firstPersonFOV) == 0x140);
	STATIC_ASSERT(offsetof(PlayerCamera, pos) == 0x144);
	STATIC_ASSERT(sizeof(PlayerCamera) == 0x168);
}
