#ifndef CLIENT_RECEIVER_H
#define CLIENT_RECEIVER_H

class ClientSender {
    private: 
        Queue<Snapshot> queue;
    public:
        ClientSender();
        void receive_snapshot_from_server();
        Snapshot pop_snapshot_from_queue();
        ~ClientSender();
};

#endif
