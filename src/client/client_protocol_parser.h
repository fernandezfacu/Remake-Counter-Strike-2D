#ifndef CLIENT_PROTOCOL_PARSER_H
#define CLIENT_PROTOCOL_PARSER_H

#include <functional>
#include <string>
#include <unordered_map>
#include <vector>

#include "../common/commands.h"
#include "../common/message.h"
#include "../common/weaponParser.h"

#define CODE_CREATE_USERNAME 0x01
#define CODE_CREATE_GAME 0x02
#define CODE_JOIN_GAME 0x03
#define CODE_BUY_WEAPON 0x04
#define CODE_BUY_BULLETS 0x05

class ClientProtocolParser {
private:
    WeaponParser weaponParser;
    std::unordered_map<CommandType,
                       std::function<InternalMessage(const MessageFromClient& request)>>
            parsersMap;

    InternalMessage parseFromCreateUsername(const MessageFromClient& request);
    InternalMessage parseFromCreateGameRequest(const MessageFromClient& request);
    InternalMessage parseFromJoinGameRequest(const MessageFromClient& request);
    InternalMessage parseFromBuyWeaponRequest(const MessageFromClient& request);
    InternalMessage parseFromBuyWeaponAmmoRequest(const MessageFromClient& request);

public:
    ClientProtocolParser();
    InternalMessage ParseMessage(const MessageFromClient& message);
    uint8_t ParseCoordinatesForSend(const std::vector<int>& coordinates);
};

#endif
