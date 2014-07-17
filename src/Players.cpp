/* Copyright 2014 <Piotr Derkowski> */

#include <vector>
#include <string>
#include "Player.hpp"
#include "Players.hpp"

Players::Players(int numberOfPlayers)
    : currentPlayer_(0)
{
    for (int i = 1; i <= numberOfPlayers; ++i) {
        players_.push_back(Player("Player " + std::to_string(i)));
    }
}

void Players::switchToNextPlayer() {
    currentPlayer_ = (currentPlayer_ + 1) % players_.size();
    std::cout << "Switching to " << players_[currentPlayer_].getName() << "\n";
}

Player* Players::getCurrentPlayer() {
    return &players_[currentPlayer_];
}
