// -r -- флаг регистрации
// -a -- флаг аунтификации

// -l -- флаг запроса списока пользователей
// -m -- флаг получения сообщения
// -c -- флаг запроса чата

// -s -- скип флаг

#pragma comment(lib, "ws2_32.lib")
#include <winsock2.h>
#include <iostream>

#include "serverService.h"
#include "databaseService.h"

#pragma warning(disable: 4996)

SOCKET connectionList[150];

void usrInterface(int id) {
	while (true) {
		char flagOfCommand[3] = "";
		recv(connectionList[id], flagOfCommand, sizeof(flagOfCommand), NULL);

		if (strcmp(flagOfCommand, "-a") == 0) {
					std::cout << "1\n";
					clientAuth(connectionList[id]);
		}
		
		else if (strcmp(flagOfCommand, "-r") == 0){
					std::cout << "2\n";

			regUser(connectionList[id]);}

		else if (strcmp(flagOfCommand, "-l") == 0){
					std::cout << "3\n";

			sendListOfUsers(connectionList[id]);}

		else if (strcmp(flagOfCommand, "-m") == 0){
					std::cout << "4\n";

			saveMsg(connectionList[id]);}

		else if (strcmp(flagOfCommand, "-c") == 0) {
					std::cout << "5\n";

			sendChatList(connectionList[id]);}

		else if (strcmp(flagOfCommand, "-s") == 0) {
					std::cout << "6\n";
		}
	}
}

int main() {
	WSAData wsaData;
	WORD DLLVersion = MAKEWORD(2, 1);
	if(WSAStartup(DLLVersion, &wsaData) != 0) {
		std::cout << "Error" << std::endl;
		exit(1);
	}

	SOCKADDR_IN addr;
	int sizeOfAddr = sizeof(addr);
	addr.sin_addr.s_addr = inet_addr("127.0.0.1");
	addr.sin_port = htons(1111);
	addr.sin_family = AF_INET;

	SOCKET sListen = socket(AF_INET, SOCK_STREAM, NULL);
	bind(sListen, (SOCKADDR*)&addr, sizeof(addr));
	listen(sListen, SOMAXCONN);

	SOCKET newConnection;
	for(int i = 0; i < 150; i++) {
		newConnection = accept(sListen, (SOCKADDR*)&addr, &sizeOfAddr);
		if(newConnection == 0) {
			std::cout << "Error #2\n";
		} else {
			connectionList[i] = newConnection;
			CreateThread(NULL, NULL, (LPTHREAD_START_ROUTINE)usrInterface, (LPVOID)(i), NULL, NULL);
		}
	}
	return 0;
}