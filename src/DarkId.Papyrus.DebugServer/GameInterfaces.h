#pragma once

#include "f4se/PapyrusNativeFunctions.h"

namespace DarkId::Papyrus::DebugServer::Game
{
    namespace BSResource
    {
        class MemoryFileStream
        {
        public:
            virtual ~MemoryFileStream();
        }; //Size: 0x0008

        namespace Archive2
        {
            class ReaderStream
            {
            public:
                virtual ~ReaderStream();

                uint32_t m_streamLength; //0x0008
                uint32_t unk_08; //0x000C
                BSResource::MemoryFileStream* N00001DCE; //0x0010
                char pad_0018[16]; //0x0018
                StringCache::Ref m_filePath; //0x0028
                char pad_0030[8]; //0x0030
                uint32_t unk_38; //0x0038

                virtual void Function1();
                virtual void Function2();
                virtual void Function3();
                virtual void Function4();
                virtual void Function5();
                virtual void Function6();
                virtual void Function7();
                virtual void Function8();
                virtual void Function9();
            }; //Size: 0x003C
        }
    }

    class Unk
    {
    public:
        char pad_0000[8]; //0x0000
    }; //Size: 0x0008

    namespace GameScript
    {
        class Store // BSScript::IStore
        {
        public:
            virtual ~Store();

            uint64_t unk_08; //0x0008
            char pad_0010[24]; //0x0010
            BSResource::Archive2::ReaderStream* m_readerStream; //0x0028
            StringCache::Ref m_filePath; //0x0030
            bool m_hasOpenFile; //0x0038
            bool unk_39; //0x0039

            virtual void Function1();
            virtual void Function2();

            // Unsure which are bools or not:
            virtual bool Seek(SInt32 offset, UInt32 base);
            virtual bool Read(UInt32 len, void* buf);
            virtual bool Write(UInt32 len, void* buf);

            virtual bool Open(const char* name);
            virtual void Close();
            virtual void Function8();
            virtual void Function9();
        };
    }

    namespace BSScript
    {
        class CompiledScriptLoader
        {
        public:
            virtual ~CompiledScriptLoader();

            Logger* m_logger;
            GameScript::Store* m_store;
        };
    }

    class ScriptFunction : public IFunction
    {
    public:
        BSFixedString	m_fnName;		// 10
        BSFixedString	m_className;	// 18
        BSFixedString	m_stateName;	// 20
        UInt64			m_retnType;		// 28
        NativeFunctionBase::ParameterInfo	m_params; // 30
        bool			m_isStatic;		// 40
        UInt8			m_unk41;		// 41
        bool			m_isLatent;		// 42 (probably invalid here)
        UInt8			m_pad43;		// 43
        UInt32			m_unk44;		// 44
        UInt64	m_instructionMetadata;	// 48 (multiple smaller unknown values)

        UInt64* m_data; // 50
        UInt64* m_unk58; // 58
        UInt64* m_unk60; // 60
        BSFixedString m_sourceFileName; // 68

        UInt64 m_lineMappingsCount; // 70
        UInt16* m_lineMappings; // 78
    };

    STATIC_ASSERT(sizeof(ScriptFunction) == 0x80);

    class VMStackData;

    struct VMStackFrame
    {
        VMStackData* stackData; //0x0000
        VMStackFrame* previousFrame; //0x0008
        IFunction* function; //0x0010
        VMObjectTypeInfo* typeInfo_18; //0x0018
        UInt64 currentInstructionPosition; //0x0020
        VMObjectTypeInfo* baseValueTypeInfo; //0x0028
        VMIdentifier* identifier; //0x0030
        UInt32 parameterCount; //0x0038
    };

    class CodeTasklet : BSIntrusiveRefCounted
    {
    public:
        virtual ~CodeTasklet();

        enum TaskletRunState
        {
            kTaskletRunState_Unk0,
            kTaskletRunState_Unk1,
            kTaskletRunState_Unk2,
            kTaskletRunState_Unk3,
            kTaskletRunState_Unk4,
            kTaskletRunState_Unk5
        };

        VMStackData* stackData; //0x0010
        VirtualMachine* virtualMachine; //0x0018
        Logger* logger; //0x0020
        TaskletRunState runState; //0x0028
        char pad_002C[4]; //0x002C
        VMStackFrame* stackFrame; //0x0030
        UInt32 N00002954; //0x0038
        UInt8 unk_3c; //0x003C
        UInt8 unk_3d_usedByAssign; //0x003D
        UInt8 unk_3e_usedByAssign; //0x003E
        UInt8 unk_3f; //0x003F
        UInt32 instructionsDataLength; //0x0040
        UInt32 N00002955; //0x0044
        void* instructionsData; //0x0048
    };

    STATIC_ASSERT(sizeof(CodeTasklet) == 0x50);

    class VMStackData
    {
    public:
        UInt32 unk_00; //0x0000
        UInt32 unk_04; //0x0004
        SimpleAllocMemoryPagePolicy* memoryPagePolicy; //0x0008
        UInt64* profiler; //0x0010
        char pad_0018[8]; //0x0018
        UInt64 unk_20;
        UInt64 unk_26; //0x0028
        UInt64 unk_30;
        UInt32 unk_38; //0x0038
        UInt32 unk_3C; //0x003C
        UInt64 unk_40;
        char pad_0048[8]; //0x0048
        UInt64 unk_50; //0x0050
        UInt64 unk_58_checkedForLessThan2; //0x0058
        VMStackFrame* currentStackFrame; //0x0060
        char pad_0068[4]; //0x0068
        UInt32 unk_6c_callsSomethingOnVmWithVMStackData; //0x006C
        VMObjectTypeInfo* unk_70; //0x0070
        UInt64 unk_78;
        UInt32 stackId; //0x0080
        UInt32 unk_84; //0x0084
        CodeTasklet* codeTasklet; //0x0088
        UInt64* stackCallbackFunctor; //0x0090
        UInt64* unk_98; //0x0098
        char unk_A0[8]; //0x00A0
    }; //Size: 0x00A8

    STATIC_ASSERT(sizeof(VMStackData) == 0xA8);
}