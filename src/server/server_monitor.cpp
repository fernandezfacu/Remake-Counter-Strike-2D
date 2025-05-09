#include "server_monitor.h"

bool ServerMonitor::CreateNewGame(const std::string& gameName, ClientHandler& client) {
    std::unique_lock<std::mutex> lck(this->mutex);
    auto result = this->gameMonitors.try_emplace(gameName, client);
    return result.second;
}

std::vector<std::string> ServerMonitor::ListGames() {
    std::unique_lock<std::mutex> lck(this->mutex);
    std::vector<std::string> games;
    for (std::map<std::string, GameMonitor>::iterator it = this->gameMonitors.begin();
         it != this->gameMonitors.end(); ++it) {
        games.push_back(it->first);
    }
    return games;
}

bool ServerMonitor::JoinGame(const std::string& gameName, ClientHandler& client) {
    std::unique_lock<std::mutex> lck(this->mutex);
    auto it = this->gameMonitors.find(gameName);
    if (it != this->gameMonitors.end()) {
        return it->second.ConnectSecondPlayer(client);
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
