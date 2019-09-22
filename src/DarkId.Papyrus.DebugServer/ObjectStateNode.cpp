#include "ObjectStateNode.h"
#include "Utilities.h"
#include "RuntimeState.h"

#include "FormMetadata.h"
#include "MetaNode.h"

namespace DarkId::Papyrus::DebugServer
{
	ObjectStateNode::ObjectStateNode(const std::string name, RE::BSScript::Object* value, RE::BSScript::ObjectTypeInfo* asClass, const bool subView) :
		m_name(name), m_subView(subView), m_value(value), m_class(asClass)
	{
		if (m_value && !m_subView)
		{
			m_class = RE::BSTSmartPointer<RE::BSScript::ObjectTypeInfo>(m_value->GetClass());
		}
	}

	bool ObjectStateNode::SerializeToProtocol(Variable& variable)
	{
		variable.variablesReference = m_value ? GetId() : 0;
		
		variable.name = m_name;
		variable.type = m_class->GetName();

		if (m_value)
		{
			std::vector<std::string> childNames;
			GetChildNames(childNames);

			variable.namedVariables = childNames.size();

			if (!m_subView)
			{
				auto vm = RE::BSScript::Internal::VirtualMachine::GetSingleton();
				const auto handle = vm->GetHandle(m_value);

				variable.value = StringFormat("%s (%08x)", m_class->GetName(), static_cast<UInt32>(handle ^ 0x0000FFFF00000000));
			}
			else
			{
				variable.value = variable.type;
			}
		}
		else
		{
			variable.value = "None";
		}
		
		return true;
	}

	bool ObjectStateNode::GetChildNames(std::vector<std::string>& names)
	{
		if (!m_value)
		{
			return true;
		}
		
#if SKYRIM
		auto vm = RE::BSScript::Internal::VirtualMachine::GetSingleton();
		
		RE::FormType32 formType;
		if (vm->GetFormTypeID(m_class->name, formType))
		{
			auto form = static_cast<RE::TESForm*>(vm->GetHandlePolicy()->Resolve(formType, vm->GetHandle(m_value)));

			// TODO: Display strings
			// TODO: Verify behavior for the handful of polymorphic types that share the same form type
#define STRING(s) #s
#define DEFINE_FORM_TYPE_CHECK(type)  \
			if constexpr (meta::isRegistered<##type##>()) \
			{\
				auto asType = form->As<##type##*>(); \
				if (asType) \
				{ \
					names.push_back(STRING(type)); \
				} \
			}\

			FORM_TYPE_LIST(DEFINE_FORM_TYPE_CHECK)
#undef DEFINE_FORM_TYPE_CHECK
#undef STRING
		}
#endif
		
		if (m_class->parent)
		{
			names.push_back("parent");
		}

		const auto variableIter = m_class->GetVariableIter();
		for (auto i = 0; i < m_class->GetNumVariables(); i++)
		{
			auto variable = variableIter[i];
			names.push_back(DemangleName(variable.name.c_str()));
		}

		return true;
	}

	bool ObjectStateNode::GetChildNode(std::string name, std::shared_ptr<StateNodeBase>& node)
	{
#if SKYRIM
		auto vm = RE::BSScript::Internal::VirtualMachine::GetSingleton();

		RE::FormType32 formType;
		if (m_value && vm->GetFormTypeID(m_class->name, formType))
		{
			
#define STRING(s) #s
#define DEFINE_FORM_TYPE_CHECK(type)  \
			if (CaseInsensitiveEquals(name, STRING(type))) \
			{\
				auto form = static_cast<##type##*>(vm->GetHandlePolicy()->Resolve(formType, vm->GetHandle(m_value))); \
				node = std::make_shared<MetaNode<##type##*>>(STRING(type), form); \
 				return true; \
			}\

			FORM_TYPE_LIST(DEFINE_FORM_TYPE_CHECK)
#undef DEFINE_FORM_TYPE_CHECK
#undef STRING
			
		}
#endif
		
		if (m_value && m_class->parent && CaseInsensitiveEquals(name, "parent"))
		{
			node = std::make_shared<ObjectStateNode>("parent", m_value.get(), m_class->parent.get(), true);
			return true;
		}
		
		const auto type = m_value->GetClass();

		const auto variableIter = type->GetVariableIter();
		for (auto i = 0; i < type->GetNumVariables(); i++)
		{
			const auto variable = &variableIter[i];
			const auto demangledName = DemangleName(variable->name.c_str());

			if (CaseInsensitiveEquals(name, demangledName))
			{
				const auto variableValue = &m_value->variables[i];
				node = RuntimeState::CreateNodeForVariable(demangledName, variableValue);
				return true;
			}
		}

		return false;
	}
}
