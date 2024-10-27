// include/Juego.hpp
#ifndef JUEGO_HPP
#define JUEGO_HPP

#include "Tablero.hpp"
#include "LocalPlayer.hpp"
#include "RemotePlayer.hpp"
#include "TurnHandler.hpp"

class Juego {
public:
    // Parameterized constructor
    Juego(LocalPlayer* localPlayer, RemotePlayer* remotePlayer, bool isLocalPlayerFirst);

    // Destructor
    ~Juego();

    // Start the game loop
    void jugar();

private:
    LocalPlayer* localPlayer;       // Local player (server or client)
    RemotePlayer* remotePlayer;     // Remote player (client or server)
    Tablero tablero;                 // Game board
    bool isLocalPlayerFirst;         // Indicates if local player starts first
    TurnHandler* turnHandler;        // Manages turn alternation
};

#endif // JUEGO_HPP
