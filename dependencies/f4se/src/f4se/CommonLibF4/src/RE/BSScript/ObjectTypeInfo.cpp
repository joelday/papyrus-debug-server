#include "RE/BSScript/ObjectTypeInfo.h"

#include "f4se/PapyrusVM.h"  // VMObjectTypeInfo


namespace RE
{
	namespace BSScript
	{
		BSFixedString ObjectTypeInfo::ScriptFlag::GetFlag() const
		{
			auto sanitizedType = flag & ~kUnkFlag;
			return *reinterpret_cast<BSFixedString*>(&sanitizedType);
		}


		UInt32 ObjectTypeInfo::ScriptState::GetNumFuncs() const
		{
			return data & kFuncCountMask;
		}


		auto ObjectTypeInfo::ScriptState::GetFuncIter()
			-> Func*
		{
			return reinterpret_cast<Func*>((std::uintptr_t)this + (data >> kFuncOffsetShift));
		}


		auto ObjectTypeInfo::ScriptState::GetFuncIter() const
			-> const Func*
		{
			return reinterpret_cast<const Func*>((std::uintptr_t)this + (data >> kFuncOffsetShift));
		}


		const char* ObjectTypeInfo::GetName() const
		{
			return name.c_str();
		}


		VMTypeID ObjectTypeInfo::GetTypeID() const
		{
			return unrestricted_cast<VMTypeID>(this);
		}
		

		UInt32 ObjectTypeInfo::GetNumGroups() const
		{
			return numGroups;
		}

		auto ObjectTypeInfo::GetGroupIter()
			-> ScriptPropertyGroup*
		{
			return *groups;
		}

		auto ObjectTypeInfo::GetGroupIter() const
			-> const ScriptPropertyGroup*
		{
			return *groups;
		}

		
		bool ObjectTypeInfo::IsInherited() const
		{
			return inherited;
		}


		bool ObjectTypeInfo::IsRemoved() const
		{
			return removed;
		}

		
		auto ObjectTypeInfo::GetFunctionIter()
			-> Function*
		{
			return reinterpret_cast<Function*>(data);
		}


		auto ObjectTypeInfo::GetFunctionIter() const
			-> const Function*
		{
			return reinterpret_cast<const Function*>(data);
		}


		UInt32 ObjectTypeInfo::GetNumFlags() const
		{
			return pun_bits(numFlags1, numFlags2, numFlags3, numFlags4, numFlags5);
		}


		auto ObjectTypeInfo::GetFlagIter()
			-> ScriptFlag*
		{
			return reinterpret_cast<ScriptFlag*>(data);
		}


		auto ObjectTypeInfo::GetFlagIter() const
			-> const ScriptFlag*
		{
			return reinterpret_cast<const ScriptFlag*>(data);
		}


		UInt32 ObjectTypeInfo::GetNumVariables() const
		{
			return pun_bits(numVariables1, numVariables2, numVariables3, numVariables4, numVariables5, numVariables6, numVariables7, numVariables8, numVariables9, numVariables10);
		}


		UInt32 ObjectTypeInfo::GetTotalNumVariables() const
		{
			auto numVars = GetNumVariables();
			for (auto iter = parent; iter; iter = iter->parent) {
				numVars += iter->GetNumVariables();
			}
			return numVars;
		}


		auto ObjectTypeInfo::GetVariableIter()
			-> ScriptVariable*
		{
			return reinterpret_cast<ScriptVariable*>(GetFlagIter() + GetNumFlags());
		}


		auto ObjectTypeInfo::GetVariableIter() const
			-> const ScriptVariable*
		{
			return reinterpret_cast<const ScriptVariable*>(GetFlagIter() + GetNumFlags());
		}


		UInt32 ObjectTypeInfo::GetNumDefaultValues() const
		{
			return pun_bits(numDefaultValues1, numDefaultValues2, numDefaultValues3, numDefaultValues4, numDefaultValues5, numDefaultValues6, numDefaultValues7, numDefaultValues8, numDefaultValues9, numDefaultValues10);
		}


		auto ObjectTypeInfo::GetDefaultValueIter()
			-> DefaultScriptValue*
		{
			return reinterpret_cast<DefaultScriptValue*>(GetVariableIter() + GetNumVariables());
		}


		auto ObjectTypeInfo::GetDefaultValueIter() const
			-> const DefaultScriptValue*
		{
			return reinterpret_cast<const DefaultScriptValue*>(GetVariableIter() + GetNumVariables());
		}


		UInt32 ObjectTypeInfo::GetNumProperties() const
		{
			return pun_bits(numProperties1, numProperties2, numProperties3, numProperties4, numProperties5, numProperties6, numProperties7, numProperties8, numProperties9, numProperties10);
		}


		auto ObjectTypeInfo::GetPropertyIter()
			-> ScriptProperty*
		{
			return reinterpret_cast<ScriptProperty*>(GetDefaultValueIter() + GetNumDefaultValues());
		}


		auto ObjectTypeInfo::GetPropertyIter() const
			-> const ScriptProperty*
		{
			return reinterpret_cast<const ScriptProperty*>(GetDefaultValueIter() + GetNumDefaultValues());
		}


		UInt32 ObjectTypeInfo::GetNumGlobalFuncs() const
		{
			return pun_bits(numGlobalFuncs1, numGlobalFuncs2, numGlobalFuncs3, numGlobalFuncs4, numGlobalFuncs5, numGlobalFuncs6, numGlobalFuncs7, numGlobalFuncs8, numGlobalFuncs9);
		}


		auto ObjectTypeInfo::GetGlobalFuncIter()
			-> ScriptGlobalFunc*
		{
			return reinterpret_cast<ScriptGlobalFunc*>(GetPropertyIter() + GetNumProperties());
		}


		auto ObjectTypeInfo::GetGlobalFuncIter() const
			-> const ScriptGlobalFunc*
		{
			return reinterpret_cast<const ScriptGlobalFunc*>(GetPropertyIter() + GetNumProperties());
		}


		UInt32 ObjectTypeInfo::GetNumMemberFuncs() const
		{
			return pun_bits(numMemberFuncs1, numMemberFuncs2, numMemberFuncs3, numMemberFuncs4, numMemberFuncs5, numMemberFuncs6, numMemberFuncs7, numMemberFuncs8, numMemberFuncs9, numMemberFuncs10, numMemberFuncs11);
		}


		auto ObjectTypeInfo::GetMemberFuncIter()
			-> ScriptMemberFunc*
		{
			return reinterpret_cast<ScriptMemberFunc*>(GetGlobalFuncIter() + GetNumGlobalFuncs());
		}


		auto ObjectTypeInfo::GetMemberFuncIter() const
			-> const ScriptMemberFunc*
		{
			return reinterpret_cast<const ScriptMemberFunc*>(GetGlobalFuncIter() + GetNumGlobalFuncs());
		}


		UInt32 ObjectTypeInfo::GetNumStates() const
		{
			return pun_bits(numStates1, numStates2, numStates3, numStates4, numStates5, numStates6, numStates7);
		}


		auto ObjectTypeInfo::GetStateIter()
			-> ScriptState*
		{
			return reinterpret_cast<ScriptState*>(GetMemberFuncIter() + GetNumMemberFuncs());
		}


		auto ObjectTypeInfo::GetStateIter() const
			-> const ScriptState*
		{
			return reinterpret_cast<const ScriptState*>(GetMemberFuncIter() + GetNumMemberFuncs());
		}


		UInt32 ObjectTypeInfo::GetPropertyIndex(const BSFixedString& a_name) const
		{
			auto prop = GetPropertyIter();
			for (UInt32 i = 0; i < GetNumVariables(); ++i) {
				if (prop->name == a_name) {
					return prop->idx;
				}
			}
			return static_cast<UInt32>(-1);
		}


		//void ObjectTypeInfo::Dtor()
		//{
		//	// TODO: ???
		//	//using func_t = function_type_t<decltype(&ObjectTypeInfo::Dtor)>;
		//	//func_t* func = EXTRACT_F4SE_MEMBER_FN_ADDR(::VMObjectTypeInfo, Destroy, func_t*);
		//	//return func(this);
		//}
	}
}
