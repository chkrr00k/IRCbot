#pragma once
#include "Socket.h"
#include <iostream>
#include <string>

class Server
{
private:
	std::string name;
	SOCKET sock = NULL;
	std::string ip;
	bool isConnect = false;
	int port;

public:
	Server(std::string name, int port);
	std::string getName();
	int getPort();
	std::string getIp();
	void connect();
	void disconnect();
	bool isConnected();
	bool write(std::string message);
	std::string read();
	~Server();
};

