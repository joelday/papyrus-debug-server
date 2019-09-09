#include "DebugExecutionManager.h"

namespace DarkId::Papyrus::DebugServer
{
	using namespace RE::BSScript::Internal;

	void DebugExecutionManager::HandleInstruction(CodeTasklet* tasklet, CodeTasklet::OpCode opCode)
	{
		// TODO: Should this lock be scoped only to everything before the pause spin?

		std::lock_guard<std::mutex> lock(m_instructionMutex);

		const auto func = tasklet->stackFrame->func;

		if (m_state != DebuggerState::kPaused && m_breakpointManager->GetExecutionIsAtValidBreakpoint(tasklet))
		{
			m_state = DebuggerState::kPaused;
			m_protocol->EmitStoppedEvent(StoppedEvent(StopReason::StopBreakpoint, tasklet->stack->stackID));
		}

		if (m_state == DebuggerState::kStepping && tasklet->stack->stackID == m_currentStepStackId)
		{
			auto shouldPause = false;

			if (m_currentStepStackFrame)
			{
				std::vector<RE::BSScript::StackFrame*> currentFrames;
				RuntimeState::GetStackFrames(tasklet->stack->stackID, currentFrames);

				if (!currentFrames.empty())
				{
					auto stepFrameIndex = -1;
					const auto stepFrameIter = std::find(currentFrames.begin(), currentFrames.end(), m_currentStepStackFrame);

					if (stepFrameIter != currentFrames.end())
					{
						stepFrameIndex = std::distance(currentFrames.begin(), stepFrameIter);
					}

					switch (m_currentStepType)
					{
					case Debugger::StepType::STEP_IN:
						shouldPause = true;
						break;
					case Debugger::StepType::STEP_OUT:
						if (stepFrameIndex == -1)
						{
							shouldPause = true;
						}
						break;
					case Debugger::StepType::STEP_OVER:
						if (stepFrameIndex <= 0)
						{
							shouldPause = true;
						}
						break;
					}
				}
			}

			if (shouldPause)
			{
				m_state = DebuggerState::kPaused;
				m_currentStepStackId = 0;
				m_currentStepStackFrame = nullptr;
				m_protocol->EmitStoppedEvent(StoppedEvent(StopReason::StopStep, tasklet->stack->stackID));
			}
		}

		const auto currentState = m_state;
		if (currentState == DebuggerState::kPaused)
		{
			ShowCursor(true);
		}

		while (m_state == DebuggerState::kPaused && !m_closed)
		{
			Sleep(100);
		}

		if (currentState == DebuggerState::kPaused)
		{
			ShowCursor(false);
		}
	}

	void DebugExecutionManager::Close()
	{
		m_closed = true;
		std::lock_guard<std::mutex> lock(m_instructionMutex);
	}

	bool DebugExecutionManager::Continue()
	{
		m_state = DebuggerState::kRunning;
		m_protocol->EmitContinuedEvent(ContinuedEvent());

		return true;
	}

	bool DebugExecutionManager::Pause() const
	{
		m_protocol->EmitStoppedEvent(StoppedEvent(StopReason::StopPause));

		return true;
	}

	bool DebugExecutionManager::Step(UInt32 stackId, const Debugger::StepType stepType)
	{
		if (m_state != DebuggerState::kPaused)
		{
			return false;
		}
		
		const auto vm = VirtualMachine::GetSingleton();

		const auto stackIter = vm->allStacks.find(stackId);

		if (stackIter != vm->allStacks.end())
		{
			const auto stack = stackIter->second.get();
			if (stack->current)
			{
				m_currentStepStackFrame = stack->current;
			}
		}

		m_state = DebuggerState::kStepping;
		m_currentStepStackId = stackId;
		m_currentStepType = stepType;

		return true;
	}
}
