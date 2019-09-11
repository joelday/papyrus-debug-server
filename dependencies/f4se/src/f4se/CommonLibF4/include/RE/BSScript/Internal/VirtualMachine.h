#pragma once

#include "f4se/GameRTTI.h"  // RTTI_BSScript__Internal__VirtualMachine

#include "RE/BSScript/Internal/FunctionMessage.h"  // BSScript::Internal::FunctionMessage
#include "RE/BSScript/Internal/SuspendedStack.h"  // BSScript::Internal::SuspendedStack
#include "RE/BSScript/IVirtualMachine.h"  // BSScript::IVirtualMachine
#include "RE/BSScript/IVMDebugInterface.h"  // BSScript::IVMDebugInterface
#include "RE/BSScript/IVMObjectBindInterface.h"  // BSScript::IVMObjectBindInterface
#include "RE/BSScript/IVMSaveLoadInterface.h"  // BSScript::IVMSaveLoadInterface
#include "RE/BSScript/LinkerProcessor.h"  // BSScript::LinkerProcessor
#include "RE/BSLock.h"  // BSUniqueLock
#include "RE/BSTArray.h"  // BSTArray
#include "RE/BSTEvent.h"  // BSTEvent
#include "RE/BSTFreeList.h"  // BSTStaticFreeList
#include "RE/BSTHashMap.h"  // BSTHashMap
#include "RE/BSTMessageQueue.h"  // BSTCommonLLMessageQueue, BSTCommonStaticMessageQueue
#include "RE/BSTSmartPointer.h"  // BSTSmartPointer

namespace RE
{
	namespace BSScript
	{
		class Array;
		class ErrorLogger;
		class IFreezeQuery;
		class ISavePatcherInterface;
		class IStackCallbackFunctor;
		class IStackCallbackSaveInterface;
		class ObjectBindPolicy;
		class SimpleAllocMemoryPagePolicy;
		class Stack;
		struct IObjectHandlePolicy;
		struct StatsEvent;


		namespace Internal
		{
			class CodeTasklet;


			class VirtualMachine :
				public IVirtualMachine,				// 0000
				public IVMObjectBindInterface,		// 0010
				public IVMSaveLoadInterface,		// 0018
				public IVMDebugInterface,			// 0020
				public BSTEventSource<StatsEvent>	// 0028
			{
			public:
				inline static const void* RTTI = RTTI_BSScript__Internal__VirtualMachine;


				virtual ~VirtualMachine();

				// override (IVirtualMachine)
				virtual void	Unk_01() override;	// take m_lockC0 and then calls this+C8
				virtual void	Unk_02() override;	// take m_lockC0 and then sets m_unkE8
				virtual void	Unk_03() override;
				virtual void	Unk_04() override;
				virtual void	Unk_05() override;	// set m_unk82BC
				virtual void	Unk_06() override;	// take m_lockBDC4, return m_BDF4 & 2
				virtual void							RegisterForm(FormType32 a_formType, const char* a_papyrusClassName) override;																															// 08
				virtual void	Unk_08() override;
				virtual bool							GetScriptClassByName(const BSFixedString& a_className, BSTSmartPointer<ObjectTypeInfo>& a_outClassPtr) override;																									// 09
				virtual bool							GetScriptClassByTypeID(FormType32 a_formType, BSTSmartPointer<ObjectTypeInfo>& a_outClassPtr) override;																											// 0A
				virtual void	Unk_0B() override;
				virtual bool							GetFormTypeID(const BSFixedString& a_className, FormType32& a_formType) override;																														// 0D
				virtual void	Unk_0D() override;
				virtual void	Unk_0E() override;
				virtual void	Unk_0F() override;
				virtual void	Unk_10() override;
				virtual void	Unk_11() override;
				virtual void	Unk_12() override;
				virtual bool	GetStructTypeInfo(const BSFixedString& a_className, BSTSmartPointer<StructTypeInfo>& a_toClassPtr) override;	// Must release outTypeInfo explicitly
				virtual void	Unk_14() override;
				virtual void	Unk_15() override;
				virtual void	Unk_16() override;
				virtual bool							CreateScriptObject(const BSFixedString& a_className, BSTSmartPointer<Object>& a_result) override;																										// 15
				virtual bool	CreateStruct(const BSFixedString* name, BSTSmartPointer<Object>& a_result) override;
				virtual bool							CreateScriptArray(const Type& a_typeID, UInt32 a_size, BSTSmartPointer<Array>& a_arrayPtr) override;																										// 16
				virtual void	Unk_1A() override;
				virtual void							RegisterFunction(IFunction* a_fn) override;																																								// 18
				virtual void							SetFunctionFlagsEx(const char* a_className, UInt32 a_arg2, const char* a_fnName, FunctionFlag a_flags) override;																							// 19
				virtual void							SetFunctionFlags(const char* a_className, const char* a_fnName, FunctionFlag a_flags) override;																											// 1A
				virtual void							VisitScripts(VMHandle a_handle, IForEachScriptObjectFunctor* a_functor) override;																														// 1B
				virtual bool							ResolveScriptObject(VMHandle a_handle, const char* a_className, BSTSmartPointer<Object>& a_result) override;																								// 1C
				virtual void	Unk_20() override;
				virtual void	Unk_21() override;
				virtual bool							CastScriptObject(const BSTSmartPointer<Object>& a_fromObjPtr, const BSTSmartPointer<IComplexType>& a_toClassPtr, BSTSmartPointer<Object>& a_toObjPtr) override;													// 1F
				virtual bool							SetObjectProperty(BSTSmartPointer<Object>& a_obj, const char* a_propertyName, Variable& a_setVal) override;																								// 20
				virtual bool							GetObjectProperty(BSTSmartPointer<Object>& a_obj, const char* a_propertyName, Variable& a_getVal) override;																								// 21
				virtual bool							ExtractValue(const BSTSmartPointer<Object>& a_objPtr, UInt32 a_index, Variable& a_out) override;																											// 22
				virtual void	Unk_26() override;
				virtual void	Unk_27() override;
				virtual void	Unk_28() override;
				virtual void	Unk_29() override;
				virtual void	Unk_2A() override;
				virtual void							QueueEvent(VMHandle a_handle, const BSFixedString& a_eventName, IFunctionArguments* a_args) override;																									// 24
				virtual void	Unk_2C() override;
				virtual void	Unk_2D() override;
				virtual void	Unk_2E() override;
				virtual void	Unk_2F() override;
				virtual void	Unk_30() override;
				virtual void							SetLatentReturn(StackID a_stackID, const Variable& a_val) override;																																		// 2B
				virtual void	Unk_32() override;
				virtual IObjectHandlePolicy* GetHandlePolicy() override;																																												// 2D
				virtual void	Unk_34() override;
				virtual ObjectBindPolicy* GetObjectBindPolicy() override;																																											// 2F
				virtual void	Unk_36() override;
				virtual void	Unk_37() override;
				virtual void							AddLogEventSink(BSTEventSink<LogEvent>* a_sink) override;																																				// 32
				virtual void							RemoveLogEventSink(BSTEventSink<LogEvent>* a_sink) override;																																				// 33
				virtual void	Unk_3A() override;
				virtual void	Unk_3B() override;
				virtual void	Unk_3C() override;
				virtual void	Unk_3D() override;																																					// 35

				// override (IVMObjectBindInterface)
				virtual VMHandle						GetHandle(const BSTSmartPointer<Object>& a_objPtr) override;																																				// 01
				virtual void							BindObject(BSTSmartPointer<Object>& a_objPtr, VMHandle a_handle, bool a_conditional) override;																												// 03
				virtual void							RegisterObject(BSTSmartPointer<Object>& a_objPtr, VMHandle a_handle, bool a_conditional) override;																											// 04
				virtual bool							CreateObject(const BSFixedString& a_className, UInt32 a_numProperties, BSTSmartPointer<Object>& a_objPtr) override;																							// 09
				virtual bool							SetProperty(BSTSmartPointer<Object>& a_objPtr, void* a_property, bool a_arg3) override;																														// 0A

				static VirtualMachine* GetSingleton();

				bool					AllocateArray(const VMTypeID& a_typeID, std::size_t a_size, BSTSmartPointer<Array>& a_array);
				template <class F> void	RegisterFunction(const char* a_fnName, const char* a_className, F* a_callback, FunctionFlag a_flags = FunctionFlag::kNone);

				UInt64	pad08[(0xC0 - 0x08) >> 3];	// 08
				mutable BSUniqueLock								classLock;					// C0
				UInt64	padC8[(0xE8 - 0xC8) >> 3];	// C8
				UInt64	m_unkE8;					// E8

				BSTHashMap<BSFixedString, BSTSmartPointer<ObjectTypeInfo>>	linkedClassMap;				// 168
				BSTHashMap<BSFixedString, BSTSmartPointer<StructTypeInfo>>	linkedStructMap;			// 198
				BSTHashMap<FormType32, BSFixedString>				typeToClassNameMap;			// 1C8
				BSTHashMap<BSFixedString, FormType32>				classNameToTypeMap;			// 1F8

				UInt64	unk1F8[(0xBD58 - 0x228) >> 3];
				
				mutable BSUniqueLock								stackLock;					// BD58
				BSTHashMap<StackID, BSTSmartPointer<Stack>>			allStacks;					// BD60
				BSTHashMap<UInt32, UnkValue>						waitingStacks;				// BD90
				StackID												nextFreeStackID;			// ????

				// attachedScripts?
			};
			
			STATIC_ASSERT(offsetof(VirtualMachine, linkedClassMap) == 0x168);
			STATIC_ASSERT(offsetof(VirtualMachine, linkedStructMap) == 0x198);
			STATIC_ASSERT(offsetof(VirtualMachine, typeToClassNameMap) == 0x1C8);
			STATIC_ASSERT(offsetof(VirtualMachine, classNameToTypeMap) == 0x1F8);
			STATIC_ASSERT(offsetof(VirtualMachine, stackLock) == 0xBD58);
		}
	}
}
