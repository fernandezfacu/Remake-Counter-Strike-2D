#ifndef MESSAGE_H
#define MESSAGE_H

#include <cstdint>
#include <string>
#include <vector>

#include "weapon.h"
#include "commands.h"

struct InternalMessage {
    uint8_t codeMessage;
    std::string s;
    int pos_x;
    int pos_y;
    int dir_x;
    int dir_y;
    uint8_t codeWeaponType;
    uint8_t codeWeapon;
    uint16_t bullets;
};

struct MessageFromServer {
    bool haveGame;
    std::string extraMessage;
    std::vector<std::string> listGames;
};

struct ServerResponseMessage {
    std::string serverResponse;
};

struct ServerResponseLobby {
    CommandType commandType;
    bool success;
};

struct MessageFromClient {
    CommandType commandType;
    std::string s;
    Weapon weapon;
    WeaponType weaponType;
    int bullets;
    bool isOff;
};

#endif
