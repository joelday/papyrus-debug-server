#define XBYAK_NO_OP_NAMES

#include "RuntimeEvents.h"

#include "f4se_common/BranchTrampoline.h"
#include "xbyak/xbyak.h"

#include "f4se_common/Relocation.h"

#include "f4se/PluginAPI.h"
#include "f4se/PapyrusVM.h"
#include "f4se/PapyrusNativeFunctions.h"

#include "f4se_common/SafeWrite.h"

#include <mutex>

namespace DarkId::Papyrus::DebugServer

{
    namespace RuntimeEvents
    {
        eventpp::CallbackList<void(Game::CodeTasklet*, Pex::OpCode)> g_instructionExecutionEvent;

        InstructionExecutionEventHandle SubscribeToInstructionExecution(std::function<void(Game::CodeTasklet*, Pex::OpCode)> handler)
        {
            return g_instructionExecutionEvent.append(handler);
        }

        bool UnsubscribeFromInstructionExecution(InstructionExecutionEventHandle handle)
        {
            return g_instructionExecutionEvent.remove(handle);
        }

        eventpp::CallbackList<void(Game::VMStackData*)> g_createStackEvent;

        CreateStackEventHandle SubscribeToCreateStack(std::function<void(Game::VMStackData*)> handler)
        {
            return g_createStackEvent.append(handler);
        }

        bool UnsubscribeFromCreateStack(CreateStackEventHandle handle)
        {
            return g_createStackEvent.remove(handle);
        }

        eventpp::CallbackList<void(UInt32)> g_cleanupStackEvent;

        CleanupStackEventHandle SubscribeToCleanupStack(std::function<void(UInt32)> handler)
        {
            return g_cleanupStackEvent.append(handler);
        }

        bool UnsubscribeFromCleanupStack(CleanupStackEventHandle handle)
        {
            return g_cleanupStackEvent.remove(handle);
        }

        RelocAddr<uintptr_t> InstructionExecute(0x0276e9bd);

        void InstructionExecute_Hook(Game::CodeTasklet* tasklet, Pex::OpCode opCode)
        {
            if (tasklet->stackFrame)
            {
                g_instructionExecutionEvent(tasklet, opCode);
            }
        }

        typedef bool (*_CreateStack)(VirtualMachine* vm, UInt64 unk1, UInt64 unk2, UInt64 unk3, Game::VMStackData** stackData);
        RelocAddr<_CreateStack> CreateStack(0x02741f50);
        _CreateStack CreateStack_Original = nullptr;

        bool CreateStack_Hook(VirtualMachine* vm, UInt64 unk1, UInt64 unk2, UInt64 unk3, Game::VMStackData** stackData)
        {
            bool result = CreateStack_Original(vm, unk1, unk2, unk3, stackData);

            if (result)
            {
                g_createStackEvent(*stackData);
            }
            
            return result;
        }

        typedef void (*_CleanupStack)(VirtualMachine* vm, Game::VMStackData* stack);
        RelocAddr<_CleanupStack> CleanupStack(0x027424f0);
        _CleanupStack CleanupStack_Original = nullptr;

        void CleanupStack_Hook(VirtualMachine* vm, Game::VMStackData* stack)
        {
            if (!stack)
            {
                return;
            }

            UInt32 stackId = stack->stackId;
            CleanupStack_Original(vm, stack);
            g_cleanupStackEvent(stackId);
        }

        //typedef UInt32(*_ScriptFunctionInvoke)(ScriptFunction* function, StackData** stackData, Logger* logger, VirtualMachine* vm, UInt32 unk);
        //RelocAddr<_ScriptFunctionInvoke> ScriptFunctionInvoke(0x027acb90);
        //_ScriptFunctionInvoke ScriptFunctionInvoke_Original = nullptr;

        //UInt32 ScriptFunctionInvoke_Hook(ScriptFunction* func, StackData** stackData, Logger* logger, VirtualMachine* virtualMachine, UInt32 unk)
        //{
        //    if ((*stackData)->currentStackFrame)
        //    {
        //        if (!func->IsStatic())
        //        {
        //            //(*stackData)->currentStackFrame->identifier->properties->

        //            ////UInt64 baseValueHandle = (*stackData)->currentStackFrame->identifier->GetHandle();
        //            ////virtualMachine->GetHandlePolicy()->Resolve(-1, baseValueHandle);

        //            ////val->SetIdentifier(&(*stackData)->currentStackFrame->identifier);
        //            ////Unpack

        //            ////_MESSAGE("%s", val->data.GetStr()->c_str());
        //        }

        //        if ((*stackData)->currentStackFrame->parameterCount > 0)
        //        {
        //            VMState* state = (VMState*)(*stackData)->currentStackFrame;
        //            UInt32    argOffset = CALL_MEMBER_FN(state->argList, GetOffset)(state);
        //            VMValue* arg0 = CALL_MEMBER_FN(state->argList, Get)(state, 0, argOffset);
        //            if (arg0->GetTypeEnum() == VMValue::kType_String)
        //            {
        //                _MESSAGE("%s", arg0->data.GetStr()->c_str());
        //            }
        //        }
        //    }

        //    UInt32 result = ScriptFunctionInvoke_Original(func, stackData, logger, virtualMachine, unk);
        //    
        //    //UInt32 argOffset = CALL_MEMBER_FN(state->argList, GetOffset)(state);

        //    //T_Base* base = NULL;

        //    //// extract base object pointer for non-static types
        //    //if (!IsStaticType <T_Base>::value)
        //    //{
        //    //    UnpackValue(&base, baseValue);
        //    //    if (!base) return false;
        //    //}

        //    return result;
        //}

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

                //{
                //    struct ScriptFunctionInvoke_Code : Xbyak::CodeGenerator {
                //        ScriptFunctionInvoke_Code(void* buf) : Xbyak::CodeGenerator(4096, buf)
                //        {
                //            Xbyak::Label retnLabel;

                //            sub(rsp, 0x28);
                //            mov(rdx, ptr[rdx]);

                //            jmp(ptr[rip + retnLabel]);

                //            L(retnLabel);
                //            dq(ScriptFunctionInvoke.GetUIntPtr() + 0x07);
                //        }
                //    };

                //    void* codeBuf = g_localTrampoline.StartAlloc();
                //    ScriptFunctionInvoke_Code code(codeBuf);
                //    g_localTrampoline.EndAlloc(code.getCurr());

                //    ScriptFunctionInvoke_Original = (_ScriptFunctionInvoke)codeBuf;

                //    g_branchTrampoline.Write5Branch(ScriptFunctionInvoke.GetUIntPtr(), (uintptr_t)ScriptFunctionInvoke_Hook);
                //}
            }
        }
    }
}