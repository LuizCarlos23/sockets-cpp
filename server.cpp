//default c++
#include <iostream>
#include <cstring> // for strcpy()
#include <cstdio> // for perror()
//socket
#include <sys/socket.h> // for socket()...
#include <sys/types.h>
#include <netinet/in.h> // for sockaddr_in
#include <unistd.h> // for close()

#define PORT 6565
#define BUFF 256

void error(std::string);

int main(int argc, char *argv[])
{
    int SocketFd, SocketClientFd, iResult;      
    struct sockaddr_in SocketAddrIn = { 0 }, SocketClientAddr = { 0 };
    socklen_t SocketClientAddrLen = sizeof SocketClientAddr;
    char ClientBuff[BUFF], ServerBuff[BUFF]; 

    SocketAddrIn = {
        sin_family: AF_INET,
        sin_port: htons(PORT)
    };
    SocketAddrIn.sin_addr.s_addr = htonl(INADDR_ANY), // Accept any address


    SocketFd = socket(AF_INET, SOCK_STREAM, 0); // Socket creation
    SocketFd >= 0 
        ? (void)(std::cout << "Socket created\n")
        : error("ERROR creating socket");


    iResult = bind(SocketFd, (struct sockaddr *)&SocketAddrIn, sizeof SocketAddrIn); // Binding socket to a system port
    iResult >= 0
        ? (void)(std::cout << "Bind done\n")
        : error("ERROR in bind");

    listen(SocketFd, 5);

    SocketClientFd = accept(SocketFd, (struct sockaddr *)&SocketClientAddr, &SocketClientAddrLen);

    SocketClientFd >= 0
        ? (void)(std::cout << "Client connected")
        : error("ERROR connection");

    iResult = recv(SocketClientFd, ClientBuff, sizeof ClientBuff, 0);
    
    iResult >= 0
        ? (void)(std::cout << "Message: " << ClientBuff)
        : (void)(std::cout << "ERROR in read  message\n");

    strcpy(ServerBuff, ClientBuff);

    iResult = send(SocketClientFd, ServerBuff, sizeof ServerBuff, 0);
    iResult >= 0
        ? (void)(std::cout << "\nMenssage sent\n")
        : (void)(std::cout << "ERROR in send message");

    shutdown(SocketClientFd, SHUT_RDWR);
    close(SocketFd);

    return 0;
}

void error(std::string msg)
{
    perror(msg.c_str());
    exit(1);
}