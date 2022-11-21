#include "PapyrusDebugger.h"

#include <functional>
#include <string>

#include "Utilities.h"
#include "GameInterfaces.h"
#include "StackStateNode.h"
#include "StackFrameStateNode.h"

#if SKYRIM
	#include <SKSE/Impl/PCH.h>
	#include <SKSE/Logger.h>
	#include <SKSE/API.h>
namespace XSE = SKSE;
#elif FALLOUT
	#include <F4SE/API.h>
	#include <f4se/GameReferences.h>
namespace XSE = F4SE;
#endif

#include "StateNodeBase.h"

namespace DarkId::Papyrus::DebugServer
{
	PapyrusDebugger::PapyrusDebugger(Protocol* protocol)
	{
		m_protocol = protocol;

		m_pexCache = std::make_shared<PexCache>();

		m_breakpointManager = std::make_shared<BreakpointManager>(m_pexCache.get());

		m_idProvider = std::make_shared<IdProvider>();
		m_runtimeState = std::make_shared<RuntimeState>(m_idProvider);

		m_executionManager = std::make_shared<DebugExecutionManager>(m_protocol, m_runtimeState.get(), m_breakpointManager.get());

		m_createStackEventHandle =
			RuntimeEvents::SubscribeToCreateStack(std::bind(&PapyrusDebugger::StackCreated, this, std::placeholders::_1));

		m_cleanupStackEventHandle =
			RuntimeEvents::SubscribeToCleanupStack(std::bind(&PapyrusDebugger::StackCleanedUp, this, std::placeholders::_1));

		m_instructionExecutionEventHandle =
			RuntimeEvents::SubscribeToInstructionExecution(
				std::bind(&PapyrusDebugger::InstructionExecution, this, std::placeholders::_1, std::placeholders::_2));

		// m_initScriptEventHandle = RuntimeEvents::SubscribeToInitScript(std::bind(&PapyrusDebugger::InitScriptEvent, this, std::placeholders::_1));

		m_logEventHandle =
			RuntimeEvents::SubscribeToLog(std::bind(&PapyrusDebugger::EventLogged, this, std::placeholders::_1));
	}

	//void PapyrusDebugger::InitScriptEvent(RE::TESInitScriptEvent* initEvent)
	//{
	//}

	void PapyrusDebugger::EventLogged(const RE::BSScript::LogEvent* logEvent) const
	{
#if SKYRIM
		const auto message = std::string(logEvent->errorMsg);
#elif FALLOUT
		const auto message = std::string(logEvent->message->text);
#endif
		
		const OutputEvent output(OutputCategory::OutputConsole, message + "\r\n");

		m_protocol->EmitOutputEvent(output);
	}


	void PapyrusDebugger::StackCreated(RE::BSTSmartPointer<RE::BSScript::Stack>& stack)
	{
		const auto stackId = stack->stackID;
		
		XSE::GetTaskInterface()->AddTask([this, stackId]()
		{
			if (m_closed)
			{
				return;
			}

			const auto stack = m_runtimeState->GetStack(stackId);
			if (!stack)
			{
				return;
			}

			m_protocol->EmitThreadEvent(ThreadEvent(ThreadReason::ThreadStarted, stackId));
			
			if (stack->top && stack->top->owningFunction)
			{
				const auto scriptName = stack->top->owningFunction->GetSourceFilename();
				CheckSourceLoaded(scriptName.c_str());
			}
		});
	}
	
	void PapyrusDebugger::StackCleanedUp(UInt32 stackId)
	{
		XSE::GetTaskInterface()->AddTask([this, stackId]()
		{
			if (m_closed)
			{
				return;
			}

			m_protocol->EmitThreadEvent(ThreadEvent(ThreadReason::ThreadExited, stackId));
		});
	}

	void PapyrusDebugger::InstructionExecution(CodeTasklet* tasklet, CodeTasklet::OpCode opcode) const
	{
		m_executionManager->HandleInstruction(tasklet, opcode);
	}

	void PapyrusDebugger::CheckSourceLoaded(const char* scriptName) const
	{
		if (!m_pexCache->HasScript(scriptName))
		{
			Source source;
			if (!m_pexCache->GetSourceData(scriptName, source))
			{
				return;
			}
			
			m_protocol->EmitLoadedSourceEvent(
				LoadedSourceEvent(LoadedSourceReason::SourceNew, source));
		}
	}

	HRESULT PapyrusDebugger::SetBreakpoints(Source& source, const std::vector<SourceBreakpoint>& srcBreakpoints, std::vector<Breakpoint>& breakpoints)
	{
		m_breakpointManager->SetBreakpoints(source, srcBreakpoints, breakpoints);
		return 0;
	}

	HRESULT PapyrusDebugger::Initialize()
	{
		m_protocol->EmitInitializedEvent();
		return 0;
	}

	HRESULT PapyrusDebugger::Pause()
	{
		return m_executionManager->Pause() ? 0 : 1;
	}

	HRESULT PapyrusDebugger::Continue()
	{
		return m_executionManager->Continue() ? 0 : 1;
	}

	HRESULT PapyrusDebugger::GetSource(Source& source, std::string& output)
	{
		return m_pexCache->GetDecompiledSource(source.name.c_str(), output) ? 0 : 1;
	}

	HRESULT PapyrusDebugger::GetLoadedSources(std::vector<Source>& sources)
	{
		const auto vm = RE::BSScript::Internal::VirtualMachine::GetSingleton();
		RE::BSSpinLockGuard lock(vm->typeInfoLock);

		for (const auto& script : vm->objectTypeMap)
		{
			Source source;
			if (m_pexCache->GetSourceData(script.first.c_str(), source))
			{
				sources.push_back(source);
			}
		}
		
		return 0;
	}

	HRESULT PapyrusDebugger::GetThreads(std::vector<Thread>& threads)
	{
		const auto vm = RE::BSScript::Internal::VirtualMachine::GetSingleton();
		RE::BSSpinLockGuard lock(vm->runningStacksLock);

		std::vector<std::string> stackIdPaths;

		for (auto& elem : vm->allRunningStacks)
		{
			const auto stack = elem.second.get();
			if (!stack || !stack->top)
			{
				continue;
			}

			stackIdPaths.push_back(std::to_string(stack->stackID));
		}

		for (auto& path : stackIdPaths)
		{
			std::shared_ptr<StateNodeBase> stateNode;
			if (!m_runtimeState->ResolveStateByPath(path, stateNode))
			{
				continue;
			}

			const auto node = dynamic_cast<StackStateNode*>(stateNode.get());

			Thread thread;
			if (node->SerializeToProtocol(thread))
			{
				threads.push_back(thread);
			}
		}

		return 0;
	}

	HRESULT PapyrusDebugger::GetScopes(const uint64_t frameId, std::vector<Scope>& scopes)
	{
		const auto vm = RE::BSScript::Internal::VirtualMachine::GetSingleton();
		RE::BSSpinLockGuard lock(vm->runningStacksLock);

		std::vector<std::shared_ptr<StateNodeBase>> frameScopes;
		m_runtimeState->ResolveChildrenByParentId(frameId, frameScopes);

		for (const auto& frameScope : frameScopes)
		{
			auto asScopeSerializable = dynamic_cast<IProtocolScopeSerializable*>(frameScope.get());
			if (!asScopeSerializable)
			{
				continue;
			}
			
			Scope scope;
			if (!asScopeSerializable->SerializeToProtocol(scope))
			{
				continue;
			}

			scopes.push_back(scope);
		}

		return 0;
	}

	HRESULT PapyrusDebugger::GetVariables(uint64_t variablesReference, VariablesFilter filter, int start, int count, std::vector<Variable> & variables)
	{
		const auto vm = RE::BSScript::Internal::VirtualMachine::GetSingleton();
		RE::BSSpinLockGuard lock(vm->runningStacksLock);

		std::vector<std::shared_ptr<StateNodeBase>> variableNodes;
		m_runtimeState->ResolveChildrenByParentId(variablesReference, variableNodes);

		for (const auto& variableNode : variableNodes)
		{
			auto asVariableSerializable = dynamic_cast<IProtocolVariableSerializable*>(variableNode.get());
			if (!asVariableSerializable)
			{
				continue;
			}

			Variable variable;
			if (!asVariableSerializable->SerializeToProtocol(variable))
			{
				continue;
			}

			variables.push_back(variable);
		}

		return 0;
	}

	int PapyrusDebugger::GetNamedVariables(uint64_t variablesReference)
	{
		// SKSE::log::info("Named variables count request: %d", variablesReference);
		return 0;
	}

	HRESULT PapyrusDebugger::GetStackTrace(int threadId, int startFrame, int levels, std::vector<StackFrame> & stackFrames, int& totalFrames)
	{
		const auto vm = RE::BSScript::Internal::VirtualMachine::GetSingleton();
		RE::BSSpinLockGuard lock(vm->runningStacksLock);

		if (threadId == -1)
		{
			totalFrames = 0;
			return 0;
		}

		std::vector<std::shared_ptr<StateNodeBase>> frameNodes;
		if (!m_runtimeState->ResolveChildrenByParentPath(std::to_string(threadId), frameNodes))
		{
			return 0;
		}

		for (auto frameIndex = startFrame; frameIndex < frameNodes.size() && frameIndex < startFrame + levels; frameIndex++)
		{
			const auto node = dynamic_cast<StackFrameStateNode*>(frameNodes.at(frameIndex).get());
			
			StackFrame frame;
			node->SerializeToProtocol(frame, m_pexCache.get());

			stackFrames.push_back(frame);
		}

		return 1;
	}

	HRESULT PapyrusDebugger::StepCommand(int threadId, StepType stepType)
	{
		return m_executionManager->Step(threadId, stepType) ? 0 : 1;
	}

	PapyrusDebugger::~PapyrusDebugger()
	{
		m_closed = true;

		RuntimeEvents::UnsubscribeFromLog(m_logEventHandle);
		// RuntimeEvents::UnsubscribeFromInitScript(m_initScriptEventHandle);
		RuntimeEvents::UnsubscribeFromInstructionExecution(m_instructionExecutionEventHandle);
		RuntimeEvents::UnsubscribeFromCreateStack(m_createStackEventHandle);
		RuntimeEvents::UnsubscribeFromCleanupStack(m_cleanupStackEventHandle);

		m_executionManager->Close();
	}
}
