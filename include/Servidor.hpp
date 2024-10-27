// include/Servidor.hpp
#ifndef SERVIDOR_HPP
#define SERVIDOR_HPP

#include "Juego.hpp"

class Servidor {
public:
    // Constructor that takes a port number
    Servidor(int port);
    
    // Method to start the server and initiate the game
    void iniciar();
    
    // Destructor
    ~Servidor();
    
private:
    int port;            // Port number the server listens on
    int server_fd;       // Server socket file descriptor
    int client_socket;   // Client socket file descriptor
    Juego* juego;        // Pointer to the Juego instance
};

#endif // SERVIDOR_HPP
