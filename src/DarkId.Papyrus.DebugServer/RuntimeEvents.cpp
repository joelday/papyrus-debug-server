#define XBYAK_NO_OP_NAMES

#include "RuntimeEvents.h"

#include "xbyak/xbyak.h"

#if SKYRIM
#include <SKSE/Impl/PCH.h>
#include <skse64_common/SafeWrite.h>
#include <skse64_common/BranchTrampoline.h>
#include <common/ITypes.h>
#include <SKSE/Events.h>
#include <RE/B/BSTEvent.h>
#include <REL/Relocation.h>
#elif FALLOUT
#include <f4se_common/SafeWrite.h>
#include <f4se_common/BranchTrampoline.h>
#endif

#include <cassert>
#include <mutex>
// TODO: !!!!Change Offset to RELOCATION_ID
// See REL/Relocation.h
namespace DarkId::Papyrus::DebugServer
{
	namespace RuntimeEvents
	{
#define EVENT_WRAPPER_IMPL(NAME, HANDLER_SIGNATURE) \
		eventpp::CallbackList<HANDLER_SIGNATURE> g_##NAME##Event; \
		\
		NAME##EventHandle SubscribeTo##NAME(std::function<HANDLER_SIGNATURE> handler) \
		{ \
			return g_##NAME##Event.append(handler); \
		} \
		\
		bool UnsubscribeFrom##NAME(NAME##EventHandle handle) \
		{ \
			return g_##NAME##Event.remove(handle); \
		} \

		EVENT_WRAPPER_IMPL(InstructionExecution, void(RE::BSScript::Internal::CodeTasklet*, RE::BSScript::Internal::CodeTasklet::OpCode))
		EVENT_WRAPPER_IMPL(CreateStack, void(RE::BSTSmartPointer<RE::BSScript::Stack>&))
		EVENT_WRAPPER_IMPL(CleanupStack, void(uint32_t))
		// EVENT_WRAPPER_IMPL(InitScript, void(RE::TESInitScriptEvent*))
		EVENT_WRAPPER_IMPL(Log, void(const RE::BSScript::LogEvent*))

#undef EVENT_WRAPPER_IMPL
		
		//class ScriptInitEventSink : public RE::BSTEventSink<RE::TESInitScriptEvent>
		//{
		//	RE::EventResult ReceiveEvent(RE::TESInitScriptEvent* evn, RE::BSTEventSource<RE::TESInitScriptEvent>* a_eventSource) override
		//	{
		//		g_InitScriptEvent(evn);

		//		return RE::EventResult::kContinue;
		//	};
		//};

		class LogEventSink : public RE::BSTEventSink<RE::BSScript::LogEvent>
		{
			using EventResult = RE::BSEventNotifyControl;

			// TODO: I have no idea why this Intellisense is bitching about this, this seems to have the correct argument types
			EventResult ProcessEvent(const RE::BSScript::LogEvent* a_event, RE::BSTEventSource<RE::BSScript::LogEvent>*) override
			{
				g_LogEvent(a_event);

				return RE::BSEventNotifyControl::kContinue;
			};
		};

#if SKYRIM

		void InstructionExecute_Hook(RE::BSScript::Internal::CodeTasklet* a_tasklet, RE::BSScript::Internal::CodeTasklet::OpCode a_opCode)
		{
			if (a_tasklet->topFrame)
			{
				g_InstructionExecutionEvent(a_tasklet, a_opCode);
			}
		}

		void CreateStack_Hook(RE::BSTSmartPointer<RE::BSScript::Stack>& a_stack)
		{
			if (&a_stack && a_stack._ptr)
			{
				g_CreateStackEvent(a_stack);
			}
		}

		using CleanupStack_t = void(RE::BSScript::Internal::VirtualMachine*, RE::BSScript::Stack*);
		CleanupStack_t* _CleanupStack = 0;

		void CleanupStack_Hook(RE::BSScript::Internal::VirtualMachine* a_vm, RE::BSScript::Stack* a_stack)
		{
			if (a_stack) {
				const auto stackID = a_stack->stackID;
				_CleanupStack(a_vm, a_stack);

				g_CleanupStackEvent(stackID);
			}
		}

		namespace Internal
		{
			void CommitHooks()
			{
				{
					// OLD: E8 ? ? ? ? 48 83 C3 08 48 3B DF 75 EF 48 83 7C 24 30 00
					constexpr std::uintptr_t FUNC_ADDR = 0x01278110;	// 1_5_97
					constexpr std::size_t CAVE_START = 0x170;
					constexpr std::size_t CAVE_END = 0x176;
					constexpr std::size_t CAVE_SIZE = CAVE_END - CAVE_START;
// TODO: RELOCATION_ID
					REL::Offset funcBase(FUNC_ADDR);

					struct Patch : Xbyak::CodeGenerator
					{
						Patch(void* a_buf, std::size_t a_callAddr, std::size_t a_retAddr) : Xbyak::CodeGenerator(1024, a_buf)
						{
							Xbyak::Label callLbl;
							Xbyak::Label retLbl;

							push(rax);	// save volatile registers
							push(rcx);
							push(rdx);
							push(r8);
							push(r9);
							push(r10);
							push(r11);
							push(r11);

							mov(rcx, rdi);	// rdi == BSScript::Internal::CodeTasklet*
							mov(r8d, edx);	// edx == BSScript::Internal::CodeTasklet::OpCode
							xor_(rdx, rdx);
							mov(edx, r8d);

							sub(rsp, 0x20);	// pad the stack
							call(ptr[rip + callLbl]);	// make call
							add(rsp, 0x20);

							pop(r11);
							pop(r11);
							pop(r10);
							pop(r9);
							pop(r8);
							pop(rdx);
							pop(rcx);
							pop(rax);

							mov(rax, r8);	// execute overridden ops
							and_(eax, 0x3F);

							jmp(ptr[rip + retLbl]);	// resume execution

							L(callLbl);
							dq(a_callAddr);

							L(retLbl);
							dq(a_retAddr);
						}
					};

					void* patchBuf = g_localTrampoline.StartAlloc();
					Patch patch(patchBuf, SKSE::stl::unrestricted_cast<std::uintptr_t>(InstructionExecute_Hook), funcBase.address() + CAVE_END);
					g_localTrampoline.EndAlloc(patch.getCurr());

					assert(CAVE_SIZE == 6);

					g_branchTrampoline.Write6Branch(funcBase.address() + CAVE_START, reinterpret_cast<std::uintptr_t>(patch.getCode()));
				}

				{
					// OLD: E8 ? ? ? ? 48 8B 5C 24 38 48 85 DB 74 19
					constexpr std::uintptr_t FUNC_ADDR = 0x012641F0;	// 1_5_97
					constexpr std::size_t HOOK_TARGET = 0x1D4;
// TODO: RELOCATION_ID
					REL::Offset funcBase(FUNC_ADDR);

					struct Patch : Xbyak::CodeGenerator
					{
						Patch(void* a_buf, std::size_t a_funcAddr) : Xbyak::CodeGenerator(1024, a_buf)
						{
							Xbyak::Label funcLbl;

							mov(rcx, ptr[rsp - 0x448]);	// rsp - 0x448 == BSTSmartPointer<BSScript::Stack>&
							jmp(ptr[rip + funcLbl]);

							L(funcLbl);
							dq(a_funcAddr);
						}
					};

					void* patchBuf = g_localTrampoline.StartAlloc();
					Patch patch(patchBuf, SKSE::stl::unrestricted_cast<std::uintptr_t>(CreateStack_Hook));
					g_localTrampoline.EndAlloc(patch.getCurr());

					g_branchTrampoline.Write5Branch(funcBase.address() + HOOK_TARGET, reinterpret_cast<std::uintptr_t>(patch.getCode()));
				}


				{
					// OLD: E8 ? ? ? ? 90 48 85 DB 74 24 41 8B C7
					constexpr std::uintptr_t FUNC_ADDR = 0x012646F0;	// 1_5_97
					constexpr std::size_t CAVE_START = 0x0;
					constexpr std::size_t CAVE_END = 0x9;
					constexpr std::size_t CAVE_SIZE = CAVE_END - CAVE_START;
					constexpr uint8_t NOP = 0x90;
// TODO: RELOCATION_ID
					REL::Offset funcBase(FUNC_ADDR);

					struct Patch : Xbyak::CodeGenerator
					{
						Patch(void* a_buf, std::size_t a_funcAddr) : Xbyak::CodeGenerator(1024, a_buf)
						{
							Xbyak::Label funcLbl;

							jmp(ptr[rip + funcLbl]);

							L(funcLbl);
							dq(a_funcAddr);
						}
					};

					void* patchBuf = g_localTrampoline.StartAlloc();
					Patch patch(patchBuf, SKSE::stl::unrestricted_cast<std::uintptr_t>(CleanupStack_Hook));
					g_localTrampoline.EndAlloc(patch.getCurr());

					assert(CAVE_SIZE >= 6);

					g_branchTrampoline.Write6Branch(funcBase.address() + CAVE_START, reinterpret_cast<std::uintptr_t>(patch.getCode()));

					for (uint8_t i = CAVE_START + 6; i < CAVE_END; ++i) {
						SafeWrite8(funcBase.address() + i, NOP);
					}

					_CleanupStack = reinterpret_cast<CleanupStack_t*>(funcBase.address() + CAVE_END);
				}

				RE::BSScript::Internal::VirtualMachine::GetSingleton()->RegisterForLogEvent(new LogEventSink());
				// RE::ScriptEventSourceHolder::GetSingleton()->AddEventSink(new ScriptInitEventSink());
			}
		}
#elif FALLOUT

		RelocAddr<uintptr_t> InstructionExecute(0x0276eadd);

		void InstructionExecute_Hook(RE::BSScript::Internal::CodeTasklet* tasklet, RE::BSScript::Internal::CodeTasklet::OpCode opCode)
		{
			if (tasklet->stackFrame)
			{
				g_InstructionExecutionEvent(tasklet, opCode);
			}
		}

		typedef bool (*_CreateStack)(RE::BSScript::Internal::VirtualMachine* vm, UInt64 unk1, UInt64 unk2, UInt64 unk3, RE::BSTSmartPointer<RE::BSScript::Stack>& stack);
		RelocAddr<_CreateStack> CreateStack(0x02742070);
		_CreateStack CreateStack_Original = nullptr;

		bool CreateStack_Hook(RE::BSScript::Internal::VirtualMachine* vm, UInt64 unk1, UInt64 unk2, UInt64 unk3, RE::BSTSmartPointer<RE::BSScript::Stack>& stack)
		{
			bool result = CreateStack_Original(vm, unk1, unk2, unk3, stack);

			if (result)
			{
				g_CreateStackEvent(stack);
			}

			return result;
		}

		typedef void (*_CleanupStack)(RE::BSScript::Internal::VirtualMachine* vm, RE::BSScript::Stack* stack);
		RelocAddr<_CleanupStack> CleanupStack(0x02742610);
		_CleanupStack CleanupStack_Original = nullptr;

		void CleanupStack_Hook(RE::BSScript::Internal::VirtualMachine* vm, RE::BSScript::Stack* stack)
		{
			if (!stack)
			{
				return;
			}

			CleanupStack_Original(vm, stack);
			g_CleanupStackEvent(stack->stackID);
		}

		namespace Internal
		{
			void CommitHooks()
			{
				{
					struct InstructionExecute_Code : Xbyak::CodeGenerator {
						InstructionExecute_Code(void* buf, uintptr_t funcAddr) : Xbyak::CodeGenerator(4096, buf)
						{
							Xbyak::Label funcLabel;
							Xbyak::Label retnLabel;

							and_(edx, 0x3f);
							and_(eax, 0x3f);
							mov(dword[rbp + 0x30], edx);
							mov(qword[rbp - 0x38], rax);
							lea(rax, ptr[r9 + r8 * 8]);
							mov(qword[rbp - 0x40], rax);

							push(rax);
							push(rcx);
							push(rdx);
							push(r8);
							push(r9);
							push(r10);
							push(r11);
							push(r11);

							mov(rcx, rdi);
							mov(rdx, dword[rbp + 0x30]);

							sub(rsp, 0x20);
							call(ptr[rip + funcLabel]);
							add(rsp, 0x20);

							pop(r11);
							pop(r11);
							pop(r10);
							pop(r9);
							pop(r8);
							pop(rdx);
							pop(rcx);
							pop(rax);

							jmp(ptr[rip + retnLabel]);

							L(funcLabel);
							dq(funcAddr);

							L(retnLabel);
							dq(InstructionExecute + 0x15);
						}
					};

					void* codeBuf = g_localTrampoline.StartAlloc();
					InstructionExecute_Code code(codeBuf, (uintptr_t)InstructionExecute_Hook);
					g_localTrampoline.EndAlloc(code.getCurr());

					g_branchTrampoline.Write6Branch(InstructionExecute, uintptr_t(code.getCode()));
				}

				{
					struct CreateStack_Code : Xbyak::CodeGenerator {
						CreateStack_Code(void* buf) : Xbyak::CodeGenerator(4096, buf)
						{
							Xbyak::Label retnLabel;

							mov(ptr[rsp + 0x10], rbx);

							jmp(ptr[rip + retnLabel]);

							L(retnLabel);
							dq(CreateStack.GetUIntPtr() + 5);
						}
					};

					void* codeBuf = g_localTrampoline.StartAlloc();
					CreateStack_Code code(codeBuf);
					g_localTrampoline.EndAlloc(code.getCurr());

					CreateStack_Original = (_CreateStack)codeBuf;

					g_branchTrampoline.Write5Branch(CreateStack.GetUIntPtr(), (uintptr_t)CreateStack_Hook);
				}

				{
					struct CleanupStack_Code : Xbyak::CodeGenerator {
						CleanupStack_Code(void* buf) : Xbyak::CodeGenerator(4096, buf)
						{
							Xbyak::Label retnLabel;
							Xbyak::Label jmpLabel;

							jmp(ptr[rip + retnLabel]);

							L(retnLabel);
							dq(CleanupStack.GetUIntPtr() + 9);
						}
					};

					void* codeBuf = g_localTrampoline.StartAlloc();
					CleanupStack_Code code(codeBuf);
					g_localTrampoline.EndAlloc(code.getCurr());

					CleanupStack_Original = (_CleanupStack)codeBuf;

					g_branchTrampoline.Write5Branch(CleanupStack.GetUIntPtr(), (uintptr_t)CleanupStack_Hook);
				}

				RE::BSScript::Internal::VirtualMachine::GetSingleton()->AddLogEventSink(new LogEventSink());
				
				//GetEventDispatcher<TESInitScriptEvent>()->AddEventSink(
				//	reinterpret_cast<BSTEventSink<TESInitScriptEvent>*>(new ScriptInitEventSink()));
			}
		}
#endif
		
	}
}
