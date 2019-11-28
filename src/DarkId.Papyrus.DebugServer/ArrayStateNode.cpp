#include "ArrayStateNode.h"
#include "Utilities.h"
#include "RuntimeState.h"

namespace DarkId::Papyrus::DebugServer
{
	ArrayStateNode::ArrayStateNode(std::string name, RE::BSScript::Array* value, RE::BSScript::Type* type) :
		m_name(name), m_value(value), m_type(type)
	{
	}

	bool ArrayStateNode::SerializeToProtocol(Variable& variable)
	{
		variable.variablesReference = m_value ? GetId() : 0;
		variable.indexedVariables = m_value ? m_value->size() : 0;

		variable.name = m_name;

		std::string elementTypeName;

		if (m_type->IsObjectArray())
		{
			elementTypeName = m_type->GetClass()->GetName();
		}
#if FALLOUT
		else if (m_type->IsStructArray())
		{
			elementTypeName = m_type->GetStructType()->GetName();
		}
#endif
		else
		{
			switch (m_type->GetUnmangledType())
			{
			case RE::VMTypeID::kStringArray:
				elementTypeName = "string";
				break;
			case RE::VMTypeID::kIntArray:
				elementTypeName = "int";
				break;
			case RE::VMTypeID::kFloatArray:
				elementTypeName = "float";
				break;
			case RE::VMTypeID::kBoolArray:
				elementTypeName = "bool";
				break;
			default:
				break;
			}
		}

		variable.type = StringFormat("%s[]", elementTypeName.c_str());

		if (!m_value)
		{
			variable.value = "None";
		}
		else
		{
			variable.value = StringFormat("%s[%d]", elementTypeName.c_str(), m_value->size());
		}
		
		return true;
	}

	bool ArrayStateNode::GetChildNames(std::vector<std::string>& names)
	{
		if (!m_value)
		{
			return true;
		}
		
		for (auto i = 0; i < m_value->size(); i++)
		{
			names.push_back(std::to_string(i));
		}

		return true;
	}

	bool ArrayStateNode::GetChildNode(std::string name, std::shared_ptr<StateNodeBase>& node)
	{
		if (!m_value)
		{
			return false;
		}
		
		int elementIndex;
		if (!ParseInt(name, &elementIndex))
		{
			return false;
		}

		if (elementIndex < 0 || elementIndex > m_value->size() - 1)
		{
			return false;
		}

		node = RuntimeState::CreateNodeForVariable(std::to_string(elementIndex), &m_value->at(elementIndex));
		
		return true;
	}
}
