#include "server_protocol.h"

#include <cstring>
#include <utility>

#include <sys/types.h>

ServerProtocol::ServerProtocol(Socket&& socket):
        CommonProtocol(std::move(socket)),
        codeToCommands({{CODE_CREATE_GAME, CommandType::CREATE_GAME},
                        {CODE_JOIN_GAME, CommandType::JOIN_GAME}}) {
    commandsManagers[CommandType::CREATE_GAME] = [this]() { return receiveCreateGameRequest(); };
    commandsManagers[CommandType::JOIN_GAME] = [this]() { return receiveJoinGameRequest(); };
}

void ServerProtocol::SendMessage(const MessageFromServer& msg) {
    if (msg.haveGame) {
        this->sendBoard(msg);
    } else {
        this->sendListGames(msg);
    }
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
