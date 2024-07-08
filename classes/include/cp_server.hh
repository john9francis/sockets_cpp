#ifndef CP_SERVER_HH
#define CP_SERVER_HH

#include <iostream>
#include "cross_platform_sockets.hh"

#include <list>
#include <thread>

class Server {
public:
  Server();
  ~Server();

private:
  int Init();
  void AcceptConnections();
  void SendMessages();

  std::list<int> sockets;
};

#endif // ! CP_SERVER_HH