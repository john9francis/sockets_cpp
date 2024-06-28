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
  int sock;
  struct addrinfo hints;
  struct addrinfo* res;

  struct sockaddr_storage their_addr;
  socklen_t addr_size;

  int new_sock;

  memset(&hints, 0, sizeof hints);

  hints.ai_family = AF_UNSPEC;
  hints.ai_socktype = SOCK_STREAM;
  hints.ai_flags = AI_PASSIVE;

  if ((status = getaddrinfo(NULL, MYPORT, &hints, &res)) != 0){
    fprintf(stderr, "getaddrinfo error: %s\n", gai_strerror(status));
    exit(1);
  }

  if ((sock = socket(res->ai_family, res->ai_socktype, res->ai_protocol)) == -1){
    std::cerr << "Could not initialize socket." << std::endl;
    exit(1);
  }

  status = connect(sock, res->ai_addr, res->ai_addrlen);

  std::cout
    << "Bound socket: "
    << sock
    << " with code: "
    << status
    << std::endl;

  char* response[100];

  recv(new_sock, response, 100, 0);

  std::cout << response << std::endl;

  // send a message over
  std::string strmsg = "Hey!";
  const char* msg = strmsg.c_str();
  int len, bytes_sent;

  len = strlen(msg);
  bytes_sent = send(new_sock, &strmsg, len, 0);

  if (bytes_sent != len){
    std::cout << "The whole message wasn't quite sent!" << std::endl;
  }


  #endif

}
