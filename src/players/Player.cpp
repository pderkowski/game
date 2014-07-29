/* Copyright 2014 <Piotr Derkowski> */

#include <iostream>
#include <map>
#include <utility>
#include <string>
#include <algorithm>
#include <stdexcept>
#include <functional>
#include <vector>
#include "Player.hpp"
#include "units/Unit.hpp"
#include "Coordinates.hpp"
#include "Tile.hpp"
#include "Fog.hpp"
#include "MapModel.hpp"
#include "Selection.hpp"
#include "Players.hpp"

namespace players {


Player::Player(const Players* players, const MapModel* model, const MapRenderer* renderer)
    : players_(players),
    model_(model),
    renderer_(renderer),
    fog_(model->getRowsNo(), model->getColumnsNo()),
    hasTurn_(false),
    isFogToggledOn_(true),
    drawer_(this, renderer)
{ }

Player::Player(const Player& other)
    : players_(other.players_),
    model_(other.model_),
    renderer_(other.renderer_),
    units_(other.units_),
    movementPoints_(other.movementPoints_),
    fog_(other.fog_),
    selection_(other.selection_),
    hasTurn_(other.hasTurn_),
    isFogToggledOn_(other.isFogToggledOn_),
    drawer_(other.drawer_)
{
    drawer_.setPointer(this);
}

void Player::draw() const {
    drawer_.draw();
}

bool Player::hasUnitAtCoords(const IntRotPoint& coords) const {
    return std::any_of(units_.begin(), units_.end(), [&coords] (const units::Unit& unit) {
        return unit.getCoords() == coords;
    });
}

void Player::addUnit(const units::Unit& unit) {
    units_.push_back(unit);

    fog_.addVisible(getSurroundingTiles(unit));
}

UnitController Player::getUnitAtCoords(const IntRotPoint& coords) {
    auto unitIt = std::find_if(units_.begin(), units_.end(), [&coords] (const units::Unit& unit) {
        return unit.getCoords() == coords;
    });

    if (unitIt != units_.end()) {
        return UnitController(&(*unitIt), this);
    } else {
        throw std::logic_error("There is no unit at the requested coords.");
    }
}

units::Unit Player::getUnitAtCoords(const IntRotPoint& coords) const {
    auto unitIt = std::find_if(units_.begin(), units_.end(), [&coords] (const units::Unit& unit) {
        return unit.getCoords() == coords;
    });

    if (unitIt != units_.end()) {
        return *unitIt;
    } else {
        throw std::logic_error("There is no unit at the requested coords.");
    }
}

std::vector<units::Unit> Player::getAllUnits() const {
    return units_;
}

void Player::startTurn() {
    hasTurn_ = true;
    resetMovementPoints();

    drawer_.updateUnitLayer(players_->getVisibleUnits());
}

void Player::endTurn() {
    hasTurn_ = false;
}

bool Player::hasTurn() const {
    return hasTurn_;
}

bool Player::doesSeeTile(const IntRotPoint& coords) const {
    if (isFogToggledOn_) {
        IntIsoPoint isoCoords(coords.toIsometric());
        return fog_(isoCoords.y, isoCoords.x) == TileVisibility::VisibleKnown;
    } else {
        return true;
    }
}

bool Player::doesKnowTile(const IntRotPoint& coords) const {
    if (isFogToggledOn_) {
        IntIsoPoint isoCoords(coords.toIsometric());
        return (fog_(isoCoords.y, isoCoords.x) == TileVisibility::VisibleKnown)
            || (fog_(isoCoords.y, isoCoords.x) == TileVisibility::UnvisibleKnown);
    } else {
        return true;
    }
}

int Player::getMovementPointsLeft(const units::Unit& unit) const {
    if (movementPoints_.find(unit.getId()) != movementPoints_.end()) {
        return movementPoints_.at(unit.getId());
    } else {
        return 0;
    }
}

void Player::setMovementPointsLeft(const units::Unit& unit, int pointsLeft) {
    if (movementPoints_.find(unit.getId()) != movementPoints_.end()) {
        movementPoints_.at(unit.getId()) = pointsLeft;
    }
}

void Player::resetMovementPoints() {
    movementPoints_.clear();

    for (auto& unit : units_) {
        movementPoints_.insert(std::make_pair(unit.getId(), 2));
    }
}

std::vector<const Tile*> Player::getSurroundingTiles(const units::Unit& unit) const {
    Tile position = unit.getPosition();
    return position.getTilesInRadius(2);
}

void Player::handleLeftClick(const sf::Event& e) {
    selection_.clear();
    selection_.setSource(getClickedTile(sf::Vector2i(e.mouseButton.x, e.mouseButton.y)));

    drawer_.clearPathLayer();
    drawer_.updateSelectionLayer();
}

void Player::handleAPressed() {
    if (selection_.isSourceSelected()) {
        if (selection_.getSource().type == tileenums::Type::Water) {
            addUnit(units::Unit(selection_.getSource().coords, units::Type::Trireme, model_));
        } else {
            addUnit(units::Unit(selection_.getSource().coords, units::Type::Phalanx, model_));
        }

        drawer_.updateUnitLayer(players_->getVisibleUnits());
        drawer_.updateFogLayer();
    }
}

void Player::handleRightClick(const sf::Event& e) {
    if (selection_.isSourceSelected() && hasUnitAtCoords(selection_.getSource().coords)) {
        auto source = selection_.getSource();
        auto destination = getClickedTile(sf::Vector2i(e.mouseButton.x, e.mouseButton.y));

        UnitController unit = getUnitAtCoords(source.coords);
        if (unit.canMoveTo(destination)) {
            if (selection_.isDestinationConfirmed(destination)) {
                unit.moveTo(destination);

                selection_.setSource(unit.get().getPosition());

                drawer_.updateFogLayer();
                drawer_.updateUnitLayer(players_->getVisibleUnits());
            } else {
                selection_.setDestination(destination);
            }

            drawer_.updatePathLayer(unit.getPathTo(destination));
        }
    }

    drawer_.updateSelectionLayer();
}

void Player::handleDPressed() {
    if (selection_.isSourceSelected() && hasUnitAtCoords(selection_.getSource().coords)) {
        auto source = selection_.getSource();

        UnitController unit = getUnitAtCoords(source.coords);
        unit.destroyUnit();

        drawer_.updateFogLayer();
        drawer_.updateUnitLayer(players_->getVisibleUnits());
        selection_.clear();
        drawer_.updateSelectionLayer();
        drawer_.clearPathLayer();
    }
}

const Tile& Player::getClickedTile(const sf::Vector2i& clickedPoint) const {
    IntIsoPoint clickedCoords = renderer_->getMapCoords(clickedPoint);
    return model_->getTile(clickedCoords);
}

void Player::toggleFog() {
    isFogToggledOn_ = !isFogToggledOn_;

    drawer_.updateUnitLayer(players_->getVisibleUnits());
}


}  // namespace players
