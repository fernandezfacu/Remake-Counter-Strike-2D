#include "client_protocol.h"

#include <cstdint>
#include <cstring>
#include <string>

#include <arpa/inet.h>
#include <sys/socket.h>

#include "../common/commands.h"
#include "../common/communication_ended.h"
#include "../common/message.h"

ClientProtocol::ClientProtocol(const std::string& hostname, const std::string& port):
        CommonProtocol(hostname, port), parser(), isAlive(true) {
    sendersMap[CommandType::CREATE_GAME] = [this](const InternalMessage& request) {
        return this->sendCreateGameRequest(request);
    };
    sendersMap[CommandType::JOIN_GAME] = [this](const InternalMessage& request) {
        return this->sendJoinGameRequest(request);
    };
}

ServerResponseMessage ClientProtocol::ReceiveCommand() {
    std::string received = this->ReceiveString();
    return ServerResponseMessage{
            received,
    };
}

void ClientProtocol::SendCommand(const MessageFromClient& request) {
    InternalMessage msg = this->parser.ParseMessage(request);
    this->SendByte(msg.codeMessage);
    this->sendersMap.find(request.commandType)->second(msg);
}

void ClientProtocol::sendCreateGameRequest(const InternalMessage& request) {
    this->SendString(request.line);
}

void ClientProtocol::sendJoinGameRequest(const InternalMessage& request) {
    this->SendString(request.line);
}

void ClientProtocol::Close() {
    this->socket.shutdown(SHUT_RDWR);
    this->socket.close();
}

ClientProtocol::~ClientProtocol() {}
