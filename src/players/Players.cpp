/* Copyright 2014 <Piotr Derkowski> */

#include <vector>
#include "units/Unit.hpp"
#include "Player.hpp"
#include "Players.hpp"
#include "MapModel.hpp"
#include "MapRenderer.hpp"

namespace players {


Players::Players(int numberOfPlayers, const MapModel* model, const MapRenderer* renderer)
    : currentPlayer_(0)
{
    for (int i = 1; i <= numberOfPlayers; ++i) {
        players_.emplace_back(this, model, renderer);
    }

    getCurrentPlayer()->startTurn();
}

void Players::switchToNextPlayer() {
    getCurrentPlayer()->endTurn();
    currentPlayer_ = (currentPlayer_ + 1) % players_.size();
    getCurrentPlayer()->startTurn();
}

Player* Players::getCurrentPlayer() {
    return &players_[currentPlayer_];
}

const Player* Players::getCurrentPlayer() const {
    return &players_[currentPlayer_];
}

std::vector<units::Unit> Players::getVisibleUnits() const {
    std::vector<units::Unit> res;

    for (const Player& player : players_) {
        std::vector<units::Unit> units = player.getAllUnits();

        for (const auto& unit : units) {
            if (getCurrentPlayer()->doesSeeTile(unit.getPosition().coords)) {
                res.push_back(unit);
            }
        }
    }

    return res;
}

void Players::draw() const {
    getCurrentPlayer()->draw();
}


void Players::handleLeftClick(const sf::Event& e) {
    getCurrentPlayer()->handleLeftClick(e);
}

void Players::handleRightClick(const sf::Event& e) {
    getCurrentPlayer()->handleRightClick(e);
}

void Players::handleAPressed() {
    getCurrentPlayer()->handleAPressed();
}

void Players::handleFPressed() {
    getCurrentPlayer()->toggleFog();
}

void Players::handleDPressed() {
    getCurrentPlayer()->handleDPressed();
}


}
