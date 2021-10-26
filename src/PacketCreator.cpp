#include <iostream>
#include <sstream>

#include "PacketCreator.h"
#include "PacketHeaders.h"

using std;

namespace PacketCreator {
   string loginResponce(int pid, string serv_name, string motd) {
      stringstream s(ios_base::in |ios_base::out | ios_base:binary);
      
      s << HEADER_SerVER_LOGIN;
      s << serv_name;
      s << motd;

      return s.str();
   }
}