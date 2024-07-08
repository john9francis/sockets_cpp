#include "cp_server.hh"

int main(){
  Server server;
  for (int i=0; i<15; i++){
    std::cout << "Doing other stuff" << std::endl;
    std::this_thread::sleep_for(std::chrono::milliseconds(500));
  }
}