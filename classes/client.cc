#include "cp_client.hh"

int main(int argc, char *argv[]){
  if (argc < 3){
    std::cout 
    << "Please specify the host and port as arguments: "
    << std::endl
    << "For example: localhost 8080"
    << std::endl;
    return 1;
  }
  Client(argv[1], argv[2]);
}