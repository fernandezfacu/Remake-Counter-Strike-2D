#include "server_protocol.h"

#include <cstring>
#include <utility>

#include <sys/types.h>

ServerProtocol::ServerProtocol(Socket&& socket):
        CommonProtocol(std::move(socket)),
        codeToCommands({{CODE_CREATE_USERNAME, CommandType::CREATE_USERNAME},
                        {CODE_CREATE_GAME, CommandType::CREATE_GAME},
                        {CODE_JOIN_GAME, CommandType::JOIN_GAME}}),
        commandsToCode({{CommandType::CREATE_USERNAME, CODE_CREATE_USERNAME},
                        {CommandType::CREATE_GAME, CODE_CREATE_GAME},
                        {CommandType::JOIN_GAME, CODE_JOIN_GAME}}),
        codeSuccessResponse({{true, CODE_SUCCESS}, 
                            {false, CODE_FAIL}}) {
    commandsManagers[CommandType::CREATE_USERNAME] = [this]() { return receiveCreateUsernameRequest(); };
    commandsManagers[CommandType::CREATE_GAME] = [this]() { return receiveCreateGameRequest(); };
    commandsManagers[CommandType::JOIN_GAME] = [this]() { return receiveJoinGameRequest(); };
    
}

void ServerProtocol::SendLobbyMessage(const ServerResponseLobby& msg) {
    this->SendByte(this->commandsToCode.find(msg.commandType)->second);
    this->SendByte(this->codeSuccessResponse.find(msg.success)->second);
}

void ServerProtocol::sendListGames(const MessageFromServer& msg) {
    std::string toSend = this->protocolParser.ParseListToString(msg.listGames);
    this->SendString(toSend);
}

void ServerProtocol::sendBoard(const MessageFromServer& msg) {
    std::string response = this->protocolParser.ParseBoardResponse(msg);
    this->SendString(response);
}

MessageFromClient ServerProtocol::ReceiveCommand() {
    uint8_t commandCode = this->receiveByte();
    CommandType command = this->codeToCommands.find(commandCode)->second;
    return this->commandsManagers.find(command)->second();
}

MessageFromClient ServerProtocol::receiveCreateUsernameRequest() {
    std::string username = this->ReceiveString();
    return MessageFromClient{CommandType::CREATE_USERNAME, username};
}

MessageFromClient ServerProtocol::receiveCreateGameRequest() {
    std::string gameName = this->ReceiveString();
    return MessageFromClient{CommandType::CREATE_GAME, gameName};
}

MessageFromClient ServerProtocol::receiveJoinGameRequest() {
    std::string gameName = this->ReceiveString();
    return MessageFromClient{CommandType::JOIN_GAME, gameName};
}

void ServerProtocol::kill() {
    this->socket.shutdown(SHUT_RDWR);
    this->socket.close();
}

ServerProtocol::~ServerProtocol() {}
