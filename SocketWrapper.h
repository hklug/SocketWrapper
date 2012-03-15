/* 
 * Copyright (c) 2012 Ma Xiaojun <damage3025 AT gmail DOT com>
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy of this software and
 * associated documentation files (the "Software"), to deal in the Software without restriction, including
 * without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to
 * the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all copies or substantial
 * portions of the Software
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS
 * FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR
 * COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER
 * IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
 * CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 */

/* Handle Header Files */
#if defined _WIN32
	#pragma comment(lib, "ws2_32.lib")
	#include <winsock2.h>
	#include <ws2tcpip.h>
#else
	#include <sys/types.h>
	#include <sys/socket.h>
	#include <netinet/in.h>
	#include <arpa/inet.h>
	#include <netdb.h>
	#include <unistd.h>
	#include <errno.h>
#endif
#include <stdio.h>
#include <stdlib.h>

/* Handle Minor Differences */
#if defined _WIN32
	#define SOCKERR() WSAGetLastError() 
#else 
	typedef int SOCKET; 
	#define INVALID_SOCKET -1 
	#define SOCKET_ERROR -1
	#define closesocket(s) close(s) 
	#define SOCKERR() errno 
#endif 

/* Define init_sockets() Macro */
#if defined _WIN32 
#define init_sockets()\
do {\
	printf("Initializing winsock environment...");\
	WSADATA wsaData;\
	if (WSAStartup(MAKEWORD(2,2), &wsaData) != NO_ERROR){\
		printf("Error at WSAStartup()\nRobot exit.");\
		exit(1);\
	}\
	printf("Done\n");\
} while(0)
#else
#define init_sockets() (void)0
#endif 

/* Define uninit_sockets() Macro */
#if defined _WIN32
#define uninit_sockets()\
do {\
	WSACleanup();\
} while(0)
#else
#define uninit_sockets() (void)0
#endif


/* Define SLEEP() Macro */
#if defined _WIN32
#define SLEEP(ms) Sleep(ms)
#else
#define SLEEP(ms)\
do {\
	unsigned n = (ms);\
	timeval timeout;\
	timeout.tv_sec = n / 1000;\
	timeout.tv_usec = (n % 1000) * 1000;\
	select(0 ,NULL, NULL, NULL, &timeout);\
} while(0)
#endif

