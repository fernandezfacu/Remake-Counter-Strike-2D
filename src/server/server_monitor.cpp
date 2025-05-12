#include "server_monitor.h"

ServerMonitor::ServerMonitor() {
    this->game_id = 0;
}

bool ServerMonitor::CreateUsername(const std::string& username) {
    std::unique_lock<std::mutex> lck(this->mutex);
    auto result = this->players.insert(username);
    return result.second;
}

bool ServerMonitor::CreateNewGame(ClientHandler& client) {
    std::unique_lock<std::mutex> lck(this->mutex);
    auto result = this->gameMonitors.try_emplace(std::to_string(this->game_id), client.GetUsername());
    // despues acá utilizar UUID, tengo que buscar alguna library que lo haga
    return result.second;
}

bool ServerMonitor::JoinGame(const std::string& gameName, ClientHandler& client) {
    std::unique_lock<std::mutex> lck(this->mutex);
    auto it = this->gameMonitors.find(gameName);
    if (it != this->gameMonitors.end()) {
        return it->second.AddPlayer(client.GetUsername());
    } else {
        return false;
    }
}

void ServerMonitor::MakePlayGame(const std::string& gameName, ClientHandler& client) {
    auto it = this->gameMonitors.find(gameName);
    if (it != this->gameMonitors.end()) {
        it->second.MakePlayGame(client);
    }
}

GameMonitor& ServerMonitor::GetGameMonitor(const std::string& gameName) {
    return this->gameMonitors.at(gameName);
}

void ServerMonitor::ManageEndGame(const std::string& gameName) {
    this->gameMonitors.erase(gameName);
}
