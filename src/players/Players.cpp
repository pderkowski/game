/* Copyright 2014 <Piotr Derkowski> */

#include <vector>
#include <string>
#include <memory>
#include "Player.hpp"
#include "Players.hpp"
#include "Coordinates.hpp"
#include "MapModel.hpp"
#include "units/Unit.hpp"
#include "Pathfinder.hpp"


namespace players {


Players::Players(int numberOfPlayers, const MapModel* model, const MapRenderer* renderer)
    : currentPlayer_(0), model_(model), renderer_(renderer), drawer_(this, renderer)
{
    for (int i = 1; i <= numberOfPlayers; ++i) {
        players_.push_back(Player(model_, "Player " + std::to_string(i)));
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
        getCurrentPlayer()->addUnit(
            units::Unit(selection_.getSource()->coords, units::Type::Phalanx, model_));

        drawer_.updateUnitLayer();
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

        Player::UnitControler unit = getCurrentPlayer()->getUnitAtCoords(source->coords);

        Pathfinder pathfinder(unit.get().getMovingCosts());
        if (pathfinder.doesPathExist(*source, *destination)) {
            std::vector<Tile> path = pathfinder.findPath(*source, *destination);

            if (isDestinationConfirmed(*destination)) {
                unit.move(path);

                selection_.clear();
                selection_.setSource(destination);

                drawer_.clearPathLayer();
                drawer_.updateFogLayer(getCurrentPlayer()->getFog());
                drawer_.updateUnitLayer();
            } else {
                selection_.setDestination(destination);

                drawer_.updatePathLayer(path);
            }
        }
    }

    drawer_.updateSelectionLayer(selection_);
}

std::shared_ptr<const Tile> Players::getClickedTile(const sf::Vector2i& clickedPoint) {
    IntIsoPoint clickedCoords = renderer_->getMapCoords(clickedPoint);
    return model_->getTile(clickedCoords);
}

bool Players::isDestinationConfirmed(const Tile& destination) const {
    return selection_.isDestinationSelected() && *(selection_.getDestination()) == destination;
}


}
