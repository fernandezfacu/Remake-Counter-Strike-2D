#ifndef CLIENT_SENDER_H
#define CLIENT_SENDER_H

class ClientSender {
    private: 
        Queue<Command> queue;
    public:
        ClientSender();
        void add_command_to_queue(const Command& command);
        void send_command_to_server();
        ~ClientSender();
};

#endif
