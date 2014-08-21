/* Copyright 2014 <Piotr Derkowski> */

#include <vector>
#include "units/Unit.hpp"
#include "Player.hpp"
#include "Players.hpp"
#include "PlayersDrawer.hpp"
#include "MapModel.hpp"
#include "MapRenderer.hpp"

namespace players {


Players::Players(int numberOfPlayers, const MapModel* model, const MapRenderer* renderer)
    : currentPlayer_(0), model_(model), renderer_(renderer), drawer_(renderer)
{
    for (int i = 1; i <= numberOfPlayers; ++i) {
        players_.emplace_back(this, model);
    }

    updateAllLayers();
}

void Players::switchToNextPlayer() {
    currentPlayer_ = (currentPlayer_ + 1) % players_.size();
    getCurrentPlayer()->resetMovementPoints();

    updateAllLayers();
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
        std::vector<units::Unit> units = player.getUnits();

        for (const auto& unit : units) {
            if (getCurrentPlayer()->doesSeeTile(unit.getPosition().coords)) {
                res.push_back(unit);
            }
        }
    }

    return res;
}

void Players::draw() const {
    drawer_.draw();
}


void Players::handleLeftClick(const sf::Event& e) {
    getCurrentPlayer()->handleLeftClick(getClickedTile(sf::Vector2i(e.mouseButton.x, e.mouseButton.y)));

    drawer_.updatePathLayer(getCurrentPlayer()->getSelection());
    drawer_.updateSelectionLayer(getCurrentPlayer()->getSelection());
}

void Players::handleRightClick(const sf::Event& e) {
    getCurrentPlayer()->handleRightClick(getClickedTile(sf::Vector2i(e.mouseButton.x, e.mouseButton.y)));

    updateAllLayers();
}

void Players::handleAPressed() {
    getCurrentPlayer()->handleAPressed();

    drawer_.updateUnitLayer(getVisibleUnits());
    drawer_.updateFogLayer(getCurrentPlayer()->getFog());
}

void Players::handleFPressed() {
    getCurrentPlayer()->handleFPressed();

    drawer_.updateFogLayer(getCurrentPlayer()->getFog());
    drawer_.updateUnitLayer(getVisibleUnits());
}

void Players::handleDPressed() {
    getCurrentPlayer()->handleDPressed();

    updateAllLayers();
}

const Tile& Players::getClickedTile(const sf::Vector2i& clickedPoint) const {
    IntIsoPoint clickedCoords = renderer_->getMapCoords(clickedPoint);
    return model_->getTile(clickedCoords);
}

void Players::updateAllLayers() {
    drawer_.updateFogLayer(getCurrentPlayer()->getFog());
    drawer_.updateUnitLayer(getVisibleUnits());
    drawer_.updateSelectionLayer(getCurrentPlayer()->getSelection());
    drawer_.updatePathLayer(getCurrentPlayer()->getSelection());
}


}
