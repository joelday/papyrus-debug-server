#pragma once

#include "f4se/GameRTTI.h"  // RTTI_BSScript__IVirtualMachine

#include "RE/BSScript/LogEvent.h"  // BSScript::LogEvent::Severity
#include "RE/BSIntrusiveRefCounted.h"  // BSIntrusiveRefCounted
#include "RE/BSTSmartPointer.h"  // BSTSmartPointer
#include "RE/BSTEvent.h"  // BSTEventSink
#include "ObjectTypeInfo.h"
#include "StructTypeInfo.h"


namespace RE
{
	class BSFixedString;


	namespace SkyrimScript
	{
		class HandlePolicy;
		class ObjectBindPolicy;
	}


	namespace BSScript
	{
		class Array;
		class ErrorLogger;
		class IForEachScriptObjectFunctor;
		class IFunction;
		class IFunctionArguments;
		class ISavePatcherInterface;
		class IStackCallbackFunctor;
		class Object;
		class ObjectBindPolicy;
		class Type;
		class Variable;
		struct IObjectHandlePolicy;
		struct LogEvent;
		struct StatsEvent;


		class IVirtualMachine : public BSIntrusiveRefCounted
		{
		public:
			inline static const void* RTTI = RTTI_BSScript__IVirtualMachine;


			using Severity = BSScript::LogEvent::Severity;
			using StackID = UInt32;


			enum class FunctionFlag : UInt32
			{
				kNone = 0,
				kNoWait = 1 << 0
			};


			virtual ~IVirtualMachine();	// 00

			// add
			virtual void	Unk_01() = 0;	// take m_lockC0 and then calls this+C8
			virtual void	Unk_02(UInt64 unk) = 0;	// take m_lockC0 and then sets m_unkE8
			virtual void	Unk_03() = 0;
			virtual void	Unk_04() = 0;
			virtual void	Unk_05(UInt8 unk) = 0;	// set m_unk82BC
			virtual void	Unk_06() = 0;	// take m_lockBDC4, return m_BDF4 & 2
			virtual void							RegisterForm(FormType32 a_formType, const char* a_papyrusClassName) = 0;																															// 08
			virtual void	Unk_08() = 0;
			virtual bool							GetScriptClassByName(const BSFixedString& a_className, BSTSmartPointer<ObjectTypeInfo>& a_outClassPtr) = 0;																									// 09
			virtual bool							GetScriptClassByTypeID(FormType32 a_formType, BSTSmartPointer<ObjectTypeInfo>& a_outClassPtr) = 0;																											// 0A
			virtual void	Unk_0B() = 0;
			virtual bool							GetFormTypeID(const BSFixedString& a_className, FormType32& a_formType) = 0;																														// 0D
			virtual void	Unk_0D() = 0;
			virtual void	Unk_0E() = 0;
			virtual void	Unk_0F() = 0;
			virtual void	Unk_10() = 0;
			virtual void	Unk_11() = 0;
			virtual void	Unk_12() = 0;
			virtual bool	GetStructTypeInfo(const BSFixedString& a_className, BSTSmartPointer<StructTypeInfo>& a_toClassPtr) = 0;	// Must release outTypeInfo explicitly
			virtual void	Unk_14() = 0;
			virtual void	Unk_15() = 0;
			virtual void	Unk_16() = 0;
			virtual bool							CreateScriptObject(const BSFixedString& a_className, BSTSmartPointer<Object>& a_result) = 0;																										// 15
			virtual bool	CreateStruct(const BSFixedString* name, BSTSmartPointer<Object>& a_result) = 0;
			virtual bool							CreateScriptArray(const Type& a_typeID, UInt32 a_size, BSTSmartPointer<Array>& a_arrayPtr) = 0;																										// 16
			// Really?: virtual bool	CreateArray(Variable* a_value, UInt32 a_size, BSTSmartPointer<Array>& a_arrayPtr);
			virtual void	Unk_1A() = 0;
			virtual void							RegisterFunction(IFunction* a_fn) = 0;																																								// 18
			virtual void							SetFunctionFlagsEx(const char* a_className, UInt32 a_arg2, const char* a_fnName, FunctionFlag a_flags) = 0;																							// 19
			virtual void							SetFunctionFlags(const char* a_className, const char* a_fnName, FunctionFlag a_flags) = 0;																											// 1A
			virtual void							VisitScripts(VMHandle a_handle, IForEachScriptObjectFunctor* a_functor) = 0;																														// 1B
			virtual bool							ResolveScriptObject(VMHandle a_handle, const char* a_className, BSTSmartPointer<Object>& a_result) = 0;																								// 1C
			virtual void	Unk_20() = 0;
			virtual void	Unk_21() = 0;
			virtual bool							CastScriptObject(const BSTSmartPointer<Object>& a_fromObjPtr, const BSTSmartPointer<IComplexType>& a_toClassPtr, BSTSmartPointer<Object>& a_toObjPtr) = 0;													// 1F
			virtual bool							SetObjectProperty(BSTSmartPointer<Object>& a_obj, const char* a_propertyName, Variable& a_setVal) = 0;																								// 20
			virtual bool							GetObjectProperty(BSTSmartPointer<Object>& a_obj, const char* a_propertyName, Variable& a_getVal) = 0;																								// 21
			virtual bool							ExtractValue(const BSTSmartPointer<Object>& a_objPtr, UInt32 a_index, Variable& a_out) = 0;																											// 22
			virtual void	Unk_26() = 0;
			virtual void	Unk_27() = 0;
			virtual void	Unk_28() = 0;
			virtual void	Unk_29() = 0;
			virtual void	Unk_2A() = 0;
			virtual void							QueueEvent(VMHandle a_handle, const BSFixedString& a_eventName, IFunctionArguments* a_args) = 0;																									// 24
			virtual void	Unk_2C() = 0;
			virtual void	Unk_2D() = 0;
			virtual void	Unk_2E() = 0;
			virtual void	Unk_2F() = 0;
			virtual void	Unk_30() = 0;
			virtual void							SetLatentReturn(StackID a_stackID, const Variable& a_val) = 0;																																		// 2B
			virtual void	Unk_32() = 0;
			virtual IObjectHandlePolicy* GetHandlePolicy() = 0;																																												// 2D
			virtual void	Unk_34() = 0;
			virtual ObjectBindPolicy* GetObjectBindPolicy() = 0;																																											// 2F
			virtual void	Unk_36() = 0;
			virtual void	Unk_37() = 0;
			virtual void							AddLogEventSink(BSTEventSink<LogEvent>* a_sink) = 0;																																				// 32
			virtual void							RemoveLogEventSink(BSTEventSink<LogEvent>* a_sink) = 0;																																				// 33
			virtual void	Unk_3A() = 0;
			virtual void	Unk_3B() = 0;
			virtual void	Unk_3C() = 0;
			virtual void	Unk_3D() = 0;

			// members
			UInt32 unk0C;	// 0C
		};
		STATIC_ASSERT(sizeof(IVirtualMachine) == 0x10);
	}
}
