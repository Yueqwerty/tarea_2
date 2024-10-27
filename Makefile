# Makefile

# Compiler
CXX = g++

# Compiler Flags
CXXFLAGS = -std=c++17 -Wall -Wextra -pthread

# Include Directories
INCLUDES = -Iinclude

# Source Files
SRCS_JUEGO = src/Juego.cpp
SRCS_LOCALPLAYER = src/LocalPlayer.cpp
SRCS_REMOTEPLAYER = src/RemotePlayer.cpp
SRCS_TABLERO = src/Tablero.cpp
SRCS_TURNHANDLER = src/TurnHandler.cpp

# Main Applications
SRCS_SERVIDOR_MAIN = src/main/main_servidor.cpp
SRCS_CLIENTE_MAIN = src/main/main_cliente.cpp

# Servidor Source Files
SRCS_SERVIDOR = src/Servidor.cpp $(SRCS_JUEGO) $(SRCS_LOCALPLAYER) $(SRCS_REMOTEPLAYER) $(SRCS_TABLERO) $(SRCS_TURNHANDLER) $(SRCS_SERVIDOR_MAIN)

# Cliente Source Files
SRCS_CLIENTE = src/Cliente.cpp $(SRCS_JUEGO) $(SRCS_LOCALPLAYER) $(SRCS_REMOTEPLAYER) $(SRCS_TABLERO) $(SRCS_TURNHANDLER) $(SRCS_CLIENTE_MAIN)

# Targets
TARGETS = bin/servidor bin/cliente

# Default Target
all: $(TARGETS)

# Server Build Rule
bin/servidor: $(SRCS_SERVIDOR)
	$(CXX) $(CXXFLAGS) $(INCLUDES) $^ -o $@

# Client Build Rule
bin/cliente: $(SRCS_CLIENTE)
	$(CXX) $(CXXFLAGS) $(INCLUDES) $^ -o $@

# Clean Rule
clean:
	rm -f bin/servidor bin/cliente

# Phony Targets
.PHONY: all clean
