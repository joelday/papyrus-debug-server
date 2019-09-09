#include "RE/BSScript/Stack.h"

#include "f4se/PapyrusArgs.h"  // VMArgList

#include "RE/BSScript/Internal/CodeTasklet.h"  // BSScript::Internal::CodeTasklet
#include "RE/BSScript/IStackCallbackFunctor.h"  // BSScript::IStackCallbackFunctor
#include "RE/Offset.h"
#include "REL/Relocation.h"


namespace RE
{
	namespace BSScript
	{
		Stack::~Stack()
		{
			dtor();
			memzero(this);
		}


		StackFrame* Stack::Chunk::GetStackFrame()
		{
			return reinterpret_cast<StackFrame*>(buf);
		}


		UInt32 Stack::GetChunkIdx(StackFrame* a_frame)
		{
			using func_t = function_type_t<decltype(&Stack::GetChunkIdx)>;
			func_t* func = EXTRACT_F4SE_MEMBER_FN_ADDR(::VMArgList, GetOffset, func_t*);
			return func(this, a_frame);
		}


		Variable* Stack::Get(StackFrame* a_frame, UInt32 a_idx, UInt32 a_chunkIdx)
		{
			using func_t = function_type_t<decltype(&Stack::Get)>;
			func_t* func = EXTRACT_F4SE_MEMBER_FN_ADDR(::VMArgList, Get, func_t*);
			return func(this, a_frame, a_idx, a_chunkIdx);
		}


		void Stack::dtor()
		{
			// TODO: ???
			
			//using func_t = function_type_t<decltype(&Stack::dtor)>;
			//REL::Offset<func_t*> func(Offset::BSScript::Stack::Dtor);
			//return func(this);
		}
	}
}
