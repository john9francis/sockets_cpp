#ifdef _WIN32

#include "win_client.hh"
using namespace WindowsSockets;

#else

#include "lin_client.hh"
using namespace LinuxSockets;

#endif

int main(int argc, char *argv[]){
  return client();
}