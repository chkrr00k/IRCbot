#pragma once
extern "C" {
	#include <stdio.h>
	#include <stdlib.h>
	#include <sys/types.h>
	#include <WinSock2.h>
	#include "Socket.h"
	#pragma comment(lib, "ws2_32.lib")
}

/*	
*	char* ipaddress: the IP address to connect
*	int port: the port to connect
*	returns: the SOCKET connected, or INVALID_SOCKET if failed
*/
extern "C" SOCKET __cdecl tcpSocket(const char* ipaddress, int port);
/*
*	char* url: the hostname to connect
*	int port: the port to connect
*	returns: the SOCKET connected, or INVALID_SOCKET if failed
*/
extern "C" SOCKET __cdecl tcpSocketURL(char* url, int port);
/*	
*	SOCKET* sock: the socket used to send the message
*	char* message: the message to be sent
*	returns: 1 if succeed 0 if not;
*/
extern "C" int __cdecl writeSock(SOCKET* sock, const char* message);
/*
*	SOCKET* sock: the socket used to recive the message
*	int* recv_size: the size of the message recived (-1 if failed)
*	returns: the message recived
*/
std::string __cdecl readSock(SOCKET* sock, int* recv_size);

std::string __cdecl readLine(SOCKET* sock);
/*
*	char* hostName: the hostname to be resolved
*	char* ipresult[20]: the IP resolved passed by reference
*	returns: 1 if succeed, 0 if failed
*/
extern "C" int __cdecl resolveURL(const char* hostName, char** ipresult);

extern "C" int  __cdecl create(const char* url);