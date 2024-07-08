#include "cp_server.hh"

Server::Server(){
  std::cout << "Hello Server" << std::endl;
  Init();
}

int Server::Init(){
  int status;

  status = cp_init();
  if (status != 0){
    std::cout << "Did not init correctly: " << status << std::endl;
    return 1;
  }

  struct addrinfo hints, *res, *rp;
  
  hints = cp_get_hints();

  status = getaddrinfo(0, "8080", &hints, &res); // hardcoded
  if (status != 0){
    std::cout << "get addr info failed: " << status << std::endl;
    return 1;
  }

  std::cout << "get addr info succeeded" << std::endl;

  int listenSocket = -1;
  for (rp=res; rp != NULL; rp = rp->ai_next){
    listenSocket = socket(rp->ai_family, rp->ai_socktype, rp->ai_protocol);

    if (listenSocket == -1) continue;

    if (bind(listenSocket, rp->ai_addr, rp->ai_addrlen) == 0) break;

    cp_close(listenSocket);
  }
  
  if (rp == NULL){
    std::cout << "Could not bind" << std::endl;
    return 1;
  }

  std::cout << "Bound socket successfully" << std::endl;
  
  char hostname[100];
  char portname[100];
  getnameinfo(res->ai_addr, res->ai_addrlen, hostname, sizeof hostname, portname, sizeof portname, NI_NUMERICHOST | NI_NUMERICSERV);

  std::cout << "HOST: " << hostname << " PORT: " << portname << std::endl;

  freeaddrinfo(res);


  if (listenSocket == -1){
    std::cout << "Error creating listen socket: " << std::endl;
    return 1;
  }

  std::cout << "listen socket created" << std::endl;
  
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

  return 0;
}