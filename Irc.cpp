#include "Irc.h"
#include <stdlib.h>

const std::string IDENT = "IDENT";
const std::string HOST = "HOST";
const std::string REALNAME = "REALNAME";
const std::string QUIT = "making an IRC client etc. etc.";


Irc::Irc(std::string server, int port, std::string nick) 
	:server{ Server(server, port) }, nick(nick) {
}

void Irc::connect() {
	this->server.connect();
	this->server.write("NICK " + this->nick + "\r\n");
	this->server.write("USER " + IDENT + " " + HOST + " ayy :" + REALNAME + "\r\n");
}

void Irc::disconnect() {
	this->server.write("QUIT :" + QUIT + "\r\n");
	this->server.disconnect();
}

void Irc::join(std::string channel){
	this->server.write("JOIN " + channel + "\r\n");
}

void Irc::part(std::string channel){
	this->server.write("PART " + channel + "\r\n");
}

void Irc::sendMessage(std::string channel, std::string message) {
	Sleep(20);
	this->server.write("PRIVMSG " + channel + " :" + message + "\r\n");
}

void Irc::sendNotice(std::string channel, std::string message) {
	this->server.write("NOTICE " + channel + " :" + message + "\r\n");
}

void Irc::pingHandler(std::string line) {
	this->server.write("PONG " + line.substr(6) + "\r\n");
}

std::string Irc::read() {
	return this->server.read();
}

Irc::~Irc() {
}
