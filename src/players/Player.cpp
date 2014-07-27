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

namespace players {


Player::Player(const MapModel* model, const std::string& name)
    : name_(name), fog_(model->getRowsNo(), model->getColumnsNo())
{ }

std::string Player::getName() const {
    return name_;
}

Fog Player::getFog() const {
    return fog_;
}

bool Player::hasUnitAtCoords(const IntRotPoint& coords) const {
    return std::any_of(units_.begin(), units_.end(), [&coords] (const units::Unit& unit) {
        return unit.getCoords() == coords;
    });
}

std::vector<units::Unit> Player::getAllUnits() const {
    return units_;
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


}  // namespace players
