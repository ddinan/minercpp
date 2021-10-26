#ifndef CLIENT_H
#define CLIENT_H

#include <string>

class Client {
private:
   int socket;
public:
   Client();
   ~Client();

   bool write(std::string data);

}

#endif