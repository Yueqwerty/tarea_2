// include/Tablero.hpp
#ifndef TABLERO_HPP
#define TABLERO_HPP

#include <vector>

class Tablero {
public:
    static const int FILAS = 6;
    static const int COLUMNAS = 7;

    Tablero(); // Constructor

    // Display the board
    void mostrar() const;

    // Place a piece in the specified column
    bool colocarFicha(int columna, char simbolo);

    // Check for victory
    bool verificarVictoria(char simbolo) const;

    // Check if the board is full
    bool estaLleno() const;

    // Get valid moves
    std::vector<int> obtenerMovimientosValidos() const;

private:
    std::vector<std::vector<char>> grid; // 2D grid representing the board
};

#endif // TABLERO_HPP
