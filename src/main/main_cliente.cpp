// src/main/main_cliente.cpp
#include "../include/Cliente.hpp"
#include <iostream>
#include <cstdlib>
#include <string>

int main(int argc, char* argv[]) {
    if (argc != 3) {
        std::cerr << "Usage: ./cliente <server_ip> <port>\n";
        return EXIT_FAILURE;
    }

    std::string server_ip = argv[1];
    int port = std::stoi(argv[2]);

    try {
        // Initialize the client with the server IP and port
        Cliente cliente(server_ip, port);

        // Start the client and initiate the game
        cliente.iniciar();
    }
    catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << "\n";
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}
