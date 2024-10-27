// src/Cliente.cpp
#include "Cliente.hpp"
#include <sys/socket.h>    // For send and recv
#include <arpa/inet.h>     // For inet_pton
#include <unistd.h>        // For read and close
#include <iostream>
#include <cstring>
#include <stdexcept>

// Constructor
Cliente::Cliente(const std::string& server_ip, int port) 
    : server_ip(server_ip), port(port), sock(-1), juego(nullptr) {
    // Create a socket
    sock = socket(AF_INET, SOCK_STREAM, 0);
    if (sock == -1) {
        throw std::runtime_error("Failed to create socket");
    }

    // Define server address
    struct sockaddr_in server_address;
    memset(&server_address, 0, sizeof(server_address));
    server_address.sin_family = AF_INET;
    server_address.sin_port = htons(port);

    // Convert IPv4 address from text to binary form
    if (inet_pton(AF_INET, server_ip.c_str(), &server_address.sin_addr) <= 0) {
        close(sock);
        throw std::runtime_error("Invalid address or address not supported");
    }

    // Connect to the server
    if (connect(sock, (struct sockaddr*)&server_address, sizeof(server_address)) < 0) {
        close(sock);
        throw std::runtime_error("Connection to server failed");
    }

    std::cout << "Connected to the server.\n";
}

// Method to start the client and initiate the game
void Cliente::iniciar() {
    // Initialize players
    LocalPlayer localJugador('O');                 // Client's local player
    RemotePlayer remoteJugador('X', sock);         // Server's remote player

    // Initialize the game (server starts first, so client waits)
    bool isLocalPlayerFirst = false;
    juego = new Juego(&localJugador, &remoteJugador, isLocalPlayerFirst);

    // Start the game loop
    juego->jugar();

    // Clean up
    delete juego;
    close(sock);
}

// Destructor
Cliente::~Cliente() {
    if (sock != -1) {
        close(sock);
    }
    if (juego != nullptr) {
        delete juego;
    }
}
