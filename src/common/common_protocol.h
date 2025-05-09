#include <cstdint>
#include <string>
#include <vector>

#include <arpa/inet.h>

#include "error_codes.h"
#include "socket.h"

class CommonProtocol {
protected:
    Socket socket;

public:
    CommonProtocol(const std::string& hostname, const std::string& port);
    explicit CommonProtocol(Socket&& socket);

    uint8_t receiveByte();
    uint16_t receiveBigEndianNumber();
    void SendByte(const uint8_t& number);
    void SendBigEndianNumber(const uint16_t& number);
    void SendString(const std::string& s);
    std::string ReceiveString();
};
