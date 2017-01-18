#include <iostream>
#include <string>
#include <exception>
#include <string.h>
#include <regex>
#include "time.h"
#include "Irc.h"

#define PRIVMSG ":(.+)\\!.+ (PRIVMSG|privmsg) (\\#\\w+) \\:(.+)"

int main(void) {
	try {
		bool auth = false;
		int rows = 0;
		Irc irc = Irc("irc.server.org", 6667, "NameBot");
		irc.connect();
		std::string message;
		std::regex re(PRIVMSG);
		std::smatch match;
		while (true) {
			message = irc.read();
			if (strcmp(message.substr(0, 4).c_str(), "PING") == 0) {
				irc.pingHandler(message);
			}

			if (std::regex_search(message, match, re) && match.size() > 1) {
				std::cout << "MESSAGE: "<< match[1].str() << ": '" << match[3].str() << "' " << match[4].str() << std::endl;
			}

			if ((rows == 6) && !auth) {
				auth = true;
				irc.join("#channel");
				irc.sendMessage("#channel", "test");
			}
			std::cout << message << std::endl;
			rows++;
		}

	}
	catch (std::exception& e) {
		std::cout << "error " << e.what() << std::endl;
	}

	system("PAUSE");
	return 0;
}


