#include "client_protocol.h"

#include <cstdint>
#include <cstring>
#include <string>

#include <arpa/inet.h>
#include <sys/socket.h>

#include "../common/commands.h"
#include "../common/communication_ended.h"
#include "../common/message.h"

ClientProtocol::ClientProtocol(const std::string& hostname, const std::string& port):
        CommonProtocol(hostname, port), parser(), isAlive(true) {
    sendersMap[CommandType::CREATE_USERNAME] = [this](const InternalMessage& request) {
        this->sendCreateUsernameRequest(request);
    };
    sendersMap[CommandType::CREATE_GAME] = [this](const InternalMessage& request) {
        return this->sendCreateGameRequest(request);
    };
    sendersMap[CommandType::JOIN_GAME] = [this](const InternalMessage& request) {
        return this->sendJoinGameRequest(request);
    };
    sendersMap[CommandType::SELECT_SKINS] = [this](const InternalMessage& request) {
        return this->sendSelectSkinsRequest(request);
    };
    sendersMap[CommandType::SELECT_MAP] = [this](const InternalMessage& request) {
        return this->sendSelectMapRequest(request);
    };
    sendersMap[CommandType::BUY_WEAPON] = [this](const InternalMessage& request) {
        return this->sendBuyWeaponRequest(request);
    };
    sendersMap[CommandType::BUY_AMMO] = [this](const InternalMessage& request) {
        return this->sendBuyWeaponAmmoRequest(request);
    };
    sendersMap[CommandType::AIM] = [this](const InternalMessage& request) {
        return this->sendAimRequest(request);
    };
    sendersMap[CommandType::MOVE] = [this](const InternalMessage& request) {
        return this->sendMoveRequest(request);
    };
    sendersMap[CommandType::SHOOT] = [this](const InternalMessage& request) {
        return this->sendShootRequest(request);
    };
    sendersMap[CommandType::CHANGE_WEAPON] = [this](const InternalMessage& request) {
        return this->sendChangeWeaponRequest(request); 
    };
    sendersMap[CommandType::PLANT_BOMB] = [this](const InternalMessage& request) {
        return this->sendPlantBombRequest(request);
    };
    sendersMap[CommandType::DEFUSE_BOMB] = [this](const InternalMessage& request) {
        return this->sendDefuseBombRequest(request);
    };
}

ServerResponseLobby ClientProtocol::ReceiveCommand() {
    // aca para la etapa de lobby recibo:
        // rta de pedido de crear nombre de usuario
        // rta de pedido de crear partida
        // rta de pedio de joinear partida
        // notificacion de empezó partida -> aca lanzó los hilos y queues
    uint8_t code = this->receiveByte();
    ServerResponseLobby response = ServerResponseLobby{this->codeToCommands.find(code)->second};
    if (this->codeToCommands.find(code)->second != CommandType::GAME_STARTED) {
        response.success = this->receiveByte();
    }
    return response;
}

void ClientProtocol::SendCommand(const MessageFromClient& request) {
    InternalMessage msg = this->parser.ParseMessage(request);
    this->SendByte(msg.code_message);
    this->sendersMap.find(request.commandType)->second(msg);
}

void ClientProtocol::sendCreateUsernameRequest(const InternalMessage& request) {
    this->SendString(request.s);
}

void ClientProtocol::sendCreateGameRequest(const InternalMessage& request) {
    this->SendByte(request.size_players);
}

void ClientProtocol::sendJoinGameRequest(const InternalMessage& request) {
    this->SendString(request.s);
}

void ClientProtocol::sendSelectSkinsRequest(const InternalMessage& request) {
    this->SendByte(request.skin_id_tt);
    this->SendByte(request.skin_id_ct);
}


void ClientProtocol::sendSelectMapRequest(const InternalMessage& request) {
    this->SendByte(request.map_id);
}

void ClientProtocol::sendBuyWeaponRequest(const InternalMessage& request) {
    this->SendByte(request.code_weapon);
}

void ClientProtocol::sendBuyWeaponAmmoRequest(const InternalMessage& request) {
    this->SendByte(request.code_weapon_type);
    this->SendBigEndianNumber(request.bullets);
}

void ClientProtocol::sendAimRequest(const InternalMessage& request) {
    this->SendByte(request.pos_x);
    this->SendByte(request.pos_y);
}

void ClientProtocol::sendMoveRequest(const InternalMessage& request) {
    this->SendByte(request.direction);
}

void ClientProtocol::sendShootRequest(const InternalMessage& request) {
    
}

void ClientProtocol::sendChangeWeaponRequest(const InternalMessage& request) {
    this->SendByte(request.code_weapon_type);
}

void ClientProtocol::sendPlantBombRequest(const InternalMessage& request) {
    
}

void ClientProtocol::sendDefuseBombRequest(const InternalMessage& request) {

}

/*

void ClientProtocol::receive_snapshot() {
    Snapshot snapshot = Snapshot{};
    snasphot.phase = Phase(this->receiveByte());
    snasphot.round_number = this->receiveByte();
    snasphot.bomb_status = BombStatus(this->receiveByte());
    snasphot.timer = this->receiveByte();
    int size_players = this->receiveByte();
    //snapshot.players = this->receive_players(size_players);
    int size_bullets = this->receiveByte();
    //snapshot.bullets = this->receive_bullets(size_bullets);
}

// ME LO COPIA ACA PARA VER QUE ENVIO

std::vector<Player> ClientProtocol::receive_players(const int& size_players) {
    std::vector<Player> players = {};
    for (int i = 0; i < size_players; i++) {
        std::string username = this->ReceiveString();
        uint8_t pos_x = this->ReceiveByte();
        uint8_t pos_y = this->ReceiveByte();
        uint8_t pos_cros_x = this->ReceiveByte();
        uint8_t pos_cros_y = this->ReceiveByte();
        uint16_t money = this->ReceiveBigEndianNumber();
        uint8_t health = this->ReceiveByte();
        bool kave_knife = this->ReceiveByte() == 0x01;
        Weapon primary_weapon = this->weaponParser(this->ReceiveByte());
        uint16_t primary_weapon_bullets = this->ReceiveBigEndianNumber();
        Weapon secondary_weapon = this->weaponParser(this->ReceiveByte());
        uint16_t secondary_weapon_bullets = this->ReceiveBigEndianNumber();
        bool have_bomb = this->ReceiveByte() == 0x01;
        bool is_shooting = this->ReceiveByte() == 0x01;
        uint8_t weapon_equipped_code = this->ReceiveByte();
        players.push_back(Player(username, pos_x, pos_y, pos_cros_x, 
        pos_cros_y, money, health, have_knife, primary_weapon, 
        primary_weapon_bullets, secondary_weapon, secondary_weapon_bullets,
        have_bomb, is_shooting, weapon_equipped_code));
    }
    return players;
}


std::vector<Bullet> ClientProtocol::receive_bullets(const int& size_bullets) {
    std::vector<Bullet> bullets = {};
    for (int i = 0; i < size_bullets; i++) {
        uint8_t id = this->ReceiveByte();
        uint8_t pos_x = this->ReceiveByte();
        uint8_t pos_y = this->ReceiveByte();
        uint8_t dir_x = this->ReceiveByte();
        uint8_t dir_y = this->ReceiveByte();
        bullets.push_back(Bullet(id, pos_x, pos_y, dir_x, dir_y));
    }
    return bullets;
}
*/

void ClientProtocol::Close() {
    this->socket.shutdown(SHUT_RDWR);
    this->socket.close();
}

ClientProtocol::~ClientProtocol() {}
