#ifndef PACKET_CREATOR_H
#define PACKET_CREATOR_H

#include <string>

namespace PacketCreator {
   std::string loginResponce(int pid, std::string serv_name, std::string motd);
}

#endif