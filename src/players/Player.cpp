/* Copyright 2014 <Piotr Derkowski> */

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


namespace players {


Player::Player(const MapModel* model)
    : model_(model), fog_(model->getRowsNo(), model->getColumnsNo())
{ }

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

std::vector<units::Unit> Player::getUnits() const {
    return units_;
}

Fog Player::getFog() const {
    return fog_;
}

Selection Player::getSelection() const {
    return selection_;
}


bool Player::doesSeeTile(const IntRotPoint& coords) const {
    IntIsoPoint isoCoords(coords.toIsometric());
    return fog_(isoCoords.y, isoCoords.x) == TileVisibility::VisibleKnown;
}

bool Player::doesKnowTile(const IntRotPoint& coords) const {
    IntIsoPoint isoCoords(coords.toIsometric());
    return (fog_(isoCoords.y, isoCoords.x) == TileVisibility::VisibleKnown)
        || (fog_(isoCoords.y, isoCoords.x) == TileVisibility::UnvisibleKnown);
}

void Player::resetMoves() {
    for (auto& unit : units_) {
        unit.setMovesLeft(2);
    }
}

std::vector<const Tile*> Player::getSurroundingTiles(const units::Unit& unit) const {
    Tile position = unit.getPosition();
    return position.getTilesInRadius(2);
}

void Player::handleLeftClick(const Tile& clickedTile) {
    selection_.clear();
    selection_.setSource(clickedTile);
}

void Player::handleAPressed() {
    if (selection_.isSourceSelected()) {
        if (selection_.getSource().type == tileenums::Type::Water) {
            addUnit(units::Unit(selection_.getSource().coords, units::Type::Trireme, model_));
        } else {
            addUnit(units::Unit(selection_.getSource().coords, units::Type::Phalanx, model_));
        }
    }
}

void Player::handleRightClick(const Tile& clickedTile) {
    if (selection_.isSourceSelected() && hasUnitAtCoords(selection_.getSource().coords)) {
        auto source = selection_.getSource();
        auto destination = clickedTile;

        UnitController unit = getUnitAtCoords(source.coords);
        if (unit.canMoveTo(destination)) {
            if (selection_.isDestinationConfirmed(destination)) {
                unit.moveTo(destination);

                selection_.setSource(unit.get().getPosition());
                selection_.setPath(unit.getPathTo(destination));
            } else {
                selection_.setDestination(destination);
                selection_.setPath(unit.getPathTo(destination));
            }
        }
    }
}

void Player::handleDPressed() {
    if (selection_.isSourceSelected() && hasUnitAtCoords(selection_.getSource().coords)) {
        auto source = selection_.getSource();

        UnitController unit = getUnitAtCoords(source.coords);
        unit.destroyUnit();

        selection_.clear();
    }
}

void Player::handleFPressed() {
    fog_.toggle();
}


}  // namespace players
