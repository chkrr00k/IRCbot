#pragma once
#include <list>
#include "Message.h"
#include "List.h"

class Channel{
private:
	std::string name;
	List<Message> messages;
	List<std::string> people;
public:
	Channel(std::string name);
	List<Message> getAll();
	std::string getName();
	List<std::string> getPeople();
	void setPeople(List<std::string> people);
	void add(Message& message);
	~Channel();
};

