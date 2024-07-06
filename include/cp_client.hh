#include "cross_platform_sockets.hh"
#include <iostream>


int client(int argc, char *argv[]){
  std::cout << "Hello Cross Platform Client" << std::endl;
  if (argc < 3){
    std::cout << "Please specify the server's ip and the port, aka: ./client 1.2.3 8080" << std::endl;
    return 1;
  }

  int status;

  status = cp_init();
  if (status != 0){
    std::cout << "init failed: " << status << std::endl;
    return 1;
  }

  struct addrinfo *res, hints;

  hints = cp_get_hints();

  status = getaddrinfo(argv[1], argv[2], &hints, &res);
  if (status != 0){
    std::cout << "getaddrinfo failed: " << status << std::endl;
    return 1;
  }

  int connectSocket = -1; // note: need to typedef cp_socket

  connectSocket = socket(res->ai_family, res->ai_socktype, res->ai_protocol);

  if (connectSocket == -1){
    std::cout << "Error creating socket: " << std::endl;
    freeaddrinfo(res);
    return 1;
  }

  char hostname[100];
  char portname[100];
  getnameinfo(res->ai_addr, res->ai_addrlen, hostname, sizeof hostname, portname, sizeof portname, NI_NUMERICHOST | NI_NUMERICSERV);

  std::cout << "HOST: " << hostname << " PORT: " << portname << std::endl;

  status = -1;
  int counter = 0;
  while (status == -1 && counter < 10){
    status = connect(connectSocket, res->ai_addr, res->ai_addrlen);
    if (status == -1){
      std::cout << "Error connecting client to socket: " << cp_get_last_error() << std::endl;
      cp_close(connectSocket);
      connectSocket = -1;
      counter ++;
    }
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