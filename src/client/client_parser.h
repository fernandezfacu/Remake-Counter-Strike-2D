#ifndef CLIENT_PARSER_H
#define CLIENT_PARSER_H

#include <functional>
#include <string>
#include <unordered_map>
#include <vector>

#include "../common/commands.h"
#include "../common/message.h"

#define INDEX_REQUEST_TYPE_KEYWORD 0
#define CREATE_GAME_KEYWORD "crear"
#define LIST_GAMES_KEYWORD "listar"
#define JOIN_GAME_KEYWORD "unirse"
#define PLAY_GAME_KEYWORD "jugar"
#define INDEX_ROW_IN_PLAY_REQUEST 2
#define INDEX_COL_IN_PLAY_REQUEST 1
#define INDEX_GAME_NAME_IN_CREATE_REQUEST 1
#define INDEX_GAME_NAME_IN_JOIN_REQUEST 1

class ClientParser {
private:
    std::unordered_map<std::string, CommandType> commandsMap;
    std::unordered_map<CommandType,
                       std::function<MessageFromClient(const std::vector<std::string>& tokens)>>
            parsersMap;

    MessageFromClient parseCreateGameRequest(const std::vector<std::string>& tokens);
    MessageFromClient parseListGamesRequest(const std::vector<std::string>& tokens);
    MessageFromClient parseJoinGameRequest(const std::vector<std::string>& tokens);
    MessageFromClient makePlayGameRequest(const std::vector<std::string>& tokens);

public:
    ClientParser();

    MessageFromClient ParseRequest(const std::string& request);
};

#endif
