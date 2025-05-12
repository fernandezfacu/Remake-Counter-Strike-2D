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

#define CODE_SUCCESS 0x01
#define CODE_FAIL 0x00

class ServerProtocol: public CommonProtocol {
private:
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
