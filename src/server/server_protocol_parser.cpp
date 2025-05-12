#include "server_protocol_parser.h"

std::vector<uint8_t> ServerProtocolParser::ParseByteToRowAndCol(const uint8_t& byte) {
    uint8_t row = (byte >> 4) & 0x0F;
    uint8_t col = byte & 0x0F;
    std::vector<uint8_t> response = {row, col};
    return response;
}

std::string ServerProtocolParser::ParseListToString(const std::vector<std::string>& listGames) {
    std::stringstream response;
    response << LIST_GAMES_TITLE;
    for (auto const& game: listGames) {
        response << MARKER_LIST_ITEM << game << "\n";
    }
    return response.str();
}

std::string ServerProtocolParser::ParseBoardResponse(const MessageFromServer& msg) {
    std::stringstream response;
    response << this->boardParser.ParseDataToBoard(msg.game.board);
    response << msg.extraMessage;
    return response.str();
}
