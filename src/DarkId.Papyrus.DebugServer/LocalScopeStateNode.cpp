#include "LocalScopeStateNode.h"
#include "Utilities.h"
#include "RuntimeState.h"

namespace DarkId::Papyrus::DebugServer
{
	LocalScopeStateNode::LocalScopeStateNode(RE::BSScript::StackFrame* stackFrame) : m_stackFrame(stackFrame)
	{
	}

	bool LocalScopeStateNode::SerializeToProtocol(Scope& scope)
	{
		scope.name = "Local";
		scope.expensive = false;

		scope.variablesReference = GetId();

		std::vector<std::string> childNames;
		GetChildNames(childNames);

		scope.namedVariables = childNames.size();
		scope.indexedVariables = 0;

		return true;
	}

	bool LocalScopeStateNode::GetChildNames(std::vector<std::string>& names)
	{
		if (!m_stackFrame->func->IsStatic())
		{
			names.push_back("self");
		}

		for (auto i = 0; i < m_stackFrame->func->GetNumVars(); i++)
		{
			RE::BSFixedString varName;
			m_stackFrame->func->GetVarName(i, varName);

			if (varName.empty() || varName.front() == ':')
			{
				continue;
			}

			names.push_back(varName.c_str());
		}

		return true;
	}

	bool LocalScopeStateNode::GetChildNode(std::string name, std::shared_ptr<StateNodeBase>& node)
	{
		if (!m_stackFrame->func->IsStatic() && CaseInsensitiveEquals(name, "self"))
		{
			node = RuntimeState::CreateNodeForVariable("self", &m_stackFrame->baseValue);
			
			return true;
		}

		for (auto i = 0; i < m_stackFrame->func->GetNumVars(); i++)
		{
			RE::BSFixedString varName;
			m_stackFrame->func->GetVarName(i, varName);

			if (varName.empty() || varName.front() == ':')
			{
				continue;
			}

			if (CaseInsensitiveEquals(name, varName.c_str()))
			{
				const auto chunkIndex = m_stackFrame->stack->GetChunkIdx(m_stackFrame);
				const auto variable = m_stackFrame->Get(i, chunkIndex);
				if (variable)
				{
					node = RuntimeState::CreateNodeForVariable(varName.c_str(), variable);

					return true;
				}
			}
		}

		return false;
	}
}
