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
  hints.ai_family = AF_UNSPEC;
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

  SOCKET listenSocket = INVALID_SOCKET;
  listenSocket = socket(res->ai_family, res->ai_socktype, res->ai_protocol);
  if (listenSocket == INVALID_SOCKET){
    std::cout << "Error creating listen socket: " << WSAGetLastError() << std::endl;
    freeaddrinfo(res);
    WSACleanup();
    return 1;
  }

  std::cout << "listen socket created" << std::endl;

  iResult = bind(listenSocket, res->ai_addr, (int)res->ai_addrlen);
  if (iResult == -1){
    std::cout << "Bind error: " << WSAGetLastError() << std::endl;
    freeaddrinfo(res);
    closesocket(listenSocket);
    WSACleanup();
    return 1;
  }

  std::cout << "Bound socket successfully" << std::endl;
  freeaddrinfo(res);

  std::cout << "Listening..." << std::endl;

  // if (listen(listenSocket, 100) == -1){
  //   std::cout << "Listen error: " << WSAGetLastError() << std::endl;
  //   closesocket(listenSocket);
  //   WSACleanup();
  //   return 1;
  // }

  listen(listenSocket, 100);

  SOCKET clientSocket = INVALID_SOCKET;

  clientSocket = accept(listenSocket, NULL, NULL);

  if (clientSocket == INVALID_SOCKET){
    std::cout << "Accept failed: " << WSAGetLastError() << std::endl;
    closesocket(listenSocket);
    WSACleanup();
    return 1; 
  }

  std::cout << "client connected" << std::endl;

  return 0;
}
} // !WindowsSockets