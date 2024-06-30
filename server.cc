#include "cp_server.hh"

int main(int argc, char* argv[]){
  if (argc == 1){
    std::cout << "Running on default port 8080" << std::endl;
  } else {
  std::cout << "Starting on port: " << argv[1] << std::endl;
  }
  return server();
}