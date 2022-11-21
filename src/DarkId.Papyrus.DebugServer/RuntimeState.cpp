#include "RuntimeState.h"
#include "Utilities.h"
#include "StateNodeBase.h"

#include <boost/algorithm/string.hpp>
#include "StackStateNode.h"
#include "ObjectStateNode.h"

#include "ArrayStateNode.h"
#include "ValueStateNode.h"

#if FALLOUT
#include "StructStateNode.h"
#endif

namespace DarkId::Papyrus::DebugServer
{
	using namespace RE::BSScript::Internal;

	RuntimeState::RuntimeState(const std::shared_ptr<IdProvider>& idProvider)
	{
		m_paths = std::make_unique<IdMap<std::string>>(idProvider);
	}

	bool RuntimeState::ResolveStateByPath(const std::string requestedPath, std::shared_ptr<StateNodeBase>& node)
	{
		const auto path = boost::algorithm::to_lower_copy(requestedPath);

		auto elements = Split(path, ".");

		if (elements.empty())
		{
			return false;
		}

		const auto stackIdElement = elements.at(0);
		int stackId;
		if (!ParseInt(stackIdElement, &stackId))
		{
			return false;
		}

		std::vector<std::string> currentPathElements;
		currentPathElements.push_back(stackIdElement);

		elements.erase(elements.begin());

		std::shared_ptr<StateNodeBase> currentNode = std::make_shared<StackStateNode>(stackId);

		while (!elements.empty() && currentNode)
		{
			auto structured = dynamic_cast<IStructuredState*>(currentNode.get());
			
			if (structured)
			{
				std::vector<std::string> childNames;
				structured->GetChildNames(childNames);

				for (auto childName : childNames)
				{
					boost::algorithm::to_lower(childName);
					auto discoveredElements(currentPathElements);
					discoveredElements.push_back(childName);

					const auto discoveredPath = Join(discoveredElements, ".");

					uint32_t addedId;
					m_paths->AddOrGetExisting(discoveredPath, addedId);
				}
			}
			
			const auto currentName = elements.at(0);
			currentPathElements.push_back(currentName);
		
			if (structured && !structured->GetChildNode(currentName, currentNode))
			{
				currentNode = nullptr;
				break;
			}
		
			elements.erase(elements.begin());
		}

		if (!currentNode)
		{
			return false;
		}

		node = currentNode;

		if (currentPathElements.size() > 1)
		{
			uint32_t id;
			m_paths->AddOrGetExisting(path, id);
			node->SetId(id);
		}
		else
		{
			node->SetId(stackId);
		}

		return true;
	}

	bool RuntimeState::ResolveStateById(const uint32_t id, std::shared_ptr<StateNodeBase>& node)
	{
		std::string path;

		if (m_paths->Get(id, path))
		{
			return ResolveStateByPath(path, node);
		}

		return false;
	}

	bool RuntimeState::ResolveChildrenByParentPath(const std::string requestedPath, std::vector<std::shared_ptr<StateNodeBase>>& nodes)
	{
		std::shared_ptr<StateNodeBase> resolvedParent;
		if (!ResolveStateByPath(requestedPath, resolvedParent))
		{
			return false;
		}

		auto structured = dynamic_cast<IStructuredState*>(resolvedParent.get());
		if (!structured)
		{
			return false;
		}

		std::vector<std::string> childNames;
		structured->GetChildNames(childNames);

		for (const auto& childName : childNames)
		{
			std::shared_ptr<StateNodeBase> childNode;
			if (ResolveStateByPath(StringFormat("%s.%s", requestedPath.c_str(), childName.c_str()), childNode))
			{
				nodes.push_back(childNode);
			}
		}

		return true;
	}

	bool RuntimeState::ResolveChildrenByParentId(const uint32_t id, std::vector<std::shared_ptr<StateNodeBase>>& nodes)
	{
		std::string path;

		if (m_paths->Get(id, path))
		{
			return ResolveChildrenByParentPath(path, nodes);
		}

		return false;
	}

	std::shared_ptr<StateNodeBase> RuntimeState::CreateNodeForVariable(std::string name, RE::BSScript::Variable* variable)
	{
		if (variable->IsObject())
		{
			return std::make_shared<ObjectStateNode>(name, variable->GetObject(), variable->GetObject()->GetTypeInfo());
		}

#if FALLOUT
		if (variable->IsVariable())
		{
			return CreateNodeForVariable(name, variable->GetVariable());
		}
		
		if (variable->IsStruct())
		{
			return std::make_shared<StructStateNode>(name, variable->GetStruct(), variable->GetStructType());
		}
#endif

		if (variable->IsArray())
		{
			return std::make_shared<ArrayStateNode>(name, variable->GetArray(), variable);
		}

		if (variable->IsBool() || variable->IsFloat() || variable->IsInt() || variable->IsString())
		{
			return std::make_shared<ValueStateNode>(name, variable);
		}
		
		return nullptr;
	}

	RE::BSTSmartPointer<RE::BSScript::Stack> RuntimeState::GetStack(uint32_t stackId)
	{
		const auto vm = VirtualMachine::GetSingleton();
		RE::BSSpinLockGuard lock(vm->runningStacksLock);

		const auto tableItem = vm->allRunningStacks.find(stackId);
		if (tableItem == vm->allRunningStacks.end())
		{
			return nullptr;
		}

		return tableItem->second;
	}

	RE::BSScript::StackFrame* RuntimeState::GetFrame(const uint32_t stackId, const uint32_t level)
	{
		std::vector<RE::BSScript::StackFrame*> frames;
		GetStackFrames(stackId, frames);

		if (frames.empty() || level > frames.size() - 1)
		{
			return nullptr;
		}

		return frames.at(level);
	}

	void RuntimeState::GetStackFrames(const RE::BSTSmartPointer<RE::BSScript::Stack> stack, std::vector<RE::BSScript::StackFrame*>& frames)
	{
		const auto vm = VirtualMachine::GetSingleton();
		RE::BSSpinLockGuard lock(vm->runningStacksLock);

		auto frame = stack->top;

		while (frame)
		{
			frames.push_back(frame);
			frame = frame->previousFrame;
		}
	}

	bool RuntimeState::GetStackFrames(const uint32_t stackId, std::vector<RE::BSScript::StackFrame*>& frames)
	{
		const auto vm = VirtualMachine::GetSingleton();
		RE::BSSpinLockGuard lock(vm->runningStacksLock);

		const auto stack = GetStack(stackId);
		if (!stack)
		{
			return false;
		}

		GetStackFrames(stack, frames);

		return true;
	}
}
