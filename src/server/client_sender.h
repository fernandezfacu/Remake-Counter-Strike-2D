#ifndef CLIENT_SENDER_H
#define CLIENT_SENDER_H

#include "../common/queue.h"

class ClientSender {
    private: 
        Queue<Snapshot> queue;
    public:
        ClientSender();
        void add_snapshot_to_queue(const Snapshot& snapshot);
        void send_snapshot_to_client();
        ~ClientSender();
};

#endif
