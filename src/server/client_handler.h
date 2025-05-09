#ifndef CLIENT_HANDLER_H
#define CLIENT_HANDLER_H

#include <string>
#include <unordered_map>

#include "../common/socket.h"
#include "../common/thread.h"

#include "server_monitor.h"
#include "server_protocol.h"

class ClientHandler: public Thread {
private:
    ServerProtocol protocol;
    std::atomic_bool keepTalking;
    std::atomic_bool isAlive;
    std::unordered_map<CommandType,
                       std::function<void(const MessageFromClient& request, bool& isInGame)>>
            managersMap;
    ServerMonitor& serverMonitor;
    std::string myGame;

    void manageCommand(const MessageFromClient& msg, bool& hasEnteredGame);
    void manageCreateGame(const MessageFromClient& msg, bool& hasEnteredGame);
    void manageListGames(const MessageFromClient& msg, const bool& hasEnteredGame);
    void manageJoinGame(const MessageFromClient& msg, bool& hasEnteredGame);
    void manageEndGame();
    bool isInGame();
    MessageFromClient ReceiveMessage();
    void launchLobby();
    void launchGame();

public:
    ClientHandler(Socket&& socket, ServerMonitor& serverMonitor);
    void SendStatusGame(const MessageFromServer& msg);
    MessageFromClient ReceivePlay();
    void run() override;
    void kill();
};

#endif
