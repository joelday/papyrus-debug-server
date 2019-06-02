#pragma once

#include "Websocket.h"
#include "DebugServerSession.h"

namespace DarkId::Papyrus::DebugServer
{
    class DebugServer
    {
    public:
		DebugServer(F4SETaskInterface* tasks);
        ~DebugServer();

        bool Listen();
    private:
		F4SETaskInterface* m_tasks;
		DebugServerSession* m_session;

        HANDLE m_thread;
        server m_server;

		websocketpp::connection_hdl m_connectionHandle;

		std::basic_streambuf<char>* m_streamBuffer;

        UInt32 ListenInternal();
		
		void Send(std::string message);

        void HandleMessage(websocketpp::connection_hdl hdl, message_ptr msg);
        void HandleOpen(websocketpp::connection_hdl hdl);
        void HandleClose(websocketpp::connection_hdl hdl);

		static DWORD WINAPI ListenThreadStart(void* param);
    };
}