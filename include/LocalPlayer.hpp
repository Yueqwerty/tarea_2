// include/LocalPlayer.hpp
#ifndef LOCALPLAYER_HPP
#define LOCALPLAYER_HPP

#include "Tablero.hpp"

class LocalPlayer {
public:
    // Constructor
    LocalPlayer(char symbol);

    // Get the player's symbol
    char getSymbol() const;

    // Get move from the local player
    int getMove(const Tablero& tablero);
    
private:
    char symbol; // Player's symbol ('X' or 'O')
};

#endif // LOCALPLAYER_HPP
