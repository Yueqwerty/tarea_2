// src/TurnHandler.cpp
#include "TurnHandler.hpp"

// Constructor
TurnHandler::TurnHandler(LocalPlayer* localPlayer, RemotePlayer* remotePlayer, bool isLocalPlayerFirst)
    : localPlayer(localPlayer),
      remotePlayer(remotePlayer),
      isLocalPlayerFirst(isLocalPlayerFirst),
      isLocalPlayerTurnFlag(isLocalPlayerFirst) {}

// Get the player whose turn it is
LocalPlayer* TurnHandler::getCurrentLocalPlayer() {
    return isLocalPlayerTurnFlag ? localPlayer : nullptr;
}

RemotePlayer* TurnHandler::getCurrentRemotePlayer() {
    return isLocalPlayerTurnFlag ? nullptr : remotePlayer;
}

// Switch to the next turn
void TurnHandler::switchTurn() {
    isLocalPlayerTurnFlag = !isLocalPlayerTurnFlag;
}

// Check if it's the local player's turn
bool TurnHandler::isLocalPlayerTurn() const {
    return isLocalPlayerTurnFlag;
}
