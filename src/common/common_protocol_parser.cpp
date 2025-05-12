#include "common_protocol_parser.h"

CodesParser::CodesParser() :         
        codeToCommands({
            {CODE_CREATE_USERNAME, CommandType::CREATE_USERNAME},
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
            {CODE_DEFUSE_BOMB, CommandType::DEFUSE_BOMB}
        }),
        commandsToCode({
            {CommandType::CREATE_USERNAME, CODE_CREATE_USERNAME},
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
            {CommandType::DEFUSE_BOMB, CODE_DEFUSE_BOMB}
        }) {}
