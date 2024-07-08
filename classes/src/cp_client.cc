#include "cp_client.hh"

Client::Client(char* host, char* port){
  std::cout 
  << "Hello Client on host: " 
  << host 
  << " and port: " 
  << port 
  << std::endl;
}