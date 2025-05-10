#ifndef COMMANDS_H
#define COMMANDS_H

#include <string>

enum CommandType {
    CREATE_USERNAME = 0,
    CREATE_GAME = 1,
    JOIN_GAME = 2,
    BUY_WEAPON = 3,
    BUY_AMMO = 4,
    SHOOT = 5,
    DROP_WEAPON = 6, 
    ROTATE = 7,
    MOVE = 8,
    PLANT_BOMB = 9,
    DEFUSE_BOMB = 10
};

#endif
