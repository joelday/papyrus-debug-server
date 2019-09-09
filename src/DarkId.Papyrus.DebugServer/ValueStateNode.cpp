#include "ValueStateNode.h"
#include "Utilities.h"

namespace DarkId::Papyrus::DebugServer
{
	ValueStateNode::ValueStateNode(std::string name, RE::BSScript::Variable* variable) :
		m_name(name), m_variable(variable)
	{
	}

	bool ValueStateNode::SerializeToProtocol(Variable& variable)
	{
		variable.name = m_name;
		
		const auto typeId = m_variable->GetUnmangledType();

		switch (typeId)
		{
			case RE::VMTypeID::kString:
			{
				variable.type = "string";
				variable.value = StringFormat("\"%s\"", m_variable->GetString().c_str());
			}
			break;
			case RE::VMTypeID::kInt:
			{
				variable.type = "int";
				variable.value = StringFormat("%d", m_variable->GetSInt());
			}
			break;
			case RE::VMTypeID::kFloat:
			{
				variable.type = "float";
				variable.value = StringFormat("%f", m_variable->GetFloat());
			}
			break;
			case RE::VMTypeID::kBool:
			{
				variable.type = "bool";
				variable.value = StringFormat(m_variable->GetBool() ? "true" : "false");
			}
			break;
			default:
				return false;
		}
		
		return true;
	}
}
