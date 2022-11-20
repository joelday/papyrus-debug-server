#pragma once

#include "IdMap.h"

#include "GameInterfaces.h"
#include <memory>
#include <vector>
#include "StateNodeBase.h"
#include <RE/B/BSTSmartPointer.h>
#include <common/ITypes.h>
namespace DarkId::Papyrus::DebugServer
{
	class RuntimeState
	{
		std::unique_ptr<IdMap<std::string>> m_paths;

	public:
		explicit RuntimeState(const std::shared_ptr<IdProvider>& idProvider);

		bool ResolveStateByPath(std::string requestedPath, std::shared_ptr<StateNodeBase>& node);
		bool ResolveStateById(UInt32 id, std::shared_ptr<StateNodeBase>& node);
		bool ResolveChildrenByParentPath(std::string requestedPath, std::vector<std::shared_ptr<StateNodeBase>>& nodes);
		bool ResolveChildrenByParentId(UInt32 id, std::vector<std::shared_ptr<StateNodeBase>>& nodes);

		static std::shared_ptr<StateNodeBase> CreateNodeForVariable(std::string name, RE::BSScript::Variable* variable);
		
		static RE::BSTSmartPointer<RE::BSScript::Stack> GetStack(UInt32 stackId);
		static RE::BSScript::StackFrame* GetFrame(UInt32 stackId, UInt32 level);

		static void GetStackFrames(RE::BSTSmartPointer<RE::BSScript::Stack> stack, std::vector<RE::BSScript::StackFrame*>& frames);
		static bool GetStackFrames(UInt32 stackId, std::vector<RE::BSScript::StackFrame*>& frames);
	};
}

