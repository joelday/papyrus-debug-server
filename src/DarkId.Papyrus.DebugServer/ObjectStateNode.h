#pragma once

#include "GameInterfaces.h"
#include "protocol/protocol.h"

#include "StateNodeBase.h"

namespace DarkId::Papyrus::DebugServer
{
	class ObjectStateNode : public StateNodeBase, public IProtocolVariableSerializable, public IStructuredState
	{
		std::string m_name;

		RE::BSTSmartPointer<RE::BSScript::Object> m_value;
		RE::BSTSmartPointer<RE::BSScript::ObjectTypeInfo> m_class;
	public:
		ObjectStateNode(std::string name, RE::BSScript::Object* value, RE::BSScript::ObjectTypeInfo* asClass, bool forceClass = false);

		bool SerializeToProtocol(Variable& variable) override;

		bool GetChildNames(std::vector<std::string>& names) override;
		bool GetChildNode(std::string name, std::shared_ptr<StateNodeBase>& node) override;
	};
}