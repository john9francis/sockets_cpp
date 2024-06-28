#include <iostream>
#include <cstring>

#include <sys/types.h>

#include <string>

#ifdef __linux__
#include <sys/socket.h>
#include <netdb.h>
#endif

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
  int serverSocket;
  struct addrinfo hints;
  struct addrinfo* res;

  struct sockaddr_storage their_addr;
  socklen_t addr_size;

  int clientSocket;

  memset(&hints, 0, sizeof hints);

  hints.ai_family = AF_UNSPEC;
  hints.ai_socktype = SOCK_STREAM;
  hints.ai_flags = AI_PASSIVE;

  if ((status = getaddrinfo(NULL, MYPORT, &hints, &res)) != 0){
    fprintf(stderr, "getaddrinfo error: %s\n", gai_strerror(status));
    exit(1);
  }

  if ((serverSocket = socket(res->ai_family, res->ai_socktype, res->ai_protocol)) == -1){
    std::cerr << "Could not initialize socket." << std::endl;
    exit(1);
  }
  
  if ((status = bind(serverSocket, res->ai_addr, res->ai_addrlen)) != 0){
    fprintf(stderr, "bind error: %s\n", gai_strerror(status));
  }

  std::cout
    << "Bound socket: "
    << serverSocket
    << " with code: "
    << status
    << std::endl;


  std::cout << "Listening on port: " << MYPORT << std::endl;
  listen(serverSocket, BACKLOG);

  addr_size = sizeof their_addr;
  clientSocket = accept(serverSocket, (struct sockaddr*)&their_addr, &addr_size);

  // send a message over
  std::string strmsg = "Server says Hey!";
  const char* msg = strmsg.c_str();
  int len, bytes_sent;

  len = strlen(msg);
  bytes_sent = send(clientSocket, "Hey from server", len, 0);

  if (bytes_sent != len){
    std::cout << "The whole message wasn't quite sent!" << std::endl;
  }
  else {
    std::cout << "Sent message" << std::endl;
  }

  char response[1024] = {0};

  int bytes_recieved = -1;

  while (bytes_recieved <= 0){
    bytes_recieved = recv(clientSocket, response, sizeof(response), 0);
  }

  std::cout << response << std::endl;

  #endif

}
