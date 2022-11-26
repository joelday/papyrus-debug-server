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
		if (pexCache->GetSourceData(NormalizeScriptName(m_stackFrame->owningFunction->GetSourceFilename().c_str()).c_str(), source))
		{
			stackFrame.source = source;

			uint32_t lineNumber;
			if (m_stackFrame->owningFunction->TranslateIPToLineNumber(m_stackFrame->instructionPointer, lineNumber))
			{
				stackFrame.line = lineNumber;
			}
		}

		auto name = std::string(m_stackFrame->owningFunction->GetName().c_str());
		if (strcmp(m_stackFrame->owningFunction->GetStateName().c_str(), "") != 0)
		{
			name = StringFormat("%s (%s)", name.c_str(), m_stackFrame->owningFunction->GetStateName().c_str());
		}

		stackFrame.name = name;

		return true;
	}

	bool StackFrameStateNode::GetChildNames(std::vector<std::string>& names)
	{
		if (!m_stackFrame->owningFunction->GetIsNative())
		{
			names.push_back("Local");
		}

		return true;
	}

	bool StackFrameStateNode::GetChildNode(std::string name, std::shared_ptr<StateNodeBase>& node)
	{
		if (!m_stackFrame->owningFunction->GetIsNative() && CaseInsensitiveEquals(name, "local"))
		{
			node = std::make_shared<LocalScopeStateNode>(m_stackFrame);
			return true;
		}

		return false;
	}
}
