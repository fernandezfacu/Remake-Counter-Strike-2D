#ifndef SERVER_MONITOR_H
#define SERVER_MONITOR_H

#include <map>
#include <memory>
#include <mutex>
#include <string>
#include <vector>
#include <set>

#include "game_monitor.h"

class ServerMonitor {
private:
    std::mutex mutex;
    std::set<std::string> players;
    std::map<std::string, std::string> players_in_game;
    std::map<std::string, GameMonitor> gameMonitors;

public:
    bool CreateUsername(const std::string& username);
    bool CreateNewGame(const std::string& gameName, ClientHandler& client);
    std::vector<std::string> ListGames();
    bool JoinGame(const std::string& gameName, ClientHandler& client);
    void MakePlayGame(const std::string& gameName, ClientHandler& client);
    GameMonitor& GetGameMonitor(const std::string& gameName);
    void ManageEndGame(const std::string& gameName);
};

#endif
