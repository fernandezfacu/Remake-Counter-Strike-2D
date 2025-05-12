#ifndef CLIENT_PROTOCOL_H
#define CLIENT_PROTOCOL_H

#include <cstdint>
#include <functional>
#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>

#include "../common/commands.h"
#include "../common/common_protocol.h"
#include "../common/message.h"
#include "../common/socket.h"
#include "../common/codes_parser.h"

#include "client_protocol_parser.h"

class ClientProtocol: public CommonProtocol, public CodesParser {
private:
    ClientProtocolParser parser;
    bool isAlive;
    std::unordered_map<CommandType, std::function<void(const InternalMessage& request)>> sendersMap;

    void sendCreateUsernameRequest(const InternalMessage& request);
    void sendCreateGameRequest(const InternalMessage& request);
    void sendJoinGameRequest(const InternalMessage& request);
    void sendSelectSkinsRequest(const InternalMessage& request);
    void sendSelectMapRequest(const InternalMessage& request);
    void sendBuyWeaponRequest(const InternalMessage& request);
    void sendBuyWeaponAmmoRequest(const InternalMessage& request);
    void sendAimRequest(const InternalMessage& request);
    void sendMoveRequest(const InternalMessage& request);
    void sendShootRequest(const InternalMessage& request);
    void sendChangeWeaponRequest(const InternalMessage& request); 
    void sendPlantBombRequest(const InternalMessage& request);
    void sendDefuseBombRequest(const InternalMessage& request);

public:
    ClientProtocol(const std::string& hostname, const std::string& port);
    void SendCommand(const MessageFromClient& request);
    ServerResponseLobby ReceiveCommand();
    void Close();
    ~ClientProtocol();
};

#endif
