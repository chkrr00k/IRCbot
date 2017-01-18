#include <string>
#include "Socket.h"

SOCKET __cdecl tcpSocketURL(const char* url, int port) {
	char* ip;
	if (resolveURL(url, &ip) == -1) {
		return INVALID_SOCKET;
	}
	return tcpSocket(ip, port);
}

SOCKET __cdecl tcpSocket(const char* ipaddress, int port) {
	WSADATA wsa;
	SOCKET sock;
	struct sockaddr_in server;

	if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0) {
		return INVALID_SOCKET;
	}
	if ((sock = socket(AF_INET, SOCK_STREAM, 0)) == INVALID_SOCKET) {
		return INVALID_SOCKET;
	}
	server.sin_addr.s_addr = inet_addr(ipaddress);
	server.sin_family = AF_INET;
	server.sin_port = htons(port);
	if (connect(sock, (struct sockaddr *)&server, sizeof(server)) < 0) {
		return INVALID_SOCKET;
	}
	return sock;
}

int __cdecl resolveURL(const char* hostName, char** ipresult) {
	WSADATA wsa;
	char ip[50];
	struct hostent *he;
	struct in_addr **addr_list;
	int i;

	if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0) {
		return 0;
	}
	if ((he = gethostbyname(hostName)) == NULL) {
		return 0;
	}
	addr_list = (struct in_addr **) he->h_addr_list;
	for (i = 0; addr_list[i] != NULL; i++) {
		strcpy(ip, inet_ntoa(*addr_list[i]));
	}
	//TODO fix this
	*ipresult = (char*)malloc(sizeof(char*)*strlen(ip));
	strcpy(*ipresult, ip);

	return 1;
}

int __cdecl writeSock(SOCKET* sock, const char* message) {
	if (send(*sock, message, strlen(message), 0) < 0) {
		return 0;
	}
	else {
		return 1;
	}
}

std::string __cdecl readSock(SOCKET* sock, int* recv_size) {
	char server_reply[2000];
	int i = 0;
	if ((*recv_size = recv(*sock, server_reply, 2000, 0)) == SOCKET_ERROR) {
		return "";
	}
	server_reply[*recv_size] = '\0';
	return std::string(server_reply);
}

std::string __cdecl readLine(SOCKET* sock) {
	int recv_size;
	char server_reply = '\0';
	std::string tmp = "";
	int i = 0;
	while (tmp.size() < 1) {
		while (server_reply != '\n' && server_reply != '\r') {
			if ((recv_size = recv(*sock, &server_reply, sizeof(char), 0)) == SOCKET_ERROR) {
				throw std::exception("Error in reading message");
			}
			tmp += server_reply;
		}
		tmp.pop_back();
		server_reply = '\0';
	}
	return tmp;
}

int __cdecl create(const char* url) {
	char* output = NULL;
	int test = resolveURL(url, &output);
	SOCKET sock = tcpSocket(output, 80);
	free(output);
	return sock;
}