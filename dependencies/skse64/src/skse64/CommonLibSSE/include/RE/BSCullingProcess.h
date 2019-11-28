#pragma once

#include "skse64/GameRTTI.h"  // RTTI_BSCullingProcess
#include "skse64/NiRTTI.h"  // NiRTTI_BSCullingProcess

#include "RE/BSTArray.h"  // BSTArray
#include "RE/BSTLocklessQueue.h"  // BSTLocklessQueue
#include "RE/NiCullingProcess.h"  // NiCullingProcess
#include "RE/NiSmartPointer.h"  // NiPointer


namespace RE
{
	class BSCompoundFrustum;
	class BSMultiBound;
	class BSOcclusionPlane;
	class NiAVObject;
	class NiBound;


	class BSCullingProcess : public NiCullingProcess
	{
	public:
		inline static const void* RTTI = RTTI_BSCullingProcess;
		inline static const void* Ni_RTTI = NiRTTI_BSCullingProcess;


		struct Data
		{
			UInt8 unk00[0x10];	// 00
		};
		STATIC_ASSERT(sizeof(Data) == 0x10);


		// override (NiCullingProcess)
		virtual const NiRTTI*	GetRTTI() const override;																		// 00

		virtual ~BSCullingProcess();																							// 15

		virtual void			Process(NiAVObject* a_object, UInt32 a_arg2) override;											// 16
		virtual void			Process(const NiCamera* a_camera, NiAVObject* a_scene, NiVisibleArray* a_visibleSet) override;	// 17
		virtual void			AppendVirtual(BSGeometry* a_visible, UInt32 a_arg2) override;									// 18

		// add
		virtual void			AppendNonAccum(NiAVObject* a_object);															// 19
		virtual bool			TestBaseVisibility1(class BSMultiBound& a_bound);												// 1A
		virtual bool			TestBaseVisibility2(class BSOcclusionPlane& a_bound);											// 1B
		virtual bool			TestBaseVisibility3(NiBound& a_bound);															// 1C


		BSTArray<NiPointer<NiAVObject>>						unk00128;			// 00128
		BSTLocklessQueue::ObjMultiProdCons<Data, 4096, 0>	cullQueue;			// 00140
		UInt64												unk30160;			// 30160
		UInt64												unk30168;			// 30168
		UInt64												unk30170;			// 30170
		UInt64												unk30178;			// 30178
		UInt64												unk30180;			// 30180
		UInt64												unk30188;			// 30188
		void*												unk30190;			// 30190
		SInt32												cullMode;			// 30198
		BSCompoundFrustum*									compoundFrustum;	// 301A0
		UInt64												unk301A8;			// 301A8
		UInt64												unk301B0;			// 301B0
		UInt64												unk301B8;			// 301B8
		UInt64												unk301C0;			// 301C0
		UInt64												unk301C8;			// 301C8
		UInt32												unk301D0;			// 301D0
		bool												recurseToGeometry;	// 301D4
		UInt8												unk301D5;			// 301D5
		UInt16												unk301D6;			// 301D6
		BSTArray<void*>										unk301D8;			// 301D8
		UInt64												unk301F0;			// 301F0
	};
	STATIC_ASSERT(sizeof(BSCullingProcess) == 0x301F8);
}
