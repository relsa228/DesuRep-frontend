#include "serverService.h"

void clientAuth(SOCKET newConnection) {
	int credsSize;

	recv(newConnection, (char*)&credsSize, sizeof(int), NULL);
	char* creds = new char[credsSize + 1];
	creds[credsSize] = '\0';
	recv(newConnection, creds, credsSize, NULL);

	std::string username = "";
	std::string password = "";
	bool passFlag = false;

	std::string credsStr = creds;
	for(auto ch : credsStr) {
		if (ch == '\n') {
			passFlag = true;
			continue;
		}
		
		if (passFlag)
			password += ch;
		else
			username += ch;
	}

	if (auth(username, password)) {
		char authResultFlag[3] = "-0";
		send(newConnection, authResultFlag, sizeof(authResultFlag), NULL);
	}
	else {
		char authResultFlag[3] = "-1";
		send(newConnection, authResultFlag, sizeof(authResultFlag), NULL);
	}
}

void sendListOfUsers(SOCKET newConnection) {
	std::vector<std::string> listOfUsers = {"Debug", "ttt", "Buerak", "little_kitten"};

	std::string stringOfUsers = "-l\n";
	for(auto uname : listOfUsers) {
		stringOfUsers += uname;
		stringOfUsers += "\n";
	}

	int sizeOfList = stringOfUsers.size();

	send(newConnection, (char*) &sizeOfList, sizeof(int), NULL);
	send(newConnection, stringOfUsers.c_str(), sizeOfList, NULL);
}

void sendChatList(SOCKET newConnection) {
	std::vector<std::string> vectOfMsgs = {"Debug: hi", "relsa: hello", "relsa: yo mama is fat", "debug: wtf?"};

	std::string stringOfMsgs = "-c\n";
	for(auto msg : vectOfMsgs) {
		stringOfMsgs += msg;
		stringOfMsgs += "\n";
	}

	int sizeOfMsgs = stringOfMsgs.size();

	send(newConnection, (char*) &sizeOfMsgs, sizeof(int), NULL);
	send(newConnection, stringOfMsgs.c_str(), sizeOfMsgs, NULL);
}

void saveMsg(SOCKET newConnection) {}
void regUser(SOCKET newConnection) {}