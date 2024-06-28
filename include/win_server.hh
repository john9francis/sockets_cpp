#include <iostream>

#include <WinSock2.h>
#include <WS2tcpip.h>

namespace WindowsSockets {

int server(){
  std::cout << "Hello Windows World" << std::endl;

  WSADATA wsaData;

  int iResult;

  iResult = WSAStartup(MAKEWORD(2,2), &wsaData);
  if (iResult != 0){
    std::cout << "WSAStartup failed: " << iResult << std::endl;
    return 1;
  }

  std::cout << "Successfully started WSA so the dll is present" << std::endl;

  return 0;
}
} // !WindowsSockets