/* Copyright 2014 <Piotr Derkowski> */

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

Player::UnitControler Player::getUnitAtCoords(const IntRotPoint& coords) {
    auto unitIt = std::find_if(units_.begin(), units_.end(), [&coords] (const units::Unit& unit) {
        return unit.getCoords() == coords;
    });

    if (unitIt != units_.end()) {
        return UnitControler(&(*unitIt), this);
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

std::vector<Tile> Player::getSurroundingTiles(const units::Unit& unit) const {
    std::shared_ptr<const Tile> position = unit.getPosition();
    std::vector<std::shared_ptr<const Tile>> neighbors = position->getNeighbors();

    std::vector<Tile> res;

    res.push_back(*position);
    for (auto neighbor : neighbors) {
        res.push_back(*neighbor);
    }

    return res;
}


Player::UnitControler::UnitControler(units::Unit* unit, Player* player)
    : unit_(unit), player_(player)
{ }

units::Unit Player::UnitControler::get() const {
    return *unit_;
}

void Player::UnitControler::move(const std::vector<Tile>& path) {
    if (path.empty() || path[0] != *(unit_->getPosition()))
        throw std::logic_error("The unit is not at the beginning of the path.");

    player_->fog_.removeVisible(player_->getSurroundingTiles(*unit_));

    for (size_t i = 0; i + 1 < path.size(); ++i) {
        auto direction = path[i].getDirection(path[i + 1]);
        unit_->moveTo(direction);

        player_->fog_.addKnown(player_->getSurroundingTiles(*unit_));
    }

    player_->fog_.addVisible(player_->getSurroundingTiles(*unit_));
}


}  // namespace players
