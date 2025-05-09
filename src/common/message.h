#ifndef MESSAGE_H
#define MESSAGE_H

#include <cstdint>
#include <string>
#include <vector>

#include "commands.h"

struct InternalMessage {
    uint8_t codeMessage;
    std::string line;
    std::vector<int> coordinate;
};

struct MessageFromServer {
    bool haveGame;
    std::string extraMessage;
    std::vector<std::string> listGames;
};

struct ServerResponseMessage {
    std::string serverResponse;
};

struct MessageFromClient {
    CommandType commandType;
    std::string gameName;
};

#endif
