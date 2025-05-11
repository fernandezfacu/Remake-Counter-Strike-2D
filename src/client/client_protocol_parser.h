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

class ClientProtocolParser {
private:
    WeaponParser weaponParser;
    std::unordered_map<CommandType,
                       std::function<InternalMessage(const MessageFromClient& request)>>
            parsersMap;

    InternalMessage parseFromCreateUsernameRequest(const MessageFromClient& request);
    InternalMessage parseFromCreateGameRequest(const MessageFromClient& request);
    InternalMessage parseFromSelectSkinsRequest(const MessageFromClient& request);
    InternalMessage parseFromSelectMapRequest(const MessageFromClient& request);
    InternalMessage parseFromJoinGameRequest(const MessageFromClient& request);
    InternalMessage parseFromBuyWeaponRequest(const MessageFromClient& request);
    InternalMessage parseFromBuyWeaponAmmoRequest(const MessageFromClient& request);
    InternalMessage parseFromAimRequest(const MessageFromClient& request);
    InternalMessage parseFromMoveRequest(const MessageFromClient& request);
    InternalMessage parseFromShootRequest(const MessageFromClient& request);
    InternalMessage parseFromChangeWeaponRequest(const MessageFromClient& request);
    InternalMessage parseFromPlantBombRequest(const MessageFromClient& request);
    InternalMessage parseFromDefuseBombRequest(const MessageFromClient& request);

public:
    ClientProtocolParser();
    InternalMessage ParseMessage(const MessageFromClient& message);
    uint8_t ParseCoordinatesForSend(const std::vector<int>& coordinates);
};

#endif
