#include <iostream>

#include <WinSock2.h>
#include <WS2tcpip.h>

namespace WindowsSockets {

int client(){
  std::cout << "Hello Windows World" << std::endl;

  WSADATA wsaData;

  int iResult;

  iResult = WSAStartup(MAKEWORD(2,2), &wsaData);
  if (iResult != 0){
    std::cout << "WSAStartup failed: " << iResult << std::endl;
    return 1;
  }

  struct addrinfo *res, hints;

  memset(&hints, 0, sizeof hints);
  hints.ai_family = AF_UNSPEC;
  hints.ai_socktype = SOCK_STREAM;
  hints.ai_protocol = IPPROTO_TCP;

  #define MYPORT "8080"

  iResult = getaddrinfo(/*argv[1]*/ NULL, MYPORT, &hints, &res);
  if (iResult != 0){
    std::cout << "getaddrinfo failed: " << iResult << std::endl;
    WSACleanup();
    return 1;
  }

  SOCKET connectSocket = INVALID_SOCKET;

  connectSocket = socket(res->ai_family, res->ai_socktype, res->ai_protocol);

  if (connectSocket == INVALID_SOCKET){
    std::cout << "Error creating socket: " << WSAGetLastError() << std::endl;
    freeaddrinfo(res);
    WSACleanup();
    return 1;
  }

  iResult = connect(connectSocket, res->ai_addr, (int)res->ai_addrlen);
  if (iResult == SOCKET_ERROR){
    closesocket(connectSocket);
    connectSocket = INVALID_SOCKET;
  }

  // from winsock tutorial:
  // =======================
  // Should really try the next address returned by getaddrinfo
  // if the connect call failed
  // But for this simple example we just free the resources
  // returned by getaddrinfo and print an error message


  char response[1024];

  int bytesReceived = -1;
  
  while (bytesReceived <= 0){
    bytesReceived = recv(connectSocket, response, sizeof(response), 0);
  }

  std::cout << "From server: " << response << std::endl;

  // send a message over
  std::string strmsg = "Client says hi!";
  const char* msg = strmsg.c_str();
  int len, bytes_sent;

  len = strlen(msg);
  bytes_sent = send(connectSocket, "Hi from client", len, 0);

  if (bytes_sent != len){
    std::cout << "The whole message wasn't quite sent!" << std::endl;
  }

  return 0;
}
} // !WindowsSockets