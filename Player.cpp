#include "Player.h"
#include "RandomPlayer.h"
#include "SmartPlayer.h"
#include "MeatBoxPlayer.h"
#include <stdexcept>

Player::Player(char playerSide) {
    playerSide_ = playerSide;
}

char Player::getPlayerSide() const{
    return playerSide_;
}

Player* Player::makeNewPlayer(PlayerType playerType, char playerSide){
    // todo switch
    switch (playerType) {
        case (RANDOM_PLAYER):
            return new RandomPlayer(playerSide);
            case (SMART_PLAYER):
                return new SmartPlayer(playerSide);
                case (MEATBOX_PLAYER):
                    return new MeatBoxPlayer(playerSide);
                    default:
                        throw std::invalid_argument("Incorrect playerType argument");
    }
}
