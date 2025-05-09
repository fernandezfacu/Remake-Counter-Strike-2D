#include "client_protocol_parser.h"

ClientProtocolParser::ClientProtocolParser() {
    parsersMap[CommandType::CREATE_GAME] = [this](const MessageFromClient& request) {
        return this->parseFromCreateGameRequest(request);
    };
    parsersMap[CommandType::LIST_GAMES] = [this](const MessageFromClient& request) {
        return this->parseFromListGameRequest(request);
    };
    parsersMap[CommandType::JOIN_GAME] = [this](const MessageFromClient& request) {
        return this->parseFromJoinGameRequest(request);
    };
    parsersMap[CommandType::MAKE_PLAY] = [this](const MessageFromClient& request) {
        return this->parseFromMakePlayGameRequest(request);
    };
}

InternalMessage ClientProtocolParser::ParseMessage(const MessageFromClient& message) {
    return this->parsersMap.find(message.commandType)->second(message);
}


InternalMessage ClientProtocolParser::parseFromCreateGameRequest(const MessageFromClient& request) {
    return InternalMessage{CODE_CREATE_GAME, request.gameName};
}

InternalMessage ClientProtocolParser::parseFromListGameRequest(const MessageFromClient& request) {
    return InternalMessage{
            CODE_LIST_GAMES,
    };
}

InternalMessage ClientProtocolParser::parseFromJoinGameRequest(const MessageFromClient& request) {
    return InternalMessage{CODE_JOIN_GAME, request.gameName};
}

InternalMessage ClientProtocolParser::parseFromMakePlayGameRequest(
        const MessageFromClient& request) {
    return InternalMessage{
            CODE_MAKE_PLAYGAME,
            "",
            this->cellParser.ParseFromCell(request.cell),
    };
}

uint8_t ClientProtocolParser::ParseCoordinatesForSend(const std::vector<int>& coordinates) {
    return (coordinates[INDEX_ROW] << 4) | (coordinates[INDEX_COL]);
}
