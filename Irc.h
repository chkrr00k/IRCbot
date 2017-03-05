#pragma once
#include <string>
#include "Server.h"
#include "Channel.h"
#include "Map.h"
#include <stdlib.h>

class Irc{
private:
	Server server;
	std::string nick;
	Map<std::string, Channel> chans;
public:
	Irc(std::string server, int port, std::string nick);
	void connect();
	void disconnect();
	// active;
	void join(std::string channel);
	void part(std::string channel);
	void sendMessage(std::string channel, std::string message);
	void sendNotice(std::string channel, std::string message);
	// passive;
	/*
	void messageHandler(std::string line);
	void modeHandler(std::string line);
	void noticeHandler(std::string line);
	void quitHandler(std::string line);
	void partHandler(std::string line);
	void inviteHandler(std::string line);
	void kickHandler(std::string line);
	void banHandler(std::string line);*/
	void pingHandler(std::string line);
	std::string read();
	~Irc();
};

