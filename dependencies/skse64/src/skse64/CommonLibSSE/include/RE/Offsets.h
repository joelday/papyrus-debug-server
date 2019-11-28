#pragma once

#include <cstdint>  // uintptr_t


namespace RE
{
	namespace Offset
	{
		namespace ActivateHandler
		{
			// VTable: .?AUActivateHandler@@
			constexpr std::uintptr_t Vtbl = 0x0166F288;	// 1_5_97
		}


		namespace ActiveEffect
		{
			// IndirectSig: E8 ? ? ? ? 48 85 DB 75 C9
			constexpr std::uintptr_t Dispell = 0x0053E380;	// 1_5_97
		}


		namespace Actor
		{
			// IndirectSig: E8 ? ? ? ? 0F B6 F0 49 8D 4E 30
			constexpr std::uintptr_t AddSpell = 0x0062F560;						// 1_5_97
			// IndirectSig: E8 ? ? ? ? 41 8B CE 3B C1
			constexpr std::uintptr_t CalcEntryValue = 0x001D9080;				// 1_5_97
			// IndirectSig: E8 ? ? ? ? 49 8B D5 49 8B 8D ? ? ? ?
			constexpr std::uintptr_t DispelWornItemEnchantments = 0x00556F20;	// 1_5_97
			// IndirectSig: E8 ? ? ? ? 85 C0 7E 2D
			constexpr std::uintptr_t GetDetectionLevel = 0x005FC9A0;			// 1_5_97
			// IndirectSig: E8 ? ? ? ? F3 0F 58 43 5C
			constexpr std::uintptr_t GetHeight = 0x005E1300;					// 1_5_97
			// IndirectSig: E8 ? ? ? ? 84 C0 49 0F 45 F4
			constexpr std::uintptr_t IsGhost = 0x005D2520;						// 1_5_97
			// IndirectSig: E8 ? ? ? ? 48 8B CF 0F B6 E8
			constexpr std::uintptr_t IsRunning = 0x005D1190;					// 1_5_97
			// IndirectSig: E8 ? ? ? ? EB 1D 8B 4D 7F
			constexpr std::uintptr_t SendStealAlarm = 0x005DD770;				// 1_5_97
			// VTable: .?AVActor@@
			constexpr std::uintptr_t Vtbl = 0x01655640;							// 1_5_97
		}


		namespace ActorValueOwner
		{
			// IndirectSig: E8 ? ? ? ? F3 44 0F 2C C0
			constexpr std::uintptr_t GetPlayerActorValueCurrent = 0x003E5250;	// 1_5_97
		}


		namespace AttackBlockHandler
		{
			// VTable: .?AUAttackBlockHandler@@
			constexpr std::uintptr_t Vtbl = 0x0166F218;	// 1_5_97
		}


		namespace AutoMoveHandler
		{
			// VTable: .?AUAutoMoveHandler@@
			constexpr std::uintptr_t Vtbl = 0x0166F2C8;	// 1_5_97
		}


		namespace BaseExtraList
		{
			// IndirectSig: E8 ? ? ? ? 4C 8D 75 10
			constexpr std::uintptr_t Add = 0x00131990;					// 1_5_97
			// IndirectSig: E8 ? ? ? ? F7 43 28 FF 03 00 00 75 0C
			constexpr std::uintptr_t SetExtraFlags = 0x00125D80;		// 1_5_97
			// IndirectSig: E8 ? ? ? ? 90 41 89 1E 48 8B C7 48 8B 5C 24 60 48 8B 6C 24 68 48 83 C4 30 41 5E
			constexpr std::uintptr_t SetInventoryChanges = 0x0010F5C0;	// 1_5_97
		}


		namespace BGSDefaultObjectManager
		{
			// IndirectSig: E8 ? ? ? ? 4C 63 C3
			constexpr std::uintptr_t GetSingleton = 0x000F7210;	// 1_5_97
		}


		namespace BSAudioManager
		{
			// IndirectSig: E8 ? ? ? ? BA 33 00 00 00
			constexpr std::uintptr_t GetSingleton = 0x00BEE580;					// 1_5_97
			// IndirectSig: E8 ? ? ? ? C6 46 04 01
			constexpr std::uintptr_t BuildSoundDataFromDescriptor = 0x00BEF0B0;	// 1_5_97
		}


		namespace BSFixedStringW
		{
			// DirectSig: 40 53 48 83 EC 20 48 C7 01 00 00 00 00 4C 8B DA
			constexpr std::uintptr_t Ctor = 0x00C29510;	// 1_5_97
			// IndirectSig: E8 ? ? ? ? 4C 8D 45 C8 48 8D 55 D8
			constexpr std::uintptr_t Dtor = 0x00C29620;	// 1_5_97
		}


		namespace BSScaleformTranslator
		{
			// VTable: .?AVBSScaleformTranslator@@
			constexpr std::uintptr_t Vtbl = 0x017B6B50;	// 1_5_97
		}


		namespace BSScript
		{
			namespace Object
			{
				// IndirectSig: E8 ? ? ? ? 49 8B CE E8 ? ? ? ? 48 85 DB 74 08
				constexpr std::uintptr_t Dtor = 0x01233670;			// 1_5_97
				// IndirectSig: E8 ? ? ? ? 49 89 3F
				constexpr std::uintptr_t IncRefCount = 0x01234360;	// 1_5_97
				// IndirectSig: E8 ? ? ? ? 85 C0 75 10 49 8B CE
				constexpr std::uintptr_t DecRefCount = 0x01234410;	// 1_5_97
			}


			namespace Internal
			{
				namespace VirtualMachine
				{
					// IndirectSig: E8 ? ? ? ? 84 C0 0F 84 ? ? ? ? 48 83 7C 24 48 00
					constexpr std::uintptr_t AllocateArray = 0x01264EB0;	// 1_5_97
				}
			}


			namespace Stack
			{
				// IndirectSig: E8 ? ? ? ? BA A0 00 00 00 49 8B CF
				constexpr std::uintptr_t Dtor = 0x012444C0;	// 1_5_97
			}
		}


		namespace BSTimeManager
		{
			//
			constexpr std::uintptr_t Singleton = 0x01EC0A80;	// 1_5_97
		}


		namespace BSWin32SaveDataSystemUtility
		{
			// IndirectSig: E8 ? ? ? ? 4C 8B 18
			constexpr std::uintptr_t GetSingleton = 0x0133F0C0;	// 1_5_97
		}


		namespace ChestsLooted
		{
			// IndirectSig: E8 ? ? ? ? 48 8B C8 48 8D 54 24 51
			constexpr std::uintptr_t GetEventSource = 0x00862160;	// 1_5_97
		}


		namespace Condition
		{
			namespace Node
			{
				// IndirectSig: E8 ? ? ? ? 44 0F B6 C0 45 84 F6
				constexpr std::uintptr_t Run = 0x004454C0;	// 1_5_97
			}


			// IndirectSig: E8 ? ? ? ? 0F B6 D8 EB 08
			constexpr std::uintptr_t Run = 0x004447A0;	// 1_5_97
		}


		namespace Console
		{
			// IndirectSig: E8 ? ? ? ? BE 02 00 00 00 8B C6
			constexpr std::uintptr_t SetSelectedRef = 0x0085BB30;	// 1_5_97
		}


		namespace CRC32Calculator
		{
			// IndirectSig: E8 ? ? ? ? 8B 75 AB
			constexpr std::uintptr_t SizeOf32 = 0x00C064F0;		// 1_5_97
			// IndirectSig: E8 ? ? ? ? 8B 5D C0
			constexpr std::uintptr_t SizeOf64 = 0x00C06570;		// 1_5_97
			// IndirectSig: E8 ? ? ? ? 8B 9D B8 00 00 00
			constexpr std::uintptr_t SizeOfSize = 0x00C06490;	// 1_5_97
		}


		namespace DialogueData
		{
			// IndirectSig: E8 ? ? ? ? 48 8B F8 41 89 1E 48 8B C7 48 8B 5C 24 70
			constexpr std::uintptr_t Ctor = 0x0056C9D0;	// 1_5_97
		}


		namespace FavoritesHandler
		{
			// VTable: .?AUFavoritesHandler@@
			constexpr std::uintptr_t Vtbl = 0x016B84B8;	// 1_5_97
		}


		namespace FavoritesMenu
		{
			// VTable: .?AVFavoritesMenu@@
			constexpr std::uintptr_t Vtbl = 0x016B1068;	// 1_5_97
		}


		namespace FirstPersonState
		{
			// VTable: .?AVFirstPersonState@@
			constexpr std::uintptr_t Vtbl = 0x016A9E60;	// 1_5_97
		}


		namespace GFxLoader
		{
			// DirectSig: 45 8B D0 48 8B C1
			constexpr std::uintptr_t CreateMovie = 0x00EDBFA0;	// 1_5_97
		}


		namespace GFxMovieView
		{
			// IndirectSig: E8 ? ? ? ? C6 44 24 20 01 41 B9 03 00 00 00 44 8D 47 69
			constexpr std::uintptr_t InvokeNoReturn = 0x00ED80B0;	// 1_5_97
		}


		namespace GFxValue
		{
			namespace ObjectInterface
			{
				// DirectSig: 48 83 EC 28 45 8B D0
				constexpr std::uintptr_t RemoveElements = 0x00ECB6C0;	// 1_5_97
				// IndirectSig: E8 ? ? ? ? 80 BE FE 03 03 00 00
				constexpr std::uintptr_t SetArraySize = 0x00ECBD20;		// 1_5_97
				// IndirectSig: E8 ? ? ? ? FF C3 48 83 C6 18
				constexpr std::uintptr_t SetElement = 0x00ECC960;		// 1_5_97
			}
		}


		namespace GlobalLookupInfo
		{
			//
			constexpr std::uintptr_t Singleton = 0x01EC3CB0;	// 1_5_97
		}


		namespace GMemory
		{
			// GFxFunctionHandler::virt_dtor + 35
			constexpr std::uintptr_t GlobalHeap = 0x03032C50;	// 1_5_97
		}


		namespace hkContainerHeapAllocator
		{
			// 48 8D 0D ? ? ? ? 48 8B 93 C8 00 00 00
			constexpr std::uintptr_t Singleton = 0x01DF5E70;	// 1_5_97
		}


		namespace Inventory
		{
			// IndirectSig: E8 ? ? ? ? 48 8B C8 48 8D 54 24 58 E8 ? ? ? ? 49 8B 0F
			constexpr std::uintptr_t GetEventSource = 0x001EF330;	// 1_5_97
		}


		namespace InventoryChanges
		{
			// IndirectSig: E8 ? ? ? ? 48 8B F8 48 8B D7 48 8B CD
			constexpr std::uintptr_t Ctor = 0x001D9200;							// 1_5_97
			// IndirectSig: E8 ? ? ? ? 90 8B 44 24 68 41 89 06 48 83 C4 38
			constexpr std::uintptr_t GenerateLeveledListChanges = 0x001E08B0;	// 1_5_97
			// IndirectSig: E8 ? ? ? ? 40 84 F6 75 08
			constexpr std::uintptr_t InitContainer = 0x001E9D90;				// 1_5_97
			// IndirectSig: E8 ? ? ? ? 48 85 ED 74 3F
			constexpr std::uintptr_t SendContainerChangedEvent = 0x001ECE20;	// 1_5_97
		}


		namespace InventoryEntryData
		{
			// IndirectSig: E8 ? ? ? ? 84 C0 0F 85 ? ? ? ? 48 8B 3F
			constexpr std::uintptr_t IsOwnedBy = 0x001D7590;	// 1_5_97
		}


		namespace ItemCrafted
		{
			// IndirectSig: E8 ? ? ? ? 48 8B C8 48 8D 55 B8 E8 ? ? ? ? 45 85 E4
			constexpr std::uintptr_t GetEventSource = 0x008708A0;	// 1_5_97
		}


		namespace ItemList
		{
			// IndirectSig: E8 ? ? ? ? EB 4A 80 7D 1A 1B
			constexpr std::uintptr_t Update = 0x00856A50;	// 1_5_97
		}


		namespace ItemsPickpocketed
		{
			// IndirectSig: E8 ? ? ? ? 48 8B C8 48 8D 54 24 58 E8 ? ? ? ? EB 7B
			constexpr std::uintptr_t GetEventSource = 0x00862250;	// 1_5_97
		}


		namespace JumpHandler
		{
			// VTable: .?AUJumpHandler@@
			constexpr std::uintptr_t Vtbl = 0x0166F388;	// 1_5_97
		}


		namespace LockState
		{
			// IndirectSig: E8 ? ? ? ? 66 0F 6E C0 0F 5B C0 0F 5A C8 F2 0F 11 0F
			constexpr std::uintptr_t GetLockLevel = 0x00134A90;	// 1_5_97
		}


		namespace LookHandler
		{
			// VTable: .?AULookHandler@@
			constexpr std::uintptr_t Vtbl = 0x0166F140;	// 1_5_97
		}


		namespace MagicItem
		{
			// IndirectSig: E8 ? ? ? ? F3 0F 59 C6 B0 01
			constexpr std::uintptr_t CalculateTotalGoldValue = 0x00101A30;	// 1_5_97
		}


		namespace MagicTarget
		{
			// DirectSig: 48 89 5C 24 18 56 48 83 EC 20 48 8B 01 48 8B F2 FF 50 38
			constexpr std::uintptr_t HasMagicEffect = 0x005530D0;	// 1_5_97
		}


		namespace MenuOpenHandler
		{
			// VTable: .?AUMenuOpenHandler@@
			constexpr std::uintptr_t Vtbl = 0x016B8480;	// 1_5_97
		}


		namespace MessageDataFactoryManager
		{
			// IndirectSig: E8 ? ? ? ? 48 8B C8 48 8D 57 08
			constexpr std::uintptr_t GetSingleton = 0x00326460;	// 1_5_97
		}


		namespace MovementHandler
		{
			// VTable: .?AUMovementHandler@@
			constexpr std::uintptr_t Vtbl = 0x0166F1A8;	// 1_5_97
		}


		namespace NiControllerManager
		{
			// IndirectSig: E8 ? ? ? ? 48 8B E8 E8 ? ? ? ?
			constexpr std::uintptr_t GetSequenceByName = 0x00189B00;	// 1_5_97
		}


		namespace NiMemManager
		{
			// 48 89 44 24 30 48 89 05 ? ? ? ?
			constexpr std::uintptr_t Singleton = 0x02F77208;	// 1_5_97
		}


		namespace NiNode
		{
			// IndirectSig: E8 ? ? ? ? 44 88 65 6F
			constexpr std::uintptr_t SetMotionType = 0x00DA81E0;	// 1_5_97
		}


		namespace NiRefObject
		{
			// NiRefObject::virt_dtor + 13
			constexpr std::uintptr_t TotalObjectCount = 0x03012520;	// 1_5_97
		}


		namespace PlayerCharacter
		{
			namespace PlayerSkills
			{
				// IndirectSig: E8 ? ? ? ? 48 8B 15 ? ? ? ? 48 81 C2 40 01 00 00
				constexpr std::uintptr_t AdvanceLevel = 0x006E6740;	// 1_5_97
			}


			// 0F 94 C3 88 1D ? ? ? ?
			constexpr std::uintptr_t CollisionDisabled = 0x01EBEB50;	// 1_5_97
			// DirectSig: 48 83 EC 38 80 7C 24 70 00
			constexpr std::uintptr_t GetPickpocketChance = 0x003BCF40;	// 1_5_97
			// IndirectSig: E8 ? ? ? ? 44 89 65 67
			constexpr std::uintptr_t PlayPickupEvent = 0x0069FE60;		// 1_5_97
			// IndirectSig: E8 ? ? ? ? 66 C7 43 18 00 00
			constexpr std::uintptr_t StartActivation = 0x006A9F90;		// 1_5_97
			// IndirectSig: E8 ? ? ? ? 84 C0 75 08 40 32 F6
			constexpr std::uintptr_t TryToPickPocket = 0x006B2530;		// 1_5_97
			// VTable: .?AVPlayerCharacter@@
			constexpr std::uintptr_t Vtbl = 0x016635E0;					// 1_5_97
		}


		namespace ReadyWeaponHandler
		{
			// VTable: .?AUReadyWeaponHandler@@
			constexpr std::uintptr_t Vtbl = 0x0166F258;	// 1_5_97
		}


		namespace RunHandler
		{
			// VTable: .?AURunHandler@@
			constexpr std::uintptr_t Vtbl = 0x0166F328;	// 1_5_97
		}


		namespace Script
		{
			// DirectSig: 41 54 41 56 41 57 48 83 EC 40 48 C7 44 24 38 FE FF FF FF 48 89 5C 24 60 48 89 6C 24 68 48 89 74 24 70 48 89 7C 24 78 4D 8B F1
			constexpr std::uintptr_t Invoke = 0x002E75F0;	// 1_5_97
		}


		namespace ScriptEventSourceHolder
		{
			// IndirectSig: E8 ? ? ? ? 90 48 8B 45 D7 48 85 C0 74 1C
			constexpr std::uintptr_t SendActivateEvent = 0x002A2070;	// 1_5_97
		}


		namespace ShoutHandler
		{
			// VTable: .?AUShoutHandler@@
			constexpr std::uintptr_t Vtbl = 0x0166F3E8;	// 1_5_97
		}


		namespace Sky
		{
			// IndirectSig: E8 ? ? ? ? 48 8B 40 48
			constexpr std::uintptr_t GetSingleton = 0x00177790;	// 1_5_97
		}


		namespace SneakHandler
		{
			// VTable: .?AUSneakHandler@@
			constexpr std::uintptr_t Vtbl = 0x0166F3B8;	// 1_5_97
		}


		namespace SoundData
		{
			// IndirectSig: E8 ? ? ? ? EB 0E 84 C0
			constexpr std::uintptr_t Play = 0x00BED530;			// 1_5_97
			// IndirectSig: E8 ? ? ? ? F3 0F 10 5D 9F
			constexpr std::uintptr_t SetNode = 0x00BEDB10;		// 1_5_97
			// IndirectSig: E8 ? ? ? ? 4C 8D 7E 20
			constexpr std::uintptr_t SetPosition = 0x00BED920;	// 1_5_97
		}


		namespace SprintHandler
		{
			// VTable: .?AUSprintHandler@@
			constexpr std::uintptr_t Vtbl = 0x0166F1D8;	// 1_5_97
		}


		namespace TES
		{
			// 45 33 C9 48 8B 0D ? ? ? ? 48 C7 44 24 28 00 00 00 00
			constexpr std::uintptr_t Singleton = 0x02F26B20;	// 1_5_97
		}


		namespace TESFile
		{
			// IndirectSig: E8 ? ? ? ? 48 8B 07 EB CA
			constexpr std::uintptr_t Duplicate = 0x0017E4B0;				// 1_5_97
			// IndirectSig: E8 ? ? ? ? EB E0
			constexpr std::uintptr_t GetCurrentSubRecordType = 0x0017D910;	// 1_5_97
			// IndirectSig: E8 ? ? ? ? 3C 5E
			constexpr std::uintptr_t GetFormType = 0x0017D4C0;				// 1_5_97
			// IndirectSig: E8 ? ? ? ? 44 8B DB
			constexpr std::uintptr_t ReadData = 0x0017DA10;					// 1_5_97
			// IndirectSig: E8 ? ? ? ? 33 FF 8B B3 88 02 00 00
			constexpr std::uintptr_t Seek = 0x0017D550;						// 1_5_97
			// IndirectSig: E8 ? ? ? ? 49 83 C6 28
			constexpr std::uintptr_t SeekNextSubrecord = 0x0017D960;		// 1_5_97
		}


		namespace TESMemoryManager
		{
			// IndirectSig: E8 ? ? ? ? 3B 77 48
			constexpr std::uintptr_t Realloc = 0x00C024B0;	// 1_5_97
		}


		namespace TESNPC
		{
			// VTable: .?AVTESNPC@@
			constexpr std::uintptr_t Vtbl = 0x0159FCD0;	// 1_5_97
		}


		namespace TESObjectACTI
		{
			// VTable: .?AVTESObjectACTI@@
			constexpr std::uintptr_t Vtbl = 0x015576F0;	// 1_5_97
		}


		namespace TESObjectCONT
		{
			// VTable: .?AVTESObjectCONT@@
			constexpr std::uintptr_t Vtbl = 0x01559930;	// 1_5_97
		}


		namespace TESObjectREFR
		{
			// IndirectSig: E8 ? ? ? ? 48 8B 4E 40 48 8B 01 8B 55 77
			constexpr std::uintptr_t ActivateRefChildren = 0x002A8CC0;	// 1_5_97
			// IndirectSig: E8 ? ? ? ? 8B 7B 14
			constexpr std::uintptr_t GetInventoryChanges = 0x001D8E40;	// 1_5_97
			// IndirectSig: E8 ? ? ? ? FF 40 18
			constexpr std::uintptr_t GetLockState = 0x002A74C0;			// 1_5_97
			// IndirectSig: E8 ? ? ? ? 85 C0 48 8B CB
			constexpr std::uintptr_t GetNumItems = 0x0028E250;			// 1_5_97
			// IndirectSig: E8 ? ? ? ? 48 3B D8 75 08
			constexpr std::uintptr_t GetOwner = 0x002A6670;				// 1_5_97
			// IndirectSig: E8 ? ? ? ? 41 B4 01 EB 1B
			constexpr std::uintptr_t PlayAnimation = 0x00189E30;		// 1_5_97
		}


		namespace ThirdPersonState
		{
			// VTable: .?AVThirdPersonState@@
			constexpr std::uintptr_t Vtbl = 0x0162F2A0;	// 1_5_97
		}


		namespace TogglePOVHandler
		{
			// VTable: .?AUTogglePOVHandler@@
			constexpr std::uintptr_t Vtbl = 0x0166F418;	// 1_5_97
		}


		namespace ToggleRunHandler
		{
			// VTable: .?AUToggleRunHandler@@
			constexpr std::uintptr_t Vtbl = 0x0166F2F8;	// 1_5_97
		}


		// IndirectSig: E8 ? ? ? ? 83 FE 0C
		constexpr std::uintptr_t DebugNotification = 0x008DA3D0;	// 1_5_97
		// IndirectSig: E8 ? ? ? ? 44 38 7E 50
		constexpr std::uintptr_t PlaySound = 0x008DA860;			// 1_5_97
		// IndirectSig: E8 ? ? ? ? 48 8B F5
		constexpr std::uintptr_t RTDynamicCast = 0x0134BDB0;		// 1_5_97
		// DirectSig: 48 83 EC 18 F3 41 0F 10 60 04
		constexpr std::uintptr_t WorldPtToScreenPt3 = 0x00C66580;	// 1_5_97
	}
}
