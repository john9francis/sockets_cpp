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

  #define MYPORT "8080"

  struct addrinfo hints, *res;
  ZeroMemory(&hints, sizeof(hints));
  hints.ai_family = AF_INET;
  hints.ai_socktype = SOCK_STREAM;
  hints.ai_protocol = IPPROTO_TCP;
  hints.ai_flags = AI_PASSIVE;

  iResult = getaddrinfo(NULL, MYPORT, &hints, &res);
  if (iResult != 0){
    std::cout << "get addr info failed: " << iResult << std::endl;
    WSACleanup();
    return 1;
  }

  std::cout << "get addr info succeeded" << std::endl;

  return 0;
}
} // !WindowsSockets