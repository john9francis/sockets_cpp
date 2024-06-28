#ifdef _WIN32
#include "win_server.hh"
#else
#include "lin_server.hh"
#endif

int main(){
  #ifdef _WIN32
  WindowsSockets::server();
  #else
  return LinuxSockets::server();
  #endif
}