#include "Channel.h"



Channel::Channel(std::string name): messages(), name(name), people(){
}

List<Message> Channel::getAll() {
	return List<Message>(this->messages);
}

std::string Channel::getName() {
	return this->name;
}

List<std::string> Channel::getPeople() {
	return this->people;
}

void Channel::setPeople(List<std::string> people) {
	 this->people = people;
}

void Channel::add(Message& message) {
	this->messages.push(message);
}


Channel::~Channel() {
}
