#pragma once

#define WIN32_LEAN_AND_MEAN

#include "Utils.h"
#include "Logger.h"

#include <boost/noncopyable.hpp>

#include <windows.h>
#include <winsock2.h>
#include <ws2tcpip.h>

#include <exception>
#include <fstream>
#include <memory>
#include <stdlib.h>
#include <string>

class TCPClient : boost::noncopyable
{
public:

	TCPClient(
        const char *server, 
        const char *port
        )
	{
        ADDRINFOA *result = nullptr;
        ADDRINFOA *ptr = nullptr;

        ADDRINFOA hints{};
        hints.ai_family = AF_UNSPEC;
        hints.ai_socktype = SOCK_STREAM;
        hints.ai_protocol = IPPROTO_TCP;

        // Resolve the server address and port
        int res = getaddrinfo(server, port, &hints, &result);
        if (res != 0)
        {
            throw std::runtime_error((std::string("getaddrinfo failed with error: ") + std::to_string(res)).c_str());
        }

        // Attempt to connect to an address until one succeeds
        for (ptr = result; ptr != nullptr; ptr = ptr->ai_next)
        {
            // Create a SOCKET for connecting to server
            m_socket = socket(ptr->ai_family, ptr->ai_socktype, ptr->ai_protocol);
            if (m_socket == INVALID_SOCKET)
            {
                throw std::runtime_error((std::string("socket failed with error: ") + std::to_string(WSAGetLastError())).c_str());
            }

            // Connect to server.
            res = connect(m_socket, ptr->ai_addr, (int)ptr->ai_addrlen);
            if (res == SOCKET_ERROR)
            {
                closesocket(m_socket);
                m_socket = INVALID_SOCKET;
                continue;
            }
            break;
        }

        freeaddrinfo(result); // possible leak

        if (m_socket == INVALID_SOCKET)
        {
            throw std::runtime_error("Unable to connect to server!");
        }

        SetTcpNoDelay();
	}

	~TCPClient()
	{
        if (m_socket != INVALID_SOCKET)
        {
            closesocket(m_socket);
        }
	}

	void Send(const std::string & data)
	{
        if (send(m_socket, data.c_str(), static_cast<int>(data.size()), 0) == SOCKET_ERROR) 
        {
            throw std::runtime_error((std::string("send failed with error: ") + std::to_string(WSAGetLastError())).c_str());
		}

        if (m_pInputLogger)
        {
            *m_pInputLogger << data;
        }
	}

	std::string ReceiveLine()
	{
		char recvbuf[2048];

        WHILE_TRUE
        {
            size_t pos = m_buffer.find_first_of('\n');
            if (pos != std::string::npos)
            {
                std::string result = m_buffer.substr(0, pos);
                m_buffer.erase(0, pos + 1); // + 1 for '\n'

                if (m_pOutputLogger)
                {
                    *m_pOutputLogger << result << std::endl;
                }

                return result;
            }

            int iResult = recv(m_socket, recvbuf, sizeof(recvbuf), 0);
            if (iResult > 0)
            {
                m_buffer.append(recvbuf, recvbuf + iResult);
            }
            else if (iResult == 0)
            {
                throw std::runtime_error("Connection closed");
            }
            else
            {
                throw std::runtime_error((std::string("recv failed with error: ") + std::to_string(WSAGetLastError())).c_str());
            }
        }
	}

    bool WaitForMessage(DWORD timeout)
    {
        size_t pos = m_buffer.find_first_of('\n');
        if (pos != std::string::npos)
        {
            // we have message in buffer
            return true;
        }

        // otherwise wait for socket
        timeval t;
        t.tv_sec = 0;
        t.tv_usec = timeout * 1000;

        FD_SET ReadSet;
        FD_ZERO(&ReadSet);
        FD_SET(m_socket, &ReadSet);

        int ret = select(0, &ReadSet, nullptr, nullptr, &t);
        if (ret == SOCKET_ERROR)
        {
            throw std::runtime_error("select failed with SOCKET_ERROR");
        }

        return ret == 1;
    }

    void setInputLogger(std::shared_ptr<Logger> i_pLogger)
    {
        m_pInputLogger = i_pLogger;
    }

    void setOutputLogger(std::shared_ptr<Logger> i_pLogger)
    {
        m_pOutputLogger = i_pLogger;
    }

private:

	void SetTcpNoDelay()
	{
		int opt = 1;
		if (setsockopt(m_socket, IPPROTO_TCP, TCP_NODELAY, (const char*)&opt, sizeof(int)))
		{
            throw std::exception("Set TCP_NDELAY to socket failed.");
		}
	}

	SOCKET m_socket;
    std::string m_buffer;

    std::shared_ptr<Logger> m_pInputLogger;
    std::shared_ptr<Logger> m_pOutputLogger;
};