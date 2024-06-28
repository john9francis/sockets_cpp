#ifdef _WIN32
#include "win_client.hh"
#else
#include "lin_client.hh"
#endif

int main(){
  #ifdef _WIN32
  WindowsSockets::client();
  #else
  LinuxSockets::client();
  #endif
}