#include <iostream>

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
  #endif


}