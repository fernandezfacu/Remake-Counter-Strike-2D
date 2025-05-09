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

#include "client_protocol_parser.h"

class ClientProtocol: public CommonProtocol {
private:
    ClientProtocolParser parser;
    bool isAlive;
    std::unordered_map<CommandType, std::function<void(const InternalMessage& request)>> sendersMap;

    void sendCreateGameRequest(const InternalMessage& request);
    void sendJoinGameRequest(const InternalMessage& request);
    void sendMakePlayGameRequest(const InternalMessage& request);

public:
    ClientProtocol(const std::string& hostname, const std::string& port);
    void SendCommand(const MessageFromClient& request);
    ServerResponseMessage ReceiveCommand();
    void Close();
    ~ClientProtocol();
};

#endif
