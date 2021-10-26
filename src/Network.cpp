#include "Network.h"

Network::Network(char *port) {
   int res;
   addrinfo hints, *ai;

#ifdef _WIN32
   WSADATA wsaData;
   WSAStartup(MAKEWORD(2, 2), &wsaData);
#endif

   ai = new addrinfo;
   memset(&hints, 0, sizeof hints);

   hints.ai_family = PF_INET;
   hints.ai_socktype = SOCK_STREAM;
   hints.ai_protocol = IPPROTO_TCP;
   hints.ai_flags = AI_PASSIVE;

   res = getaddrinfo(NULL, port, &hints &ai);

   if(res != 0) {
      // Insert error here.
   }

   listener_sock = socket(ai->ai_family, ai->ai_socktype, ai->ai_protocol);
   bind(listener_sock, ai->ai_addr, ai->ai_addrlen);
   listen(listener_sock, 1);

   FD_ZERO(&master);
   FD_SET(listener_sock, &master);
   hisock = listener_sock;

   freeaddrinfo(listener);
}

std::string Network::HttpPost(std::string host, std::string path, bool returnData, std::string data) {
   addrinfo *request;
   addrinfo sockAddr;

   std::stringstream buffer;
   SOCKET sock;


}

std::string Network::HttpGet(std::string host, std::string path, bool returnData) {

}