#ifndef SERVER_PROTOCOL_H
#define SERVER_PROTOCOL_H

#include <cstdint>
#include <functional>
#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>

#include "../common/common_protocol.h"
#include "../common/message.h"
#include "../common/socket.h"
#include "../common/codes_parser.h"
#include "../common/snapshot.h"

#define CODE_SUCCESS 0x01
#define CODE_FAIL 0x00

class ServerProtocol: public CommonProtocol, public CodesParser {
private:
    std::unordered_map<bool, uint8_t> codeSuccessResponse;
    std::unordered_map<CommandType, std::function<MessageFromClient(const CommandType& command)>> commandsManagers;

    MessageFromClient receiveCreateUsernameRequest(const CommandType& command);
    MessageFromClient receiveCreateGameRequest(const CommandType& command);
    MessageFromClient receiveJoinGameRequest(const CommandType& command);
    MessageFromClient receiveSelectMapRequest(const CommandType& command);
    MessageFromClient receiveBuyWeaponRequest(const CommandType& command);
    MessageFromClient receiveBuyWeaponAmmoRequest(const CommandType& command);
    MessageFromClient receiveAimRequest(const CommandType& command);
    MessageFromClient receiveMoveRequest(const CommandType& command);
    MessageFromClient receiveShootRequest(const CommandType& command);
    MessageFromClient receiveChangeWeaponRequest(const CommandType& command); 
    MessageFromClient receivePlantBombRequest(const CommandType& command);
    MessageFromClient receiveDefuseBombRequest(const CommandType& command);

    MessageFromClient receiveSelectSkinsRequest();

    // void send_players(const std::vector<Player>& players);
    // void send_bullets(const std::vector<Bullet>& bullets);
public:
    explicit ServerProtocol(Socket&& socket);
    void SendLobbyMessage(const ServerResponseLobby& msg);
    void SendStartGame(const ServerResponseLobby& msg);
    void SendSnapshot(const Snapshot& snapshot);
    void SendMessage(const MessageFromServer& msg);
    MessageFromClient Receive_command();
    void kill();
    ~ServerProtocol();
};

#endif
