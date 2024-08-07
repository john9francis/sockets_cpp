#include "cp_server.hh"

Server::Server(){
  std::cout << "Hello Server" << std::endl;

  Init(); // stops main function execution

  // runs concurrently with the rest of the main function
  listenThread = std::thread(&Server::AcceptConnections, this);
  sendDataThread = std::thread(&Server::SendMessages, this);

}

Server::~Server(){
  Stop();
  listenThread.join();
  sendDataThread.join();
}

void Server::AcceptConnections(){
  while (running){
    
    int clientSocket = -1;
    clientSocket = accept(listenSocket, NULL, NULL);

    if (clientSocket == -1){
      std::cout << "Accept failed" << std::endl;
    }

    std::cout << "client connected" << std::endl;

    newSockets.push_back(clientSocket);
  }
}

void Server::SendMessages(){
  while (running){
    
    if (newSockets.size() == 0) continue;

    int clientSocket = newSockets.front();

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

    std::cout << "From socket " << clientSocket << ": " << response << std::endl;

    newSockets.pop_front();
    sockets.push_back(clientSocket);

    //  shut down:
    // status = shutdown(clientSocket, SD_BOTH);
    // if (status == -1){
    //   std::cout << "Shutdown failed" << std::endl;
    //   cp_close(clientSocket);
    //   return 1;
    // }

    // cp_close(clientSocket);
  }
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

  listenSocket = -1;
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

  return 0;
}