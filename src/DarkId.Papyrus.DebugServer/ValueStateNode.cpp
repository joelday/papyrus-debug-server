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
		
		if (m_variable->IsString()){
							variable.type = "string";
				variable.value = StringFormat("\"%s\"", m_variable->GetString());
		} else if (m_variable->IsInt()){
				variable.type = "int";
				variable.value = StringFormat("%d", m_variable->GetSInt());
		} else if (m_variable->IsFloat()){
				variable.type = "float";
				variable.value = StringFormat("%f", m_variable->GetFloat());
		} else if (m_variable->IsBool()){
				variable.type = "bool";
				variable.value = StringFormat(m_variable->GetBool() ? "true" : "false");
		}
				
		return true;
	}
}
