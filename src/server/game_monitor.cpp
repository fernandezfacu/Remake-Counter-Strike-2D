#include "game_monitor.h"

#include "client_handler.h"

GameMonitor::GameMonitor(ClientHandler& client): gameReady(false) {
    players.push_back(&client);
}

bool GameMonitor::ConnectSecondPlayer(ClientHandler& client) {
    if (this->players.size() == 1) {
        this->players.push_back(&client);
        this->gameReady = true;
        this->gameIsReady.notify_all();
        return true;
    }
    return false;
}

void GameMonitor::WaitSecondPlayer() {
    std::unique_lock<std::mutex> lck(this->mutex);
    this->gameIsReady.wait(lck, [&]() { return this->gameReady; });
}

void GameMonitor::MakePlayGame(ClientHandler& client) {
}

bool GameMonitor::isFinished() {
    return false;
}
