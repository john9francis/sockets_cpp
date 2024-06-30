// differences:
//
// windows has WSAStartup to link to the .lib
// 
// windows uses UINT_PTR instead of int for sockets,
// however, using an int seems to work.

#ifndef CROSS_PLATFORM_SOCKETS_HH
#define CROSS_PLATFORM_SOCKETS_HH

namespace cp_sockets{

// include header files
#ifdef _WIN32

#include <WinSock2.h>
#include <WS2tcpip.h>

#else

#include <cstring>
#include <sys/types.h>
#include <string>
#include <sys/socket.h>
#include <netdb.h>

#endif

int init(){

  #ifdef _WIN32
  WSADATA wsaData;

  int iResult = WSAStartup(MAKEWORD(2,2), &wsaData);
  if (iResult != 0){
    return 1;
  }
  #endif

  return 0;
}

// #include <stdarg.h>

// void cleanup(struct addrinfo *res=NULL, int socket, ...){

// }

} // ! namespace cp_sockets

#endif // ! CROSS_PLATFORM_SOCKETS_HH