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
    sendersMap[CommandType::SELECT_SKINS] = [this](const InternalMessage& request) {
        return this->sendSelectSkinsRequest(request);
    };
    sendersMap[CommandType::SELECT_MAP] = [this](const InternalMessage& request) {
        return this->sendSelectMapRequest(request);
    };
    sendersMap[CommandType::BUY_WEAPON] = [this](const InternalMessage& request) {
        return this->sendBuyWeaponRequest(request);
    };
    sendersMap[CommandType::BUY_AMMO] = [this](const InternalMessage& request) {
        return this->sendBuyWeaponAmmoRequest(request);
    };
    sendersMap[CommandType::AIM] = [this](const InternalMessage& request) {
        return this->sendAimRequest(request);
    };
    sendersMap[CommandType::MOVE] = [this](const InternalMessage& request) {
        return this->sendMoveRequest(request);
    };
    sendersMap[CommandType::SHOOT] = [this](const InternalMessage& request) {
        return this->sendShootRequest(request);
    };
    sendersMap[CommandType::CHANGE_WEAPON] = [this](const InternalMessage& request) {
        return this->sendChangeWeaponRequest(request); 
    };
    sendersMap[CommandType::PLANT_BOMB] = [this](const InternalMessage& request) {
        return this->sendPlantBombRequest(request);
    };
    sendersMap[CommandType::DEFUSE_BOMB] = [this](const InternalMessage& request) {
        return this->sendDefuseBombRequest(request);
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
    this->SendByte(msg.code_message);
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

void ClientProtocol::sendSelectSkinsRequest(const InternalMessage& request) {
    this->SendByte(request.skin_id_tt);
    this->SendByte(request.skin_id_ct);
}


void ClientProtocol::sendSelectMapRequest(const InternalMessage& request) {
    this->SendByte(request.map_id);
}

void ClientProtocol::sendBuyWeaponRequest(const InternalMessage& request) {
    this->SendByte(request.code_weapon);
}

void ClientProtocol::sendBuyWeaponAmmoRequest(const InternalMessage& request) {
    this->SendByte(request.code_weapon_type);
    this->SendBigEndianNumber(request.bullets);
}

void ClientProtocol::sendAimRequest(const InternalMessage& request) {
    this->SendByte(request.pos_x);
    this->SendByte(request.pos_y);
}

void ClientProtocol::sendMoveRequest(const InternalMessage& request) {
    this->SendByte(request.direction);
}

void ClientProtocol::sendShootRequest(const InternalMessage& request) {
    
}

void ClientProtocol::sendChangeWeaponRequest(const InternalMessage& request) {
    this->SendByte(request.code_weapon_type);
}

void ClientProtocol::sendPlantBombRequest(const InternalMessage& request) {
    
}

void ClientProtocol::sendDefuseBombRequest(const InternalMessage& request) {

}

void ClientProtocol::Close() {
    this->socket.shutdown(SHUT_RDWR);
    this->socket.close();
}

ClientProtocol::~ClientProtocol() {}
