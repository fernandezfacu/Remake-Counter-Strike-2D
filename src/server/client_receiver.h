#ifndef CLIENT_RECEIVER_H
#define CLIENT_RECEIVER_H

class ClientReceiver {
    private:
        &Queue<Command> queue; 
        // Me guardo la referencia de la queue del gameloop a la que voy a pushear los comandos.
        // creo que deberian ser directamente los MessageFromClient; 
    public:
        ClientReceiver();
        void receive_command_from_client();
        void add_command_to_queue(const Command& command);
        ~ClientReceiver();
};

#endif
