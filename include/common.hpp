#ifndef COMMON_HPP
#define COMMON_HPP

#include <string>

// Network Constants
const int PORT = 54000; // Default port
const int BUFFER_SIZE = 1024;

// Messages
const std::string WELCOME_MSG = "Welcome to Connect Four!\n";
const std::string MOVE_PROMPT = "Your turn. Enter column number (1-7): ";
const std::string INVALID_MOVE = "Invalid move. Please try again.\n";
const std::string WIN_MSG = "Congratulations! You have won.\n";
const std::string LOSE_MSG = "You lost. The opponent has won.\n";
const std::string DRAW_MSG = "The game ended in a draw.\n";

// Forward Declaration
class Tablero;

// Abstract Player Class
class Player {
public:
    Player(char symbol) : symbol(symbol) {}
    virtual ~Player() = default;

    // Pure virtual function to get player's move
    virtual int getMove(const Tablero &tablero) = 0;

    // Get the player's symbol ('X' or 'O')
    char getSymbol() const { return symbol; }

protected:
    char symbol;
};

#endif // COMMON_HPP
