#ifndef MESSAGE_H
#define MESSAGE_H

#include <cstdint>
#include <string>
#include <vector>

#include "weapon.h"
#include "commands.h"

struct InternalMessage {
    uint8_t code_message;
    std::string s;
    int pos_x;
    int pos_y;
    uint8_t direction;
    uint8_t code_weapon_type;
    uint8_t code_weapon;
    uint8_t size_players;
    uint8_t skin_id_tt;
    uint8_t skin_id_ct;
    uint8_t map_id;
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
