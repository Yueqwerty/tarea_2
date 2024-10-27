// src/Tablero.cpp
#include "Tablero.hpp"
#include <iostream>

// Constructor
Tablero::Tablero() : grid(FILAS, std::vector<char>(COLUMNAS, ' ')) {}

// Display the board
void Tablero::mostrar() const {
    std::cout << "\n";
    for (const auto& fila : grid) {
        std::cout << "|";
        for (const auto& celda : fila) {
            std::cout << " " << (celda == ' ' ? ' ' : celda) << " |";
        }
        std::cout << "\n";
    }
    std::cout << " ";
    for (int i = 1; i <= COLUMNAS; ++i) {
        std::cout << " " << i << "  ";
    }
    std::cout << "\n\n";
}

// Place a piece in the specified column
bool Tablero::colocarFicha(int columna, char simbolo) {
    if (columna < 0 || columna >= COLUMNAS) {
        return false;
    }

    for (int fila = FILAS - 1; fila >= 0; --fila) {
        if (grid[fila][columna] == ' ') {
            grid[fila][columna] = simbolo;
            return true;
        }
    }
    return false; // Column is full
}

// Check for victory
bool Tablero::verificarVictoria(char simbolo) const {
    // Check horizontal
    for (int fila = 0; fila < FILAS; ++fila) {
        for (int col = 0; col <= COLUMNAS - 4; ++col) {
            if (grid[fila][col] == simbolo &&
                grid[fila][col + 1] == simbolo &&
                grid[fila][col + 2] == simbolo &&
                grid[fila][col + 3] == simbolo) {
                return true;
            }
        }
    }

    // Check vertical
    for (int col = 0; col < COLUMNAS; ++col) {
        for (int fila = 0; fila <= FILAS - 4; ++fila) {
            if (grid[fila][col] == simbolo &&
                grid[fila + 1][col] == simbolo &&
                grid[fila + 2][col] == simbolo &&
                grid[fila + 3][col] == simbolo) {
                return true;
            }
        }
    }

    // Check diagonal (bottom-left to top-right)
    for (int fila = 3; fila < FILAS; ++fila) {
        for (int col = 0; col <= COLUMNAS - 4; ++col) {
            if (grid[fila][col] == simbolo &&
                grid[fila - 1][col + 1] == simbolo &&
                grid[fila - 2][col + 2] == simbolo &&
                grid[fila - 3][col + 3] == simbolo) {
                return true;
            }
        }
    }

    // Check diagonal (top-left to bottom-right)
    for (int fila = 0; fila <= FILAS - 4; ++fila) {
        for (int col = 0; col <= COLUMNAS - 4; ++col) {
            if (grid[fila][col] == simbolo &&
                grid[fila + 1][col + 1] == simbolo &&
                grid[fila + 2][col + 2] == simbolo &&
                grid[fila + 3][col + 3] == simbolo) {
                return true;
            }
        }
    }

    return false;
}

// Check if the board is full
bool Tablero::estaLleno() const {
    for (const auto& celda : grid[0]) {
        if (celda == ' ') {
            return false;
        }
    }
    return true;
}

// Get valid moves
std::vector<int> Tablero::obtenerMovimientosValidos() const {
    std::vector<int> validMoves;
    for (int columna = 0; columna < COLUMNAS; ++columna) {
        if (grid[0][columna] == ' ') {
            validMoves.push_back(columna);
        }
    }
    return validMoves;
}
