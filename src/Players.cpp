/* Copyright 2014 <Piotr Derkowski> */

#include <vector>
#include <string>
#include <memory>
#include "Player.hpp"
#include "Players.hpp"

Players::Players(int numberOfPlayers, const MapRenderer* renderer)
    : currentPlayer_(0), drawer_(this, renderer)
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

void Players::draw() const {
    drawer_.draw();
}

std::vector<const units::Unit*> Players::getAllUnits() const {
    std::vector<const units::Unit*> res;

    for (auto& player : players_) {
        auto playerUnits = player.getAllUnits();
        res.insert(res.end(), playerUnits.begin(), playerUnits.end());
    }

    return res;
}
