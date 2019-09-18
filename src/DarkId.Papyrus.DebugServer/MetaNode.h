#pragma once

#include "StateNodeBase.h"

#include <functional>
#include <variant>
#include "Meta.h"
#include "Utilities.h"

namespace DarkId::Papyrus::DebugServer
{
	template<typename T>
	class PlainValueNode;
	
	template<class Class>
	class MetaNode :
		public StateNodeBase,
		public IProtocolVariableSerializable,
		public IStructuredState
	{
		std::string m_name;
		const Class& m_value;
		
	public:
		MetaNode(std::string name, const Class& value) : m_name(name), m_value(value)
		{
		}
		
		~MetaNode() override
		{
		}

		bool SerializeToProtocol(Variable& variable) override
		{
			variable.variablesReference = GetId();
			variable.namedVariables = meta::getMemberCount<Class>();
			variable.name = m_name;
			variable.value = typeid(Class).name();

			return true;
		}

		bool GetChildNames(std::vector<std::string>& names) override
		{
			meta::doForAllMembers<Class>([&names](auto& member)
			{
				names.push_back(member.getName());
			});
			
			return true;
		}

		bool GetChildNode(std::string name, std::shared_ptr<StateNodeBase>& node) override
		{
			auto success = false;
			
			meta::doForAllMembers<Class>([this, &success, &name, &node](auto& member)
			{
				if (!CaseInsensitiveEquals(name, member.getName()))
				{
					return;
				}

				using MemberT = meta::get_member_type<decltype(member)>;
				if (meta::isRegistered<MemberT>())
				{
					node = std::make_shared<MetaNode<MemberT>>(member.getName(), member.get(this->m_value));
					success = true;
				}
				else if (!std::is_abstract<MemberT>())
				{
					node = std::make_shared<PlainValueNode<MemberT>>(member.getName(), member.get(this->m_value));
					success = true;
				}
			});

			return success;
		}
	};

	template<typename T>
	class PlainValueNode :
		public StateNodeBase,
		public IProtocolVariableSerializable
	{
		std::string m_name;
		const T& m_value;
		
	public:
		PlainValueNode(std::string name, const T& value): m_name(name), m_value(value)
		{
		}
		
		~PlainValueNode() override
		{
		}

		bool SerializeToProtocol(Variable& variable) override
		{
			variable.name = m_name;
			variable.type = typeid(T).name();

			if constexpr (std::is_same<T, bool>())
			{
				variable.value = m_value ? "true" : "false";
			}
			else if constexpr (std::is_same<T, RE::BSFixedString>() || std::is_same<T, BSFixedString>())
			{
				variable.value = "\"" + std::string(m_value.c_str()) + "\"";
			}
			else if constexpr (std::is_integral<T>())
			{
				variable.value = StringFormat("%d", static_cast<int>(m_value));
			}
			else if constexpr (std::is_floating_point<T>())
			{
				variable.value = StringFormat("%f", static_cast<float>(m_value));
			}
			else if constexpr (std::is_convertible<T, std::string>())
			{
				variable.value = "\"" + std::string(m_value) + "\"";
			}
			else
			{
				variable.value = variable.type;
			}
			
			return true;
		}
	};
}
