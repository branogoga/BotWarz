#include "TCPClient.h"
#include "Application.h"

#include "Consts.h"

#include <iostream>
#include <exception>

#pragma comment (lib, "Ws2_32.lib")
#pragma comment (lib, "Mswsock.lib")
#pragma comment (lib, "AdvApi32.lib")

int main()
{
    WSADATA wsa_data;
    // Initialize Winsock
    int res = WSAStartup(MAKEWORD(2, 2), &wsa_data);
    if (res != 0) 
    {
        std::cout << "WSAStartup failed with error: " << res << std::endl;
        return 1;
    }

    try
    {
        Application app;
        app.Execute(TOKEN, NICKNAME);
    }
    catch (std::exception &e)
    {
        std::cout << e.what() << std::endl;
    }

    // Cleanup Winsock
    if (WSACleanup() != 0)
    {
        std::cout << "WSAStartup failed with error: " << WSAGetLastError() << std::endl;
        return 1;
    }

	return 0;
}
