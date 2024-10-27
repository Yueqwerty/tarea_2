// include/Cliente.hpp
#ifndef CLIENTE_HPP
#define CLIENTE_HPP

#include "Juego.hpp"
#include <string>

class Cliente {
public:
    // Constructor that takes server IP as string and port
    Cliente(const std::string& server_ip, int port);
    
    // Method to start the client and initiate the game
    void iniciar();
    
    // Destructor
    ~Cliente();
    
private:
    std::string server_ip; // Server IP address
    int port;              // Server port number
    int sock;              // Client socket file descriptor
    Juego* juego;          // Pointer to the Juego instance
};

#endif // CLIENTE_HPP
