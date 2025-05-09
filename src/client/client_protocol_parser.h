#ifndef CLIENT_PROTOCOL_PARSER_H
#define CLIENT_PROTOCOL_PARSER_H

#include <functional>
#include <string>
#include <unordered_map>
#include <vector>

#include "../common/commands.h"
#include "../common/message.h"

#define CODE_CREATE_GAME 0x6E
#define CODE_JOIN_GAME 0x6A
#define CODE_LIST_GAMES 0x6C
#define CODE_MAKE_PLAYGAME 0x70

class ClientProtocolParser {
private:
    std::unordered_map<CommandType,
                       std::function<InternalMessage(const MessageFromClient& request)>>
            parsersMap;

    InternalMessage parseFromCreateGameRequest(const MessageFromClient& request);
    InternalMessage parseFromListGameRequest(const MessageFromClient& request);
    InternalMessage parseFromJoinGameRequest(const MessageFromClient& request);
    InternalMessage parseFromMakePlayGameRequest(const MessageFromClient& request);

public:
    ClientProtocolParser();
    InternalMessage ParseMessage(const MessageFromClient& message);
    uint8_t ParseCoordinatesForSend(const std::vector<int>& coordinates);
};

#endif
