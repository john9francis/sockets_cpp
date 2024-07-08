#ifndef CP_CLIENT_HH
#define CP_CLIENT_HH

#include <iostream>

class Client {
public:
  Client(char* host, char* port);

private:
  int Init();
};


#endif