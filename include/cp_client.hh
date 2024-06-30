#include "cross_platform_sockets.hh"
#include <iostream>


int client(){
  std::cout << "Hello Cross Platform Client" << std::endl;

  int status;

  status = cp_init();
  if (status != 0){
    std::cout << "init failed: " << status << std::endl;
    return 1;
  }

  struct addrinfo *res, hints;

  hints = cp_get_hints();

  status = getaddrinfo(/*argv[1]*/ NULL, MYPORT, &hints, &res);
  if (status != 0){
    std::cout << "getaddrinfo failed: " << status << std::endl;
    return 1;
  }

  int connectSocket = -1;

  connectSocket = socket(res->ai_family, res->ai_socktype, res->ai_protocol);

  if (connectSocket == -1){
    std::cout << "Error creating socket: " << std::endl;
    freeaddrinfo(res);
    return 1;
  }

  status = connect(connectSocket, res->ai_addr, res->ai_addrlen);
  if (status == -1){
    std::cout << "Error connecting client to socket" << std::endl;
    cp_close(connectSocket);
    connectSocket = -1;
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