#ifndef SERVER_PROTOCOL_PARSER_H
#define SERVER_PROTOCOL_PARSER_H

#include <cstdint>
#include <sstream>
#include <string>
#include <vector>

#include "../common/common_protocol_parser.h"
#include "../common/message.h"
#define LIST_GAMES_TITLE "Partidas:\n"
#define MARKER_LIST_ITEM " - "

class ServerProtocolParser : public CommonProtocolParser {
public:

};

#endif
