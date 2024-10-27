// include/RemotePlayer.hpp
#ifndef REMOTEPLAYER_HPP
#define REMOTEPLAYER_HPP

#include "Tablero.hpp"

class RemotePlayer {
public:
    // Constructor
    RemotePlayer(char symbol, int socket_fd);

    // Get the player's symbol
    char getSymbol() const;

    // Receive a move from the remote player
    int getMove(const Tablero& tablero); // 'tablero' is unused but included for interface consistency

    // Send a move to the remote player
    void sendMove(int columna);

private:
    char symbol;      // Player's symbol ('X' or 'O')
    int socket_fd;    // Socket file descriptor for communication
};

#endif // REMOTEPLAYER_HPP
