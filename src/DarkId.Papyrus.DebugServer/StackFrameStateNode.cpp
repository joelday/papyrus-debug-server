#include "StackFrameStateNode.h"

#include "Utilities.h"
#include <string>

#include "LocalScopeStateNode.h"

namespace DarkId::Papyrus::DebugServer
{
	StackFrameStateNode::StackFrameStateNode(RE::BSScript::StackFrame* stackFrame) : m_stackFrame(stackFrame)
	{

	}

	bool StackFrameStateNode::SerializeToProtocol(StackFrame& stackFrame, PexCache* pexCache) const
	{
		stackFrame = StackFrame(GetId());

		Source source;
		if (pexCache->GetSourceData(m_stackFrame->func->GetScriptName().c_str(), source))
		{
			stackFrame.source = source;

			UInt32 lineNumber;
			if (m_stackFrame->func->GetLineNumber(m_stackFrame->taskletExecutionOffset, lineNumber))
			{
				stackFrame.line = lineNumber;
			}
		}

		auto name = std::string(m_stackFrame->func->GetFunctionName().c_str());
		if (strcmp(m_stackFrame->func->GetStateName().c_str(), "") != 0)
		{
			name = StringFormat("%s (%s)", name.c_str(), m_stackFrame->func->GetStateName().c_str());
		}

		stackFrame.name = name;

		return true;
	}

	bool StackFrameStateNode::GetChildNames(std::vector<std::string>& names)
	{
		if (!m_stackFrame->func->IsNative())
		{
			names.push_back("Local");
		}

		return true;
	}

	bool StackFrameStateNode::GetChildNode(std::string name, std::shared_ptr<StateNodeBase>& node)
	{
		if (!m_stackFrame->func->IsNative() && CaseInsensitiveEquals(name, "local"))
		{
			node = std::make_shared<LocalScopeStateNode>(m_stackFrame);
			return true;
		}

		return false;
	}
}
