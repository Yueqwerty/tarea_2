// src/RemotePlayer.cpp
#include "RemotePlayer.hpp"
#include <sys/socket.h>    // For send and recv
#include <unistd.h>        // For read and close
#include <iostream>
#include <cstring>
#include <cstdlib>
#include <string>
#include <algorithm>
#include <stdexcept>

// Constructor
RemotePlayer::RemotePlayer(char symbol, int socket_fd) : symbol(symbol), socket_fd(socket_fd) {}

// Get the player's symbol
char RemotePlayer::getSymbol() const {
    return symbol;
}

// Receive a move from the remote player
int RemotePlayer::getMove(const Tablero& /*tablero*/) { // 'tablero' is intentionally unused
    std::string mensaje;
    char ch;

    // Read until newline
    while (true) {
        ssize_t valread = read(socket_fd, &ch, 1);
        if (valread == 0) {
            throw std::runtime_error("Connection closed by the remote player.");
        }
        if (valread < 0) {
            throw std::runtime_error("Read error while receiving move.");
        }
        if (ch == '\n') {
            break;
        }
        mensaje += ch;
    }

    // Trim any carriage return characters
    if (!mensaje.empty() && mensaje.back() == '\r') {
        mensaje.pop_back();
    }

    // Convert to integer
    try {
        int columna = std::stoi(mensaje) - 1; // Adjust to 0-based index
        return columna;
    }
    catch (const std::invalid_argument& e) {
        throw std::runtime_error("Received invalid move: " + mensaje);
    }
}

// Send a move to the remote player
void RemotePlayer::sendMove(int columna) {
    std::string moveStr = std::to_string(columna + 1) + "\n"; // Convert to 1-based index and append newline

    ssize_t totalSent = 0;
    ssize_t toSend = moveStr.size();
    const char* data = moveStr.c_str();

    while (totalSent < toSend) {
        ssize_t sent = send(socket_fd, data + totalSent, toSend - totalSent, 0);
        if (sent == -1) {
            throw std::runtime_error("Failed to send move to the remote player.");
        }
        totalSent += sent;
    }
}
