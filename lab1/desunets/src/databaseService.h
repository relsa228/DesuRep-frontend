#include <vector>
#include <string>
#include <stdlib.h>

#include "sqlite3.h"

bool auth(std::string username, std::string password);

std::vector<std::string> getListOfUsers();
std::vector<std::string> getChat(int getterId, int senderId);

void saveMsg(int getterId, int senderId, std::string msg);
bool saveUsr(std::string username, std::string password);

