#pragma once

#include "protocol/debugger.h"

#include "f4se/PluginAPI.h"
#include "RuntimeEvents.h"
#include "PexCache.h"

#include "GameInterfaces.h"

#include <set>

namespace DarkId::Papyrus::DebugServer
{
	class PapyrusDebugger :
		public Debugger
	{
	public:
		PapyrusDebugger(Protocol* protocol, F4SETaskInterface* tasks);
		~PapyrusDebugger();

		bool IsJustMyCode() const { return false; };
		void SetJustMyCode(bool enable) { };

		HRESULT Initialize() override;
		HRESULT Attach() override { return 0; };
		HRESULT Launch(std::string fileExec, std::vector<std::string> execArgs, bool stopAtEntry = false) override { return 0; }
		HRESULT ConfigurationDone() override { return 0; }

		HRESULT Disconnect(DisconnectAction action = DisconnectDefault) override { return 0; }

		int GetLastStoppedThreadId() override { return 0; }

		HRESULT Continue() override;
		HRESULT Pause() override;
		HRESULT GetThreads(std::vector<Thread>& threads) override;
		HRESULT SetBreakpoints(const Source& source, const std::vector<SourceBreakpoint>& srcBreakpoints, std::vector<Breakpoint>& breakpoints) override;
		HRESULT SetFunctionBreakpoints(const std::vector<FunctionBreakpoint>& funcBreakpoints, std::vector<Breakpoint>& breakpoints) override { return 0; }
		void InsertExceptionBreakpoint(const std::string& name, Breakpoint& breakpoint) override { }
		HRESULT GetStackTrace(int threadId, int startFrame, int levels, std::vector<StackFrame>& stackFrames, int& totalFrames) override;
		HRESULT StepCommand(int threadId, StepType stepType) override;
		HRESULT GetScopes(uint64_t frameId, std::vector<Scope>& scopes) override;
		HRESULT GetVariables(uint64_t variablesReference, VariablesFilter filter, int start, int count, std::vector<Variable>& variables) override;
		int GetNamedVariables(uint64_t variablesReference) override;
		HRESULT Evaluate(uint64_t frameId, const std::string& expression, Variable& variable, std::string& output) override { return 0; }
		HRESULT SetVariable(const std::string& name, const std::string& value, uint32_t ref, std::string& output) override { return 0; }
		HRESULT SetVariableByExpression(uint64_t frameId, const std::string& name, const std::string& value, std::string& output) override { return 0; }
		HRESULT GetSource(Source& source, std::string& output) override;
        HRESULT GetLoadedSources(std::vector<Source>& sources) override;
    private:
        enum DebuggerState
        {
            kState_Running = 0,
            kState_Paused,
            kState_Stepping
        };

        F4SETaskInterface* m_tasks;

        bool m_closed = false;

        DebuggerState m_state;
        UInt32 m_currentStepStackId;
        Game::VMStackFrame* m_currentStepStackFrame;
        StepType m_currentStepType;

        VirtualMachine* m_vm;
        Protocol* m_protocol;
        PexCache* m_pexCache;

        std::map<int, std::set<int>> m_breakpoints;

        std::set<int> m_deadStackIds;

        UInt64 m_currentValueId = 0;
        std::map<UInt64, VMValue*> m_values;

        RuntimeEvents::CreateStackEventHandle m_createStackEventHandle;
        RuntimeEvents::CleanupStackEventHandle m_cleanupStackEventHandle;
        RuntimeEvents::InstructionExecutionEventHandle m_instructionExecutionEventHandle;

        UInt64 CacheValue(VMValue* value);

        void StackCreated(Game::VMStackData* stackData);
        void StackCleanedUp(UInt32 stackId);
        void InstructionExecution(Game::CodeTasklet* tasklet, Pex::OpCode opCode);

        Game::VMStackFrame* GetFrame(UInt64 frameId);
        void GetStackFrames(UInt32 stackId, std::vector<Game::VMStackFrame*>& frames);
        bool GetSourceData(const char* scriptName, Source& data, std::set<int>& seenScripts);

        void ToRefVariables(VMRefOrInventoryObj* ref, std::vector<Variable>& variables);
        void ToVariableData(const char* name, VMValue* value, Variable& out);
        void ToStackFrameData(Game::VMStackFrame* frame, UInt32 level, StackFrame& out);
        void ToThreadData(Game::VMStackData* stack, Thread& thread);
	};
}