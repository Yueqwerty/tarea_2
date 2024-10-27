// src/Juego.cpp
#include "Juego.hpp"
#include "RemotePlayer.hpp"
#include "LocalPlayer.hpp"
#include "TurnHandler.hpp"
#include <iostream>
#include <exception>

// Parameterized constructor
Juego::Juego(LocalPlayer* localPlayer, RemotePlayer* remotePlayer, bool isLocalPlayerFirst)
    : localPlayer(localPlayer),
      remotePlayer(remotePlayer),
      tablero(),
      isLocalPlayerFirst(isLocalPlayerFirst),
      turnHandler(new TurnHandler(localPlayer, remotePlayer, isLocalPlayerFirst)) {
    // No additional initialization required
}

// Destructor
Juego::~Juego() {
    delete turnHandler;
}

// Start the game loop
void Juego::jugar() {
    if (!localPlayer || !remotePlayer || !turnHandler) {
        std::cerr << "Juego::jugar: Players or TurnHandler not initialized.\n";
        return;
    }

    bool juegoTerminado = false;

    while (!juegoTerminado) {
        tablero.mostrar();  // Display the current state of the board

        if (turnHandler->isLocalPlayerTurn()) {
            // Local player's turn
            std::cout << "Your turn. Enter column number (1-7): ";
            int columna = localPlayer->getMove(tablero);  // Get move from LocalPlayer

            if (!tablero.colocarFicha(columna, localPlayer->getSymbol())) {
                std::cout << "Invalid move. Try again.\n";
                continue; // Retry the same player's turn
            }

            // Send move to RemotePlayer
            try {
                remotePlayer->sendMove(columna);
            }
            catch (const std::exception& e) {
                std::cerr << "Juego::jugar: Error sending move to RemotePlayer: " << e.what() << "\n";
                return;
            }
        }
        else {
            // Remote player's turn
            std::cout << "Waiting for remote player's move...\n";
            int columna;
            try {
                columna = remotePlayer->getMove(tablero);  // Get move from RemotePlayer
            }
            catch (const std::exception& e) {
                std::cerr << "Juego::jugar: Error receiving move from RemotePlayer: " << e.what() << "\n";
                return;
            }

            if (!tablero.colocarFicha(columna, remotePlayer->getSymbol())) {
                std::cout << "Received invalid move. Ending game.\n";
                juegoTerminado = true;
                break;
            }
        }

        // Check for a win or draw after the move
        char simboloActual = turnHandler->isLocalPlayerTurn() ? localPlayer->getSymbol() : remotePlayer->getSymbol();
        if (tablero.verificarVictoria(simboloActual)) {
            tablero.mostrar();
            std::cout << (turnHandler->isLocalPlayerTurn() ? "You win!" : "Remote player wins!") << "\n";
            juegoTerminado = true;
        }
        else if (tablero.estaLleno()) {
            tablero.mostrar();
            std::cout << "The game ended in a draw.\n";
            juegoTerminado = true;
        }

        // Switch turns
        turnHandler->switchTurn();
    }
}
