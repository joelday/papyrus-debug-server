#pragma once

#include "GameInterfaces.h"
#include "Champollion/Pex/Instruction.hpp"

#include <functional>

#include "eventpp/callbacklist.h"

namespace DarkId::Papyrus::DebugServer
{
	namespace RuntimeEvents
	{
		typedef eventpp::CallbackList<void(Game::CodeTasklet*, Pex::OpCode)>::Handle InstructionExecutionEventHandle;
		InstructionExecutionEventHandle SubscribeToInstructionExecution(std::function<void(Game::CodeTasklet*, Pex::OpCode)> handler);
		bool UnsubscribeFromInstructionExecution(InstructionExecutionEventHandle handle);

		typedef eventpp::CallbackList<void(Game::VMStackData*)>::Handle CreateStackEventHandle;
		CreateStackEventHandle SubscribeToCreateStack(std::function<void(Game::VMStackData*)> handler);
		bool UnsubscribeFromCreateStack(CreateStackEventHandle handle);

		typedef eventpp::CallbackList<void(UInt32)>::Handle CleanupStackEventHandle;
		CleanupStackEventHandle SubscribeToCleanupStack(std::function<void(UInt32)> handler);
		bool UnsubscribeFromCleanupStack(CleanupStackEventHandle handle);

		namespace Internal
		{
			void CommitHooks();
		}
	}
}