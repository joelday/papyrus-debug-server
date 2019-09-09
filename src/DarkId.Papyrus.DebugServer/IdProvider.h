#pragma once
#include <mutex>

namespace DarkId::Papyrus::DebugServer
{
	class IdProvider
	{
		UInt32 m_currentId = 1000;
		std::mutex m_idMutex;
	public:
		UInt32 GetNext();
	};
}