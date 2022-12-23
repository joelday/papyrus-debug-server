#include "RuntimeState.h"
#include "ArrayStateNode.h"
#include "Utilities.h"

namespace DarkId::Papyrus::DebugServer
{
	ArrayStateNode::ArrayStateNode(std::string name, RE::BSScript::Array* value, RE::BSScript::TypeInfo* type) :
		m_name(name), m_value(value), m_type(type)
	{
	}

	bool ArrayStateNode::SerializeToProtocol(Variable& variable)
	{
		variable.variablesReference = m_value ? GetId() : 0;
		variable.indexedVariables = m_value ? m_value->size() : 0;

		variable.name = m_name;

		std::string elementTypeName;
#if SKYRIM
		if (m_type->IsObjectArray())
		{
			elementTypeName = m_type->GetTypeInfo()->GetName();
		}
		else
		{
			switch (m_type->GetUnmangledRawType())
			{
			case RE::BSScript::TypeInfo::RawType::kStringArray:
				elementTypeName = "string";
				break;
			case RE::BSScript::TypeInfo::RawType::kIntArray:
				elementTypeName = "int";
				break;
			case RE::BSScript::TypeInfo::RawType::kFloatArray:
				elementTypeName = "float";
				break;
			case RE::BSScript::TypeInfo::RawType::kBoolArray:
				elementTypeName = "bool";
				break;
			default:
				break;
			}
		}
#else // FALLOUT
		if (m_type->IsObjectArray())
		{
			elementTypeName = ((RE::BSScript::ObjectTypeInfo * )m_type->data.complexTypeInfo)->GetName();
		}
		else if (m_type->IsStructArray())
		{
			elementTypeName = ((RE::BSScript::StructTypeInfo * )m_type->data.complexTypeInfo)->GetName();
		}
		else
		{
			switch (m_type->GetRawType())
			{
			case RE::BSScript::TypeInfo::RawType::kArrayString:
				elementTypeName = "string";
				break;
			case RE::BSScript::TypeInfo::RawType::kArrayInt:
				elementTypeName = "int";
				break;
			case RE::BSScript::TypeInfo::RawType::kArrayFloat:
				elementTypeName = "float";
				break;
			case RE::BSScript::TypeInfo::RawType::kArrayBool:
				elementTypeName = "bool";
				break;
			default:
				break;
			}
		}
#endif


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

		node = RuntimeState::CreateNodeForVariable(std::to_string(elementIndex), &(*m_value)[elementIndex]);
		
		return true;
	}
}
