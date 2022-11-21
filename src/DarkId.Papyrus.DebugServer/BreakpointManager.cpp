#include "BreakpointManager.h"
#include "Pex/Binary.hpp"
#include <regex>

namespace DarkId::Papyrus::DebugServer
{
	void BreakpointManager::SetBreakpoints(Source& source, const std::vector<SourceBreakpoint>& srcBreakpoints, std::vector<Breakpoint>& breakpoints)
	{
		std::set<int> breakpointLines;

		auto scriptName = std::regex_replace(source.name.c_str(), std::regex(".psc"), "");
		auto binary = m_pexCache->GetScript(scriptName.c_str());

		const auto sourceReference = m_pexCache->GetScriptReference(scriptName.c_str());
		source.sourceReference = sourceReference;

		for (const auto& srcBreakpoint : srcBreakpoints)
		{
			auto foundLine = false;

			if (binary)
			{
				for (auto functionInfo : binary->getDebugInfo().getFunctionInfos())
				{
					if (foundLine)
					{
						break;
					}

					for (auto lineNumber : functionInfo.getLineNumbers())
					{
						if (srcBreakpoint.line == lineNumber)
						{
							foundLine = true;
							break;
						}
					}
				}
			}

			breakpointLines.emplace(srcBreakpoint.line);

			Breakpoint breakpoint;
			breakpoint.source = source;
			breakpoint.verified = foundLine;
			breakpoint.line = srcBreakpoint.line;

			breakpoints.push_back(breakpoint);
		}

		m_breakpoints[sourceReference] = breakpointLines;
	}

	bool BreakpointManager::GetExecutionIsAtValidBreakpoint(RE::BSScript::Internal::CodeTasklet* tasklet)
	{
		auto func = tasklet->topFrame->owningFunction;

		if (func->GetIsNative())
		{
			return false;
		}

		const auto sourceReference = m_pexCache->GetScriptReference(func->GetSourceFilename().c_str());
		
		if (m_breakpoints.find(sourceReference) != m_breakpoints.end())
		{
			auto breakpointLines = m_breakpoints[sourceReference];
			if (!breakpointLines.empty())
			{
				uint32_t currentLine;

				return func->TranslateIPToLineNumber(tasklet->topFrame->instructionPointer, currentLine) &&
					breakpointLines.find(currentLine) != breakpointLines.end();
			}
		}

		return false;
	}
}
