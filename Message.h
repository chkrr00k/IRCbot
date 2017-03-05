#pragma once
#include <string>
#include <ostream>

class Message{
private:
	std::string channel;
	std::string person;
	std::string message;
	std::string sendtime;

	std::string getCurrentTime();
public:
	Message(std::string person, std::string message, std::string channel);
	std::string getChannel();
	std::string getPerson();
	std::string getMessage();
	std::string getTime();
	std::string toString();
	~Message();
};
std::ostream& operator<<(std::ostream& os, Message& m);

