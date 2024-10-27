// src/main/main_servidor.cpp
#include "../include/Servidor.hpp"
#include <iostream>
#include <cstdlib>

int main(int argc, char* argv[]) {
    if (argc != 2) {
        std::cerr << "Usage: ./servidor <port>\n";
        return EXIT_FAILURE;
    }

    int port = std::stoi(argv[1]);

    try {
        // Initialize the server with the specified port
        Servidor servidor(port);

        // Start the server and initiate the game
        servidor.iniciar();
    }
    catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << "\n";
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}
