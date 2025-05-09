#include "client_parser.h"

#include <string>
#include <vector>

ClientParser::ClientParser() {
    this->commandsMap = {{CREATE_GAME_KEYWORD, CommandType::CREATE_GAME},
                         {JOIN_GAME_KEYWORD, CommandType::JOIN_GAME}};
    parsersMap[CommandType::CREATE_GAME] = [this](const std::vector<std::string>& tokens) {
        return parseCreateGameRequest(tokens);
    };
    parsersMap[CommandType::JOIN_GAME] = [this](const std::vector<std::string>& tokens) {
        return parseJoinGameRequest(tokens);
    };
}

MessageFromClient ClientParser::ParseRequest(const std::string& request) {
    CommandType command = this->commandsMap.find(splitted[INDEX_REQUEST_TYPE_KEYWORD])->second;
    return this->parsersMap.find(command)->second(splitted);
}

MessageFromClient ClientParser::parseCreateGameRequest(const std::vector<std::string>& tokens) {
    return MessageFromClient{CommandType::CREATE_GAME, tokens[INDEX_GAME_NAME_IN_CREATE_REQUEST]};
}

MessageFromClient ClientParser::parseJoinGameRequest(const std::vector<std::string>& tokens) {
    return MessageFromClient{CommandType::JOIN_GAME, tokens[INDEX_GAME_NAME_IN_JOIN_REQUEST]};
}

