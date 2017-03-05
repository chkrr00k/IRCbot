#include "Message.h"
#include <regex>



std::string Message::getCurrentTime() {
	time_t current = time(0);
	struct tm tstruct;
	char result[20];
	tstruct = *localtime(&current);
	strftime(result, sizeof(result), "%X", &tstruct);
	return result;
}

Message::Message(std::string person, std::string message, std::string channel)
	:person(person), message(message), channel(channel), sendtime(getCurrentTime()) {
}

std::string Message::getChannel() {
	return this->channel;
}

std::string Message::getPerson() {
	return this->person;
}

std::string Message::getMessage() {
	return this->message;
}

std::string Message::getTime() {
	return this->sendtime;
}

std::string Message::toString() {
	return "<" + this->getTime() + "> " + this->getPerson() + " " + this->getMessage();
}

std::ostream& operator<<(std::ostream& os, Message & m){
	return os << m.getTime() << " " << m.getChannel() << " " << m.getPerson() << " " << m.getMessage();
}

Message::~Message(){
}
