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

class ServerProtocol: public CommonProtocol, public CommonProtocolParser {
private:
    std::unordered_map<bool, uint8_t> codeSuccessResponse;
    std::unordered_map<CommandType, std::function<MessageFromClient(const CommandType& command)>> commandsManagers;
    ServerProtocolParser protocolParser;

    MessageFromClient receiveCreateUsernameRequest(const CommandType& command);
    MessageFromClient receiveCreateGameRequest(const CommandType& command);
    MessageFromClient receiveJoinGameRequest(const CommandType& command);
    MessageFromClient receiveSelectSkinsRequest(const CommandType& command);
    MessageFromClient receiveSelectMapRequest(const CommandType& command);
    MessageFromClient receiveBuyWeaponRequest(const CommandType& command);
    MessageFromClient receiveBuyWeaponAmmoRequest(const CommandType& command);
    MessageFromClient receiveAimRequest(const CommandType& command);
    MessageFromClient receiveMoveRequest(const CommandType& command);
    MessageFromClient receiveShootRequest(const CommandType& command);
    MessageFromClient receiveChangeWeaponRequest(const CommandType& command); 
    MessageFromClient receivePlantBombRequest(const CommandType& command);
    MessageFromClient receiveDefuseBombRequest(const CommandType& command);
public:
    explicit ServerProtocol(Socket&& socket);
    void SendLobbyMessage(const ServerResponseLobby& msg);    
    void SendMessage(const MessageFromServer& msg);
    MessageFromClient ReceiveCommand();
    void kill();
    ~ServerProtocol();
};

#endif
