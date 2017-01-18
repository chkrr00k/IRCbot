#include <iostream>
#include <string>
#include <regex>
#include "Server.h"
#include "Socket.h"

#define HTTP_WWW "(http|https)://([\\w_-]+(?:(?:\.[\\w_-]+)+))([\\w.,@?^=%&:/~+#-]*[\\w@?^=%&/~+#-])?"
#define WWW "([\\w_-]+(?:(?:\.[\\w_-]+)+))([\\w.,@?^=%&:/~+#-]*[\\w@?^=%&/~+#-])?"
#define IP "(\\d{1,3}\\.\\d{1,3}\\.\\d{1,3}\\.\\d{1,3})"



Server::Server(std::string name, int port): port(port) {
	std::regex reIp(IP);
	std::regex reWww(WWW);
	std::smatch match;
	if (std::regex_search(name, match, reIp) && match.size() > 1) {
		this->ip = name;
		this->name = "Unknown";
	}
	else if (std::regex_search(name, match, reWww) && match.size() > 1) {
		this->name = name;
		char* output = NULL;
		int result = resolveURL((this->name).c_str(), &output);
		if (result) {
			this->ip = output;
		}
		else {
			throw std::exception("Error in resolving URL");
		}
		free(output);
	}
	else {
		throw std::invalid_argument("");
	}
}

std::string Server::getIp() {
	return this->ip;
}

std::string Server::getName() {
	return this->name;
}

int Server::getPort() {
	return this->port;
}

void Server::connect(){
	SOCKET tmp = tcpSocket((this->ip).c_str(), this->port);
	if (tmp == INVALID_SOCKET) {
		throw std::exception("Error in connecting");
	}
	this->sock = tmp;
	this->isConnect = true;
}

void Server::disconnect() {
	closesocket(this->sock);
	WSACleanup();
}

bool Server::write(std::string message) {
	if (this->isConnect) {
		return writeSock(&(this->sock), message.c_str());
	}
	else {
		throw std::exception("Socket not connected");
	}
}

std::string Server::read() {
	if (this->isConnect) {
		return std::string(readLine(&(this->sock)));
	}
	else {
		throw std::exception("Socket not connected");
	}
}

bool Server::isConnected() {
	return this->isConnect;
}

Server::~Server(){
	closesocket(this->sock);
	WSACleanup();
}
