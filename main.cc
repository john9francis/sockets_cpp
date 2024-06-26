#include <iostream>
#include <cstring>

#include <sys/types.h>

#ifdef __linux__
#include <sys/socket.h>
#include <netdb.h>
#endif

#include "server_lin.hh"

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

  memset(&hints, 0, sizeof hints);

  hints.ai_family = AF_UNSPEC;
  hints.ai_socktype = SOCK_STREAM;
  hints.ai_flags = AI_PASSIVE;

  if ((status = getaddrinfo(NULL, "8080", &hints, &res)) != 0){
    fprintf(stderr, "getaddrinfo error: %s\n", gai_strerror(status));
    exit(1);
  }

  if ((sock = socket(res->ai_family, res->ai_socktype, res->ai_protocol)) == -1){
    std::cerr << "Could not initialize socket." << std::endl;
    exit(1);
  }
  
  if ((status = bind(sock, res->ai_addr, res->ai_addrlen)) != 0){
    fprintf(stderr, "bind error: %s\n", gai_strerror(status));
  }

  std::cout
    << "Bound socket: "
    << sock
    << " with code: "
    << status
    << std::endl;


  listen(sock, 10);


  #endif

}
