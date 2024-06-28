#ifdef _WIN32
// put windows header here
#else
#include "lin_server.hh"
#endif

int main(){
  #ifdef _WIN32
  // windows function
  #else
  return LinuxSockets::server();
  #endif
}