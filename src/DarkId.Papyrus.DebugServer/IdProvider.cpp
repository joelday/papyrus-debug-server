#include "IdProvider.h"
#include <common/ITypes.h>
namespace DarkId::Papyrus::DebugServer
{
	UInt32 IdProvider::GetNext()
	{
		std::lock_guard<std::mutex> lock(m_idMutex);
		return m_currentId++;
	}
}
