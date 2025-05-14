#include "server_protocol.h"

#include <cstring>
#include <utility>
#include "../common/skins.h"

#include <sys/types.h>

ServerProtocol::ServerProtocol(Socket&& socket):
        CommonProtocol(std::move(socket)),
        codeSuccessResponse({{true, CODE_SUCCESS}, 
                            {false, CODE_FAIL}}) {
    commandsManagers[CommandType::CREATE_USERNAME] = [this](const CommandType& command) { return receiveCreateUsernameRequest(command); };
    commandsManagers[CommandType::CREATE_GAME] = [this](const CommandType& command) { return receiveCreateGameRequest(command); };
    commandsManagers[CommandType::JOIN_GAME] = [this](const CommandType& command) { return receiveJoinGameRequest(command); };
    commandsManagers[CommandType::SELECT_SKINS] = [this](const CommandType& command) { return receiveSelectSkinsRequest(command); };
    commandsManagers[CommandType::SELECT_MAP] = [this](const CommandType& command) { return receiveSelectMapRequest(command); };
    commandsManagers[CommandType::BUY_WEAPON] = [this](const CommandType& command) { return receiveBuyWeaponRequest(command); };
    commandsManagers[CommandType::BUY_AMMO] = [this](const CommandType& command) { return receiveBuyWeaponAmmoRequest(command); };
    commandsManagers[CommandType::AIM] = [this](const CommandType& command) { return receiveAimRequest(command); };
    commandsManagers[CommandType::MOVE] = [this](const CommandType& command) { return receiveMoveRequest(command); };
    commandsManagers[CommandType::SHOOT] = [this](const CommandType& command) { return receiveShootRequest(command); };
    commandsManagers[CommandType::CHANGE_WEAPON] = [this](const CommandType& command) { return receiveChangeWeaponRequest(command); };
    commandsManagers[CommandType::PLANT_BOMB] = [this](const CommandType& command) { return receivePlantBombRequest(command); };
    commandsManagers[CommandType::DEFUSE_BOMB] = [this](const CommandType& command) { return receiveDefuseBombRequest(command); };
}

void ServerProtocol::SendLobbyMessage(const ServerResponseLobby& msg) {
    this->SendByte(this->commandsToCode.find(msg.commandType)->second);
    this->SendByte(this->codeSuccessResponse.find(msg.success)->second);
}

void ServerProtocol::SendStartGame(const ServerResponseLobby& msg) {
    this->SendByte(this->commandsToCode.find(msg.commandType)->second);
}

void ServerProtocol::SendSnapshot(const Snapshot& snapshot) {
    this->SendByte(snapshot.phase);
    this->SendByte(snapshot.round_number);
    this->SendByte(snapshot.bomb_status);
    this->SendByte(snapshot.timer);
    //this->SendByte(snapshot.players.size());
    //this->send_players(snapshot.players);
    //this->SendByte(snapshot.bullets.size());
    //this->send_bullets(snapshot.bullets);
}

/*
void ServerProtocol::send_players(const std::vector<Player>& players) {
    for (auto player : players) {
        this->SendString(player.username);
        this->SendByte(player.pos_x);
        this->SendByte(player.pos_y);
        this->SendByte(player.pos_cros_x);
        this->SendByte(player.pos_cros_y);
        this->SendBigEndianNumber(player.money);
        this->SendByte(player.health);
        this->SendByte(player.equipment.have_knife ? 0x01 : 0x00);
        this->SendByte(this->weaponParser.getWeaponCode(player.equipment.primary_weapon));
        this->SendBigEndianNumber(player.equipment.primary_weapon.bullets);
        this->SendByte(this->weaponParser.getWeaponCode(player.equipment.secondary_weapon));
        this->SendBigEndianNumber(player.equipment.secondary_weapon.bullets);
        this->SendByte(player.equipment.have_bomb ? 0x01 : 0x00);
        this->SendByte(player.is_shooting ? 0x01 : 0x00);
        this->SendByte(player.weapon_equipped);
    }
}

void ServerProtocol::send_bullets(const std::vector<Bullet>& bullets) {
    for (auto bullet : bullets) {
        this->SendByte(bullet.id);
        this->SendByte(bullet.pos_x);
        this->SendByte(bullet.pos_y);
        this->SendByte(bullet.dir_x);
        this->SendByte(bullet.dir_y);
    }
}
*/

MessageFromClient ServerProtocol::ReceiveCommand() {
    uint8_t commandCode = this->receiveByte();
    CommandType command = this->codeToCommands.find(commandCode)->second;
    return this->commandsManagers.find(command)->second(command);
}

MessageFromClient ServerProtocol::receiveCreateUsernameRequest(const CommandType& command) {
    std::string username = this->ReceiveString();
    return MessageFromClient{command, username};
}

MessageFromClient ServerProtocol::receiveCreateGameRequest(const CommandType& command) {
    uint8_t size_players = this->receiveByte();
    MessageFromClient msg = MessageFromClient{command};
    msg.size_players = size_players;
    return msg;
}

MessageFromClient ServerProtocol::receiveJoinGameRequest(const CommandType& command) {
    std::string gameName = this->ReceiveString();
    return MessageFromClient{command, gameName};
}

MessageFromClient ServerProtocol::receiveSelectSkinsRequest(const CommandType& command) {
    uint8_t skin_id_tt = this->receiveByte();
    uint8_t skin_id_ct = this->receiveByte();
    MessageFromClient msg = MessageFromClient{command};
    msg.tt_skin = TerroristSkin(skin_id_tt - 1);
    msg.ct_skin = CounterTerroristSkin(skin_id_ct - 1);
    return msg;
}

MessageFromClient ServerProtocol::receiveSelectMapRequest(const CommandType& command) {
    MessageFromClient msg = MessageFromClient{command};
    // msg.map_id = Map(this->receiveByte());
    // falta lo del enum o lo que fuere
    return msg;
}

MessageFromClient ServerProtocol::receiveBuyWeaponRequest(const CommandType& command) {
    Weapon weapon = Weapon(this->receiveByte());
    MessageFromClient msg = MessageFromClient{command};
    msg.weapon = weapon;
    return msg;
}

MessageFromClient ServerProtocol::receiveBuyWeaponAmmoRequest(const CommandType& command) {
    WeaponType weapon_type = WeaponType(this->receiveByte());
    uint16_t bullets = this->receiveBigEndianNumber();
    MessageFromClient msg = MessageFromClient{command};
    msg.weaponType = weapon_type;
    msg.bullets = bullets;
    return msg;
}

MessageFromClient ServerProtocol::receiveAimRequest(const CommandType& command) {
    uint8_t pos_x = this->receiveByte();
    uint8_t pos_y = this->receiveByte();
    MessageFromClient msg = MessageFromClient{command};
    msg.pos_x = pos_x;
    msg.pos_y = pos_y;
    return msg;
}

MessageFromClient ServerProtocol::receiveMoveRequest(const CommandType& command) {
    uint8_t direction = this->receiveByte();
    MessageFromClient msg = MessageFromClient{command};
    msg.movement = Movement(direction - 1);
    return msg; 
}

MessageFromClient ServerProtocol::receiveShootRequest(const CommandType& command) {
    return MessageFromClient{command};
}

MessageFromClient ServerProtocol::receiveChangeWeaponRequest(const CommandType& command) {
    MessageFromClient msg = MessageFromClient{command};
    msg.weaponType = WeaponType(this->receiveByte());
    return msg;
}

MessageFromClient ServerProtocol::receivePlantBombRequest(const CommandType& command) {
    return MessageFromClient{command};
}

MessageFromClient ServerProtocol::receiveDefuseBombRequest(const CommandType& command) {
    return MessageFromClient{command};
}

void ServerProtocol::kill() {
    this->socket.shutdown(SHUT_RDWR);
    this->socket.close();
}

ServerProtocol::~ServerProtocol() {}
