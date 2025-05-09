#ifndef COMMANDS_H
#define COMMANDS_H

#include <string>

enum CommandType { 
    CREATE_GAME = 0,
    JOIN_GAME = 1,
    BUY_WEAPON = 2,
    BUY_AMMO = 3,
    SHOOT = 4,
    DROP_WEAPON = 5, 
    ROTATE = 6,
    MOVE = 7,
    PLANT_BOMB = 8,
    DEFUSE_BOMB = 9
};

#endif
