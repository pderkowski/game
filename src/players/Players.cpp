/* Copyright 2014 <Piotr Derkowski> */

#include <vector>
#include <string>
#include <memory>
#include "Player.hpp"
#include "Players.hpp"
#include "Coordinates.hpp"
#include "MapModel.hpp"
#include "units/Unit.hpp"


namespace players {


Players::Players(int numberOfPlayers, const MapModel* model, const MapRenderer* renderer)
    : currentPlayer_(0), model_(model), renderer_(renderer), drawer_(this, renderer)
{
    for (int i = 1; i <= numberOfPlayers; ++i) {
        players_.push_back(Player(model_, "Player " + std::to_string(i)));
    }

    drawer_.updateFogLayer(getCurrentPlayer()->getFog());
}

void Players::switchToNextPlayer() {
    currentPlayer_ = (currentPlayer_ + 1) % players_.size();

    std::cout << "Switching to " << players_[currentPlayer_].getName() << "\n";

    selection_.clear();
    drawer_.updateSelectionLayer(selection_);
    drawer_.clearPathLayer();
    drawer_.updateUnitLayer(getCurrentPlayer()->getFog());
    drawer_.updateFogLayer(getCurrentPlayer()->getFog());
}

Player* Players::getCurrentPlayer() {
    return &players_[currentPlayer_];
}

void Players::draw() const {
    drawer_.draw();
}

std::vector<units::Unit> Players::getAllUnits() const {
    std::vector<units::Unit> res;

    for (auto& player : players_) {
        auto playerUnits = player.getAllUnits();
        res.insert(res.end(), playerUnits.begin(), playerUnits.end());
    }

    return res;
}

void Players::handleLeftClick(const sf::Event& e) {
    selection_.clear();
    selection_.setSource(getClickedTile(sf::Vector2i(e.mouseButton.x, e.mouseButton.y)));

    drawer_.clearPathLayer();
    drawer_.updateSelectionLayer(selection_);
}

void Players::handleAPressed() {
    if (selection_.isSourceSelected()) {
        if (selection_.getSource().type == tileenums::Type::Water) {
            getCurrentPlayer()->addUnit(
                units::Unit(selection_.getSource().coords, units::Type::Trireme, model_));
        } else {
            getCurrentPlayer()->addUnit(
                units::Unit(selection_.getSource().coords, units::Type::Phalanx, model_));
        }

        drawer_.updateUnitLayer(getCurrentPlayer()->getFog());
        drawer_.updateFogLayer(getCurrentPlayer()->getFog());
    }
}

void Players::handleFPressed() {
    drawer_.toggleFog();
}

void Players::handleRightClick(const sf::Event& e) {
    if (selection_.isUnitSelected(getCurrentPlayer())) {
        auto source = selection_.getSource();
        auto destination = getClickedTile(sf::Vector2i(e.mouseButton.x, e.mouseButton.y));

        Player::UnitControler unit = getCurrentPlayer()->getUnitAtCoords(source.coords);
        if (unit.canMoveTo(destination)) {
            if (isDestinationConfirmed(destination)) {
                unit.moveTo(destination);

                selection_.clear();
                selection_.setSource(destination);

                drawer_.clearPathLayer();
                drawer_.updateFogLayer(getCurrentPlayer()->getFog());
                drawer_.updateUnitLayer(getCurrentPlayer()->getFog());
            } else {
                selection_.setDestination(destination);

                drawer_.updatePathLayer(unit.getPathTo(destination));
            }
        }
    }

    drawer_.updateSelectionLayer(selection_);
}

void Players::handleDPressed() {
    if (selection_.isUnitSelected(getCurrentPlayer())) {
        auto source = selection_.getSource();

        Player::UnitControler unit = getCurrentPlayer()->getUnitAtCoords(source.coords);
        unit.destroyUnit();

        drawer_.updateFogLayer(getCurrentPlayer()->getFog());
        drawer_.updateUnitLayer(getCurrentPlayer()->getFog());
        selection_.clear();
        drawer_.updateSelectionLayer(selection_);
        drawer_.clearPathLayer();
    }
}

const Tile& Players::getClickedTile(const sf::Vector2i& clickedPoint) const {
    IntIsoPoint clickedCoords = renderer_->getMapCoords(clickedPoint);
    return model_->getTile(clickedCoords);
}

bool Players::isDestinationConfirmed(const Tile& destination) const {
    return selection_.isDestinationSelected() && selection_.getDestination() == destination;
}


}
