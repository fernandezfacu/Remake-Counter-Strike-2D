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
    sendersMap[CommandType::CREATE_USERNAME] = [this](const InternalMessage& request) {
        this->sendCreateUsernameRequest(request);
    };
    sendersMap[CommandType::CREATE_GAME] = [this](const InternalMessage& request) {
        return this->sendCreateGameRequest(request);
    };
    sendersMap[CommandType::JOIN_GAME] = [this](const InternalMessage& request) {
        return this->sendJoinGameRequest(request);
    };
    sendersMap[CommandType::BUY_WEAPON] = [this](const InternalMessage& request) {
        return this->sendBuyWeaponRequest(request);
    };
    sendersMap[CommandType::BUY_AMMO] = [this](const InternalMessage& request) {
        return this->sendBuyWeaponAmmoRequest(request);
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

void ClientProtocol::sendCreateUsernameRequest(const InternalMessage& request) {
    this->SendString(request.s);
}

void ClientProtocol::sendCreateGameRequest(const InternalMessage& request) {
    
}

void ClientProtocol::sendJoinGameRequest(const InternalMessage& request) {
    this->SendString(request.s);
}

void ClientProtocol::sendBuyWeaponRequest(const InternalMessage& request) {
    this->SendByte(request.codeWeapon);
}

void ClientProtocol::sendBuyWeaponAmmoRequest(const InternalMessage& request) {
    this->SendByte(request.codeWeaponType);
    this->SendBigEndianNumber(request.bullets);
}

void ClientProtocol::Close() {
    this->socket.shutdown(SHUT_RDWR);
    this->socket.close();
}

ClientProtocol::~ClientProtocol() {}
