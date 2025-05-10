#ifndef SERVER_PROTOCOL_H
#define SERVER_PROTOCOL_H

#include <cstdint>
#include <functional>
#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>

#include "../common/common_protocol.h"
#include "../common/message.h"
#include "../common/socket.h"

#include "server_protocol_parser.h"

#define CODE_CREATE_USERNAME 0x01
#define CODE_CREATE_GAME 0x02
#define CODE_JOIN_GAME 0x03
#define CODE_MAKE_PLAY 0x04
#define CODE_SUCCESS 0x01
#define CODE_FAIL 0x00

class ServerProtocol: public CommonProtocol {
private:
    std::unordered_map<uint8_t, CommandType> codeToCommands;
    std::unordered_map<CommandType, uint8_t> commandsToCode;
    std::unordered_map<bool, uint8_t> codeSuccessResponse;
    std::unordered_map<CommandType, std::function<MessageFromClient()>> commandsManagers;
    ServerProtocolParser protocolParser;

    MessageFromClient receiveCreateUsernameRequest();
    MessageFromClient receiveCreateGameRequest();
    MessageFromClient receiveJoinGameRequest();
    void sendBoard(const MessageFromServer& msg);
    void sendListGames(const MessageFromServer& msg);

public:
    explicit ServerProtocol(Socket&& socket);
    void SendLobbyMessage(const ServerResponseLobby& msg);    
    void SendMessage(const MessageFromServer& msg);
    MessageFromClient ReceiveCommand();
    void kill();
    ~ServerProtocol();
};

#endif
