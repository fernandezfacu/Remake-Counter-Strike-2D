#include <iostream>

#include "../common/error_codes.h"
#include "../common/liberror.h"

#include "client.h"

#define AMOUNT_OF_EXPECTED_ARGUMENTS 3
#define MESSAGE_BAD_AMOUNT_OF_EXPECTED_ARGUMENTS                      \
    "You must pass " + std::to_string(AMOUNT_OF_EXPECTED_ARGUMENTS) + \
            " arguments including the executable."
#define ARG_INDEX_HOSTNAME 1
#define ARG_INDEX_SERVICE 2

int main(int argc, char* argv[]) {
    if (argc != AMOUNT_OF_EXPECTED_ARGUMENTS) {
        std::cerr << MESSAGE_BAD_AMOUNT_OF_EXPECTED_ARGUMENTS << std::endl;
        return ErrorCodes::INVALID_ARGUMENTS;
    }
    std::string hostname = std::string(argv[ARG_INDEX_HOSTNAME]);
    std::string service = std::string(argv[ARG_INDEX_SERVICE]);
    try {
        Client client = Client(hostname, service);
        return client.Run();
    } catch (const LibError& e) {
        return ErrorCodes::SOCKET_ERROR;
    }
}
