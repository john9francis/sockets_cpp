#ifdef _WIN32
// put windows header here
#else
#include "lin_client.hh"
#endif

int main(){
  #ifdef _WIN32
  // windows function
  #else
  LinuxSockets::client();
  #endif
}