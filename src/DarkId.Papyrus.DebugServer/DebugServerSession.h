#pragma once
#include "f4se/PluginAPI.h"
#include "PapyrusDebugger.h"
#include "protocol/vscodeprotocol.h"

namespace DarkId::Papyrus::DebugServer
{
	class DebugServerSession
	{
		PapyrusDebugger* m_debugger;
		VSCodeProtocol* m_protocol;

		HANDLE m_thread;

		static DWORD WINAPI CommandLoopThreadStart(void* param);
	public:
		DebugServerSession(std::function<void(std::string)> sendCallback, F4SETaskInterface* tasks);
		
		void Receive(std::string message);
		void Close();

		~DebugServerSession();
	};
}