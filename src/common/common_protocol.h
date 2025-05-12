#include <cstdint>
#include <string>
#include <vector>

#include <arpa/inet.h>

#include "error_codes.h"
#include "socket.h"
#include <unordered_map>
#include "commands.h"

#define CODE_CREATE_USERNAME 0x01
#define CODE_CREATE_GAME 0x02
#define CODE_JOIN_GAME 0x03
#define CODE_SELECT_SKINS 0x04
#define CODE_SELECT_MAP 0x05
#define CODE_BUY_WEAPON 0x06
#define CODE_BUY_BULLETS 0x07
#define CODE_AIM 0x08
#define CODE_MOVE 0x09
#define CODE_SHOOT 0x10
#define CODE_CHANGE_WEAPON 0x11
#define CODE_PLANT_BOMB 0x12
#define CODE_DEFUSE_BOMB 0x13

class CommonProtocol {
protected:
    Socket socket;
    std::unordered_map<uint8_t, CommandType> codeToCommands;
    std::unordered_map<CommandType, uint8_t> commandsToCode;

public:
    CommonProtocol(const std::string& hostname, const std::string& port);
    explicit CommonProtocol(Socket&& socket);

    uint8_t receiveByte();
    uint16_t receiveBigEndianNumber();
    void SendByte(const uint8_t& number);
    void SendBigEndianNumber(const uint16_t& number);
    void SendString(const std::string& s);
    std::string ReceiveString();
};
