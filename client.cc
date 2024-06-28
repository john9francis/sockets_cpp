#include <iostream>
#include <cstring>

#include <sys/types.h>

#ifdef __linux__
#include <sys/socket.h>
#include <netdb.h>
#endif

#include <string>

#include "server_lin.hh"

#define MYPORT "8080"
#define BACKLOG 10

int main(){
  #ifdef _WIN32
  std::cout << "Hello WIN32 World" << std::endl;
  #endif 
  #ifdef __linux__
  std::cout << "Hello Linux World" << std::endl;
  
  int status;
  int clientSocket;
  struct addrinfo hints;
  struct addrinfo* res;

  struct sockaddr_storage their_addr;
  socklen_t addr_size;

  memset(&hints, 0, sizeof hints);

  hints.ai_family = AF_UNSPEC;
  hints.ai_socktype = SOCK_STREAM;
  hints.ai_flags = AI_PASSIVE;

  if ((status = getaddrinfo(NULL, MYPORT, &hints, &res)) != 0){
    fprintf(stderr, "getaddrinfo error: %s\n", gai_strerror(status));
    exit(1);
  }

  if ((clientSocket = socket(res->ai_family, res->ai_socktype, res->ai_protocol)) == -1){
    std::cerr << "Could not initialize socket." << std::endl;
    exit(1);
  }

  status = connect(clientSocket, res->ai_addr, res->ai_addrlen);

  std::cout
    << "Connected socket: "
    << clientSocket
    << " with code: "
    << status
    << std::endl;

  char response[1024];

  int bytesReceived = -1;
  
  while (bytesReceived <= 0){
    bytesReceived = recv(clientSocket, response, sizeof(response), 0);
  }

  std::cout << "From server: " << response << std::endl;

  // send a message over
  std::string strmsg = "Client says hi!";
  const char* msg = strmsg.c_str();
  int len, bytes_sent;

  len = strlen(msg);
  bytes_sent = send(clientSocket, "Hi from client", len, 0);

  if (bytes_sent != len){
    std::cout << "The whole message wasn't quite sent!" << std::endl;
  }


  #endif

}
