// src/Servidor.cpp
#include "Servidor.hpp"
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <iostream>
#include <cstring>
#include <stdexcept>

// Constructor
Servidor::Servidor(int port) : port(port), server_fd(-1), client_socket(-1), juego(nullptr) {
    // Create a socket
    server_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (server_fd == -1) {
        throw std::runtime_error("Failed to create socket");
    }

    // Allow address reuse
    int opt = 1;
    if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt)) < 0) {
        close(server_fd);
        throw std::runtime_error("setsockopt(SO_REUSEADDR) failed");
    }

    // Bind the socket to the specified port
    struct sockaddr_in address;
    memset(&address, 0, sizeof(address));
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY; // Bind to all interfaces
    address.sin_port = htons(port);

    if (bind(server_fd, (struct sockaddr*)&address, sizeof(address)) < 0) {
        close(server_fd);
        throw std::runtime_error("Failed to bind socket to port");
    }

    // Listen for incoming connections
    if (listen(server_fd, 1) < 0) {
        close(server_fd);
        throw std::runtime_error("Failed to listen on socket");
    }

    std::cout << "Server listening on port " << port << "...\n";
}

// Method to start the server and initiate the game
void Servidor::iniciar() {
    // Accept a client connection
    struct sockaddr_in client_address;
    socklen_t addrlen = sizeof(client_address);
    client_socket = accept(server_fd, (struct sockaddr*)&client_address, &addrlen);
    if (client_socket < 0) {
        throw std::runtime_error("Failed to accept client connection");
    }

    std::cout << "New client connected.\n";

    // Initialize players
    LocalPlayer localJugador('X');                 // Server's local player
    RemotePlayer remoteJugador('O', client_socket); // Client's remote player

    // Initialize the game (server starts first)
    bool isLocalPlayerFirst = true;
    juego = new Juego(&localJugador, &remoteJugador, isLocalPlayerFirst);

    // Start the game loop
    juego->jugar();

    // Clean up
    delete juego;
    close(client_socket);
}

// Destructor
Servidor::~Servidor() {
    if (client_socket != -1) {
        close(client_socket);
    }
    if (server_fd != -1) {
        close(server_fd);
    }
    if (juego != nullptr) {
        delete juego;
    }
}
