// include/TurnHandler.hpp
#ifndef TURNHANDLER_HPP
#define TURNHANDLER_HPP

#include "LocalPlayer.hpp"
#include "RemotePlayer.hpp"

class TurnHandler {
public:
    // Constructor
    TurnHandler(LocalPlayer* localPlayer, RemotePlayer* remotePlayer, bool isLocalPlayerFirst);
    
    // Get the player whose turn it is
    LocalPlayer* getCurrentLocalPlayer();
    RemotePlayer* getCurrentRemotePlayer();
    
    // Switch to the next turn
    void switchTurn();
    
    // Check if it's the local player's turn
    bool isLocalPlayerTurn() const;
    
private:
    LocalPlayer* localPlayer;
    RemotePlayer* remotePlayer;
    bool isLocalPlayerFirst;
    bool isLocalPlayerTurnFlag;
};

#endif // TURNHANDLER_HPP
