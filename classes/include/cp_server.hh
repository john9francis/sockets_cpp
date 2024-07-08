#ifndef CP_SERVER_HH
#define CP_SERVER_HH

#include <iostream>
#include "cross_platform_sockets.hh"

class Server {
public:
  Server();

private:
  int Init();
  void AcceptConnections(){};
};

#endif // ! CP_SERVER_HH