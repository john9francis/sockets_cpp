#pragma once

#include <string>

// server built to run on a linux machine
// note: this server only accepts one client
class ServerLin {
public:
  ServerLin();
  ~ServerLin();

  int SendMsgToClient();

private:
  int Init();
  void Listen();
  int SendString(std::string);
  std::string RecvString();

  int clientSocket;
};