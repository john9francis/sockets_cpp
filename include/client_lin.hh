#pragma once

#include <string>

// a client that continually receives messages from the server
// and then responds with an OK
class ClientLin {
public:
  ClientLin();
  ~ClientLin();

private:
  int Init();
  void Connect();
  int SendString(std::string);
  std::string RecvString();

  int clientSocket;
};