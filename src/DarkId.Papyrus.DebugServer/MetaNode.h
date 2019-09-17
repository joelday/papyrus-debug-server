#pragma once

#include "StateNodeBase.h"

#include <functional>
#include <variant>
#include "Meta.h"

// TODO: Move/reimplement this:
#include "MetaStuff/example/StringCast.h"

namespace DarkId::Papyrus::DebugServer
{
	template<typename T>
	class PrimitiveValueNode;
	
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
			// TODO: get member count as constexpr
			std::vector<std::string> names;
			GetChildNames(names);
			
			variable.variablesReference = GetId();
			variable.namedVariables = names.size();
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

				success = true;
				
				using MemberT = meta::get_member_type<decltype(member)>;
				if (meta::isRegistered<MemberT>())
				{
					node = std::make_shared<MetaNode<MemberT>>(member.getName(), member.get(this->m_value));
				}
				else
				{
					node = std::make_shared<PrimitiveValueNode<MemberT>>(member.getName(), member.getCopy(this->m_value));
				}
			});

			return success;
		}
	};

	template<typename T>
	class PrimitiveValueNode :
		public StateNodeBase,
		public IProtocolVariableSerializable
	{
		std::string m_name;
		T m_value;
		
	public:
		PrimitiveValueNode(std::string name, T value): m_name(name), m_value(value)
		{
		}
		
		~PrimitiveValueNode() override
		{
		}

		bool SerializeToProtocol(Variable& variable) override
		{
			variable.name = m_name;
			variable.type = typeid(T).name();

			if (std::is_convertible<T, bool>() ||
				std::is_convertible<T, int>() ||
				std::is_convertible<T, float>() ||
				std::is_convertible<T, std::string>())
			{
				variable.value = castToString(m_value);
			}
			else
			{
				variable.value = variable.type;
			}
			
			return true;
		}
	};
}
