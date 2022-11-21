#include "StateNodeBase.h"
#include <common/ITypes.h>
namespace DarkId::Papyrus::DebugServer
{
	int StateNodeBase::GetId() const
	{
		return m_id;
	}

	void StateNodeBase::SetId(const UInt32 id)
	{
		m_id = id;
	}
}

