#include "client_protocol_parser.h"

ClientProtocolParser::ClientProtocolParser() {
    parsersMap[CommandType::CREATE_USERNAME] = [this](const MessageFromClient& request) {
        return this->parseFromCreateUsername(request);
    };
    parsersMap[CommandType::CREATE_GAME] = [this](const MessageFromClient& request) {
        return this->parseFromCreateGameRequest(request);
    };
    parsersMap[CommandType::JOIN_GAME] = [this](const MessageFromClient& request) {
        return this->parseFromJoinGameRequest(request);
    };
    parsersMap[CommandType::BUY_WEAPON] = [this](const MessageFromClient& request) {
        return this->parseFromBuyWeaponRequest(request);
    };
    parsersMap[CommandType::BUY_AMMO] = [this](const MessageFromClient& request) {
        return this->parseFromBuyWeaponAmmoRequest(request);
    };
}

InternalMessage ClientProtocolParser::ParseMessage(const MessageFromClient& message) {
    return this->parsersMap.find(message.commandType)->second(message);
}

InternalMessage ClientProtocolParser::parseFromCreateUsername(const MessageFromClient& request) {
    return InternalMessage{CODE_CREATE_USERNAME, request.s};
}

InternalMessage ClientProtocolParser::parseFromCreateGameRequest(const MessageFromClient& request) {
    return InternalMessage{CODE_CREATE_GAME};
}

InternalMessage ClientProtocolParser::parseFromJoinGameRequest(const MessageFromClient& request) {
    return InternalMessage{CODE_JOIN_GAME, request.s};
}

InternalMessage ClientProtocolParser::parseFromBuyWeaponRequest(const MessageFromClient& request) {
    InternalMessage msg = InternalMessage{CODE_BUY_WEAPON};
    msg.code_weapon = this->weaponParser.getWeaponToByte(request.weapon);
    return msg;
}

InternalMessage ClientProtocolParser::parseFromBuyWeaponAmmoRequest(const MessageFromClient& request) {
    InternalMessage msg = InternalMessage{CODE_BUY_BULLETS};
    msg.code_weapon_type = this->weaponParser.getWeaponTypeToByte(this->weaponParser.getWeaponType(request.weapon));
    msg.bullets = request.bullets;
    return msg;
}
