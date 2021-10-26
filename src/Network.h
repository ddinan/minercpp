#ifndef NETWORK_H
#define NETWORK_H

#include <string>
#ifdef _WIN32
   #include <winsock2.h>
   #include <ws2tcpip.h>
   #define closesock(sock) closesocket(sock)
#else
   #include <arpa/inet.h>
   #include <sys/socket.h>
   #include <netinet/in.h>
   #include <sys/types.h>
   #define SOCKET int
   #define closesock(sock) close(sock)
#endif

class Network {
private:
   SOCKET listener_sock;
   fd_set master;
   int hisock;

public:
   Network(char* port);
   ~Network();

   std::string HttpPost(std::string host, std::string path, bool returnData, std::string data);
   std::string HttpGet(std::string host, std::string path, bool returnData);
}

#endif