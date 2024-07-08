#ifdef _WIN32

#include "win_server.hh"
using namespace WindowsSockets;

#else

#include "lin_server.hh"
using namespace LinuxSockets;

#endif

int main(int argc, char *argv[]){
  return server();
}