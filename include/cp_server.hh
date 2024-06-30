#include "cross_platform_sockets.hh"
#include "iostream"

int server(){
  std::cout << "Hello Cross Platform Server" << std::endl;

  int status;
  status = cp_init();
  if (status != 0){
    std::cout << "Did not init correctly: " << status << std::endl;
    return 0;
  }

  struct addrinfo hints, *res;
  
  hints = cp_get_hints();

  status = getaddrinfo(NULL, MYPORT, &hints, &res);
  if (status != 0){
    std::cout << "get addr info failed: " << status << std::endl;
    return 1;
  }

  std::cout << "get addr info succeeded" << std::endl;

  int listenSocket = -1;
  listenSocket = socket(res->ai_family, res->ai_socktype, res->ai_protocol);
  if (listenSocket == -1){
    std::cout << "Error creating listen socket: " << std::endl;
    freeaddrinfo(res);
    return 1;
  }

  std::cout << "listen socket created" << std::endl;

  status = bind(listenSocket, res->ai_addr, (int)res->ai_addrlen);
  if (status == -1){
    std::cout << "Bind error, perhaps port already in use." << std::endl;
    freeaddrinfo(res);
    cp_close(listenSocket);
    return 1;
  }

  std::cout << "Bound socket successfully" << std::endl;
  freeaddrinfo(res);

  std::cout << "Listening..." << std::endl;

  if (listen(listenSocket, 100) == -1){
    std::cout << "Listen error" << std::endl;
    cp_close(listenSocket);
    return 1;
  }

  int clientSocket = -1;

  clientSocket = accept(listenSocket, NULL, NULL);

  if (clientSocket == -1){
    std::cout << "Accept failed" << std::endl;
    cp_close(listenSocket);
    return 1; 
  }

  std::cout << "client connected" << std::endl;

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

  //  shut down:
  // status = shutdown(clientSocket, SD_BOTH);
  // if (status == -1){
  //   std::cout << "Shutdown failed" << std::endl;
  //   cp_close(clientSocket);
  //   return 1;
  // }

  cp_close(clientSocket);
  return 0;
}