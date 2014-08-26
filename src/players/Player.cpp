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
#include "units/UnitFactory.hpp"
#include "Coordinates.hpp"
#include "Tile.hpp"
#include "Fog.hpp"
#include "MapModel.hpp"
#include "Selection.hpp"
#include "MiscellaneousEnums.hpp"


namespace players {


Player::Player(miscellaneous::Flag flag, const MapModel* model)
    : flag_(flag), fog_(model->getRowsNo(), model->getColumnsNo()), model_(model)
{ }

bool Player::isUnitSelected() const {
    if (selection_.isSourceSelected()) {
        const IntRotPoint coords = selection_.getSource().coords;

        return std::any_of(units_.begin(), units_.end(), [&coords] (const units::Unit& unit) {
            return unit.getCoords() == coords;
        });
    } else {
        return false;
    }
}

void Player::addUnit(const units::Unit& unit) {
    units_.push_back(unit);

    fog_.addVisible(getSurroundingTiles(unit));
}

UnitController Player::getSelectedUnit() {
    const IntRotPoint coords = selection_.getSource().coords;

    auto unitIt = std::find_if(units_.begin(), units_.end(), [&coords] (const units::Unit& unit) {
        return unit.getCoords() == coords;
    });

    if (unitIt != units_.end()) {
        return UnitController(&(*unitIt), this);
    } else {
        throw std::logic_error("There is no unit at the requested coords.");
    }
}

units::Unit Player::getSelectedUnit() const {
    const IntRotPoint coords = selection_.getSource().coords;

    auto unitIt = std::find_if(units_.begin(), units_.end(), [&coords] (const units::Unit& unit) {
        return unit.getCoords() == coords;
    });

    if (unitIt != units_.end()) {
        return *unitIt;
    } else {
        throw std::logic_error("There is no unit at the requested coords.");
    }
}

bool Player::hasUnitAtCoords(const IntRotPoint& coords) const {
    return std::any_of(units_.begin(), units_.end(), [&coords] (const units::Unit& unit) {
        return unit.getCoords() == coords;
    });
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

std::vector<units::Unit> Player::getUnits() const {
    return units_;
}

Fog Player::getFog() const {
    return fog_;
}

Selection Player::getSelection() const {
    return selection_;
}

miscellaneous::Flag Player::getFlag() const {
    return flag_;
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

void Player::setModel(const MapModel* model) {
    model_ = model;
    units_.clear();
    fog_.clear();
    selection_.clear();
}

void Player::resetMoves() {
    for (auto& unit : units_) {
        unit.resetMoves();
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
            addUnit(units::UnitFactory::createTrireme(selection_.getSource().coords, model_, this));
        } else {
            addUnit(units::UnitFactory::createPhalanx(selection_.getSource().coords, model_, this));
        }
    }
}

void Player::handleRightClick(const Tile& clickedTile) {
    if (isUnitSelected()) {
        auto destination = clickedTile;

        UnitController unit = getSelectedUnit();
        if (unit.canMoveTo(destination)) {
            if (selection_.isDestinationConfirmed(destination)) {
                unit.moveTo(destination);

                selection_.setSource(unit.get()->getPosition());
                selection_.setPath(unit.getPathTo(destination));
            } else {
                selection_.setDestination(destination);
                selection_.setPath(unit.getPathTo(destination));
            }
        }
    }
}

void Player::handleDPressed() {
    if (isUnitSelected()) {
        UnitController unit = getSelectedUnit();
        unit.destroyUnit();

        selection_.clear();
    }
}

void Player::handleFPressed() {
    fog_.toggle();
}


}  // namespace players
