#include "client_handler.h"

#include <utility>
#include <vector>

#include <sys/socket.h>

#include "server_monitor.h"

ClientHandler::ClientHandler(Socket&& socket, ServerMonitor& server_monitor):
        protocol(std::move(socket)), server_monitor(server_monitor) {
    managersMap[CommandType::CREATE_GAME] = [this](const MessageFromClient& request) {
        return manageCreateGame(request);
    };
    managersMap[CommandType::JOIN_GAME] = [this](const MessageFromClient& request) {
        return manageJoinGame(request);
    };
}

void ClientHandler::run() {
    this->_is_alive = this->_keep_running = true;
    this->is_in_game = false;
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
        this->manageCommand(msg);
    }
}

MessageFromClient ClientHandler::ReceivePlay() { return this->protocol.ReceiveCommand(); }

void ClientHandler::launchGame() {
    while (!this->server_monitor.GetGameMonitor(this->my_game).isFinished()) {
        this->server_monitor.MakePlayGame(this->my_game, *this);
    }
    this->_keep_running = false;
}

void ClientHandler::sendLobbyResponse(const CommandType& command, const bool& success) {
    this->protocol.SendLobbyMessage(ServerResponseLobby{command, success});
}

void ClientHandler::SendStatusGame(const MessageFromServer& msg) {
    this->protocol.SendMessage(msg);
}

void ClientHandler::manageCommand(const MessageFromClient& msg) {
    this->managersMap.find(msg.commandType)->second(msg);
}

void ClientHandler::manageCreateUsername(const MessageFromClient& msg) {
    bool success = this->server_monitor.CreateUsername(msg.s);
    if (success) {
        this->username = msg.s;
    }
    this->sendLobbyResponse(msg.commandType, success);
}

void ClientHandler::manageCreateGame(const MessageFromClient& msg) {
    bool success = this->server_monitor.CreateNewGame(msg.s, *this);
    if (!this->isInGame() && success) {
        this->my_game = msg.s;
        this->is_in_game = true;
    }
    this->sendLobbyResponse(msg.commandType, success);
}

void ClientHandler::manageJoinGame(const MessageFromClient& msg) {
    bool success = this->server_monitor.JoinGame(msg.s, *this);
    if (!this->isInGame() && success) {
        this->is_in_game = true;
        this->my_game = msg.s;
    }
    this->sendLobbyResponse(msg.commandType, success);
}

void ClientHandler::manageEndGame() { this->server_monitor.ManageEndGame(this->my_game); }

void ClientHandler::kill() { this->_keep_running = false; }

bool ClientHandler::isInGame() { return this->is_in_game && this->my_game != ""; }
