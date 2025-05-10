#ifndef GAME_MONITOR_H
#define GAME_MONITOR_H

#include <atomic>
#include <condition_variable>
#include <mutex>
#include <vector>

#include "server_protocol.h"

class ClientHandler;

class GameMonitor {
private:
    std::mutex mutex;
    std::vector<ClientHandler*> players;
    std::condition_variable gameIsReady;
    std::condition_variable isTurn;
    bool gameReady;

public:
    explicit GameMonitor(ClientHandler& client);

    bool ConnectSecondPlayer(ClientHandler& client);
    void WaitSecondPlayer();
    void MakePlayGame(ClientHandler& client);

    bool isFinished();
};

#endif
