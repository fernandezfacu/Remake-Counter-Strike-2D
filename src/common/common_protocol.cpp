#include "common_protocol.h"

#include <utility>

#include <string.h>

#include "communication_ended.h"

CommonProtocol::CommonProtocol(const std::string& hostname, const std::string& port):
        socket(hostname.c_str(), port.c_str()),
        codeToCommands({{CODE_CREATE_USERNAME, CommandType::CREATE_USERNAME},
            {CODE_CREATE_GAME, CommandType::CREATE_GAME},
            {CODE_JOIN_GAME, CommandType::JOIN_GAME},
            {CODE_SELECT_SKINS, CommandType::SELECT_SKINS},
            {CODE_SELECT_MAP, CommandType::SELECT_MAP},
            {CODE_BUY_WEAPON, CommandType::BUY_WEAPON},
            {CODE_BUY_BULLETS, CommandType::BUY_AMMO},
            {CODE_AIM, CommandType::AIM},
            {CODE_MOVE, CommandType::MOVE},
            {CODE_SHOOT, CommandType::SHOOT},
            {CODE_CHANGE_WEAPON, CommandType::CHANGE_WEAPON},
            {CODE_PLANT_BOMB, CommandType::PLANT_BOMB},
            {CODE_DEFUSE_BOMB, CommandType::DEFUSE_BOMB}}),
        commandsToCode({{CommandType::CREATE_USERNAME, CODE_CREATE_USERNAME},
            {CommandType::CREATE_GAME, CODE_CREATE_GAME},
            {CommandType::JOIN_GAME, CODE_JOIN_GAME},
            {CommandType::SELECT_SKINS, CODE_SELECT_SKINS},
            {CommandType::SELECT_MAP, CODE_SELECT_MAP},
            {CommandType::BUY_WEAPON, CODE_BUY_WEAPON},
            {CommandType::BUY_AMMO, CODE_BUY_BULLETS},
            {CommandType::AIM, CODE_AIM},
            {CommandType::MOVE, CODE_MOVE},
            {CommandType::SHOOT, CODE_SHOOT},
            {CommandType::CHANGE_WEAPON, CODE_CHANGE_WEAPON},
            {CommandType::PLANT_BOMB, CODE_PLANT_BOMB},
            {CommandType::DEFUSE_BOMB, CODE_DEFUSE_BOMB}}) {}

CommonProtocol::CommonProtocol(Socket&& socket): socket(std::move(socket)) {}

uint8_t CommonProtocol::receiveByte() {
    uint8_t number;

    size_t received = this->socket.recvall(&number, sizeof(number));
    if (received != sizeof(number)) {
        throw CommunicationEnded();
    }

    return number;
}

uint16_t CommonProtocol::receiveBigEndianNumber() {
    uint16_t number;

    size_t received = this->socket.recvall(&number, sizeof(number));
    if (received != sizeof(number)) {
        throw CommunicationEnded();
    }

    return ntohs(number);
}

void CommonProtocol::SendByte(const uint8_t& number) {
    size_t sended = this->socket.sendall(&number, sizeof(number));
    if (sended != sizeof(number)) {
        throw CommunicationEnded();
    }
}

void CommonProtocol::SendBigEndianNumber(const uint16_t& number) {
    uint16_t parsed = htons(number);

    size_t sended = this->socket.sendall(&parsed, sizeof(parsed));
    if (sended != sizeof(parsed)) {
        throw CommunicationEnded();
    }
}

void CommonProtocol::SendString(const std::string& s) {
    this->SendBigEndianNumber(s.size());
    size_t sended = this->socket.sendall(s.c_str(), s.size());
    if (sended != s.size()) {
        throw CommunicationEnded();
    }
}


std::string CommonProtocol::ReceiveString() {
    size_t lengthString = this->receiveBigEndianNumber();
    std::vector<uint8_t> vectorBytes(lengthString);
    size_t received = this->socket.recvall(vectorBytes.data(), vectorBytes.size());
    if (received != lengthString) {
        throw CommunicationEnded();
    }
    std::string s(vectorBytes.begin(), vectorBytes.end());
    return s;
}
