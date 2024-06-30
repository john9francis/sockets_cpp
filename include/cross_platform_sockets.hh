// differences:
//
// windows has WSAData for error handling
// (which may be unneccesary..?)
// 
// windows : freeaddrinfo()... may be the same
//

#ifndef CROSS_PLATFORM_SOCKETS_HH
#define CROSS_PLATFORM_SOCKETS_HH

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

#endif // ! CROSS_PLATFORM_SOCKETS_HH