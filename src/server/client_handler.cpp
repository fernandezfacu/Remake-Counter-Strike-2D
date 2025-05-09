#include "client_handler.h"

#include <utility>
#include <vector>

#include <sys/socket.h>

#include "server_monitor.h"

ClientHandler::ClientHandler(Socket&& socket, ServerMonitor& serverMonitor):
        protocol(std::move(socket)), serverMonitor(serverMonitor) {
    managersMap[CommandType::CREATE_GAME] = [this](const MessageFromClient& request,
                                                   bool& isInGame) {
        return manageCreateGame(request, isInGame);
    };
    managersMap[CommandType::JOIN_GAME] = [this](const MessageFromClient& request, bool& isInGame) {
        return manageJoinGame(request, isInGame);
    };
    managersMap[CommandType::LIST_GAMES] = [this](const MessageFromClient& request,
                                                  const bool& isInGame) {
        return manageListGames(request, isInGame);
    };
}

void ClientHandler::run() {
    this->_is_alive = this->_keep_running = true;
    while (this->_keep_running) {
        this->launchLobby();
        this->launchGame();
    }
    this->manageEndGame();
    this->_is_alive = false;
    this->protocol.kill();
}

void ClientHandler::launchLobby() {
    bool hasEnteredGame = false;
    while (!hasEnteredGame) {
        MessageFromClient msg = this->protocol.ReceiveCommand();
        this->manageCommand(msg, hasEnteredGame);
    }
}

MessageFromClient ClientHandler::ReceivePlay() { return this->protocol.ReceiveCommand(); }

void ClientHandler::launchGame() {
    while (!this->serverMonitor.GetGameMonitor(this->myGame).isFinished()) {
        this->serverMonitor.MakePlayGame(this->myGame, *this);
    }
    this->_keep_running = false;
}

void ClientHandler::SendStatusGame(const MessageFromServer& msg) {
    this->protocol.SendMessage(msg);
}

void ClientHandler::manageCommand(const MessageFromClient& msg, bool& hasEnteredGame) {
    this->managersMap.find(msg.commandType)->second(msg, hasEnteredGame);
}

void ClientHandler::manageCreateGame(const MessageFromClient& msg, bool& hasEnteredGame) {
    hasEnteredGame = this->serverMonitor.CreateNewGame(msg.gameName, *this);
    if (!this->isInGame() && hasEnteredGame) {
        this->myGame = msg.gameName;
        GameMonitor& monitor = this->serverMonitor.GetGameMonitor(msg.gameName);
        monitor.WaitSecondPlayer();
        Game game = monitor.GetGame();
        this->SendStatusGame(MessageFromServer{true, this->gameParser.GameToDTO(game), ""});
    }
}

void ClientHandler::manageListGames(const MessageFromClient& msg, const bool& hasEnteredGame) {
    std::vector<std::string> games = this->serverMonitor.ListGames();
    MessageFromServer msgServer = MessageFromServer{
            false,
            GameDTO{},
            "",
            games,
    };
    this->protocol.SendMessage(msgServer);
}

void ClientHandler::manageJoinGame(const MessageFromClient& msg, bool& hasEnteredGame) {
    hasEnteredGame = this->serverMonitor.JoinGame(msg.gameName, *this);
    if (!this->isInGame() && hasEnteredGame) {
        this->myGame = msg.gameName;
    }
}

void ClientHandler::manageEndGame() { this->serverMonitor.ManageEndGame(this->myGame); }

void ClientHandler::kill() { this->_keep_running = false; }

bool ClientHandler::isInGame() { return this->myGame != ""; }
