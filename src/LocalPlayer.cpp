// src/LocalPlayer.cpp
#include "LocalPlayer.hpp"
#include <iostream>
#include <limits>
#include <algorithm>

// Constructor
LocalPlayer::LocalPlayer(char symbol) : symbol(symbol) {}

// Get the player's symbol
char LocalPlayer::getSymbol() const {
    return symbol;
}

// Get move from the local player
int LocalPlayer::getMove(const Tablero& tablero) {
    int columna;
    while (true) {
        std::cin >> columna;

        // Validate input
        if (std::cin.fail() || columna < 1 || columna > 7) {
            std::cin.clear(); // Clear error flags
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Discard invalid input
            std::cout << "Invalid input. Please enter a number between 1 and 7: ";
            continue;
        }

        columna -= 1; // Adjust to 0-based index

        // Check if the column is full
        std::vector<int> validMoves = tablero.obtenerMovimientosValidos();
        if (std::find(validMoves.begin(), validMoves.end(), columna) == validMoves.end()) {
            std::cout << "Column " << (columna + 1) << " is full. Choose another column: ";
            continue;
        }

        return columna;
    }
}
