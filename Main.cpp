#include <iostream>
#include <string>
#include <exception>
#include <string.h>
#include <regex>
#include <list>
#include "time.h"
#include "Irc.h"
#include "Message.h"

#define PRIVMSG ":(.+)\\!.+ (PRIVMSG|privmsg) (\\#\\w+) \\:(.+)"

int main(void) {
	try {
		
		bool auth = false;
		int rows = 0;
		Irc irc = Irc("irc.example.org", 6667, "nameBot");
		irc.connect();
		std::string message;
		std::regex re(PRIVMSG);
		std::smatch match;
		while (true) {
			message = irc.read();
			if (strcmp(message.substr(0, 4).c_str(), "PING") == 0) {
				irc.pingHandler(message);
			}
			Message* tmp = nullptr;
			if (std::regex_search(message, match, re) && match.size() > 1) {
				tmp = new Message(match[1].str(), match[4].str(), match[3].str());
				std::cout << *tmp << std::endl;
				delete tmp;
			}

			if ((rows == 6) && !auth) {
				auth = true;
				irc.join("#channel");
				irc.sendMessage("#channel", "test");
			}
			//std::cout << message << std::endl;
			rows++;
		}

	}
	catch (std::exception& e) {
		std::cout << "error " << e.what() << std::endl;
	}

	system("PAUSE");
	return 0;
}


