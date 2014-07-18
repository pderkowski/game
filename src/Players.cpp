/* Copyright 2014 <Piotr Derkowski> */

#include <vector>
#include <string>
#include <memory>
#include "Player.hpp"
#include "Players.hpp"
#include "Coordinates.hpp"
#include "MapModel.hpp"

Players::Players(int numberOfPlayers, const MapModel* model, const MapRenderer* renderer)
    : currentPlayer_(0), model_(model), renderer_(renderer), drawer_(this, renderer)
{
    for (int i = 1; i <= numberOfPlayers; ++i) {
        players_.push_back(Player("Player " + std::to_string(i)));
    }
}

void Players::switchToNextPlayer() {
    currentPlayer_ = (currentPlayer_ + 1) % players_.size();

    selection_.clear();
    drawer_.updateSelectionLayer(selection_);

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

void Players::handleLeftClick(const sf::Event& e) {
    selection_.clear();

    IntIsoPoint clicked = renderer_->getMapCoords(sf::Vector2i(e.mouseButton.x, e.mouseButton.y));
    auto clickedTile = model_->getTile(clicked);

    selection_.setSource(clickedTile);
    // mapDrawer_.updatePathLayer(std::vector<Tile>());
    drawer_.updateSelectionLayer(selection_);
}
