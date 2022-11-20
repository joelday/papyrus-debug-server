#pragma once
#include <map>
#include <set>
#include "Protocol/protocol.h"

#include "GameInterfaces.h"

#include "PexCache.h"

namespace DarkId::Papyrus::DebugServer
{
	class BreakpointManager
	{
		std::map<int, std::set<int>> m_breakpoints;
		PexCache* m_pexCache;

	public:
		explicit BreakpointManager(PexCache* pexCache)
			: m_pexCache(pexCache)
		{
		}

		void SetBreakpoints(Source& source, const std::vector<SourceBreakpoint>& srcBreakpoints, std::vector<Breakpoint>& breakpoints);
		bool GetExecutionIsAtValidBreakpoint(RE::BSScript::Internal::CodeTasklet* tasklet);
	};
}
