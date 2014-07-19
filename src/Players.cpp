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
    selection_.setSource(getClickedTile(sf::Vector2i(e.mouseButton.x, e.mouseButton.y)));

    drawer_.updatePathLayer(std::vector<Tile>());
    drawer_.updateSelectionLayer(selection_);
}

void Players::handleAPressed() {
    if (selection_.isSourceSelected()) {
        getCurrentPlayer()->addUnit(
            units::Unit(selection_.getSource()->coords, units::Type::Phalanx, model_));

        drawer_.updateUnitLayer();
    }
}

void Players::handleRightClick(const sf::Event& e) {
    if (selection_.isUnitSelected(getCurrentPlayer())) {
        auto source = selection_.getSource();
        auto destination = getClickedTile(sf::Vector2i(e.mouseButton.x, e.mouseButton.y));

        units::Unit* selectedUnit = getCurrentPlayer()->getUnitAtCoords(source->coords);

        Pathfinder pathfinder(selectedUnit->getMovingCosts());
        if (pathfinder.doesPathExist(*source, *destination)) {
            std::vector<Tile> path = pathfinder.findPath(*source, *destination);

            if (isDestinationConfirmed(*destination)) {
                moveUnit(selectedUnit, path);

                selection_.clear();
                selection_.setSource(destination);

                path.clear();
            } else {
                selection_.setDestination(destination);
            }

            drawer_.updatePathLayer(path);
        }
    }

    drawer_.updateSelectionLayer(selection_);
}

void Players::moveUnit(units::Unit* unit, const std::vector<Tile>& path) {
    for (size_t i = 0; i + 1 < path.size(); ++i) {
        auto direction = path[i].getDirection(path[i + 1]);
        unit->moveTo(direction);
    }

    drawer_.updateUnitLayer();
}

std::shared_ptr<const Tile> Players::getClickedTile(const sf::Vector2i& clickedPoint) {
    IntIsoPoint clickedCoords = renderer_->getMapCoords(clickedPoint);
    return model_->getTile(clickedCoords);
}

bool Players::isDestinationConfirmed(const Tile& destination) const {
    return selection_.isDestinationSelected() && *(selection_.getDestination()) == destination;
}
