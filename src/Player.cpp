/* Copyright 2014 <Piotr Derkowski> */

#include <string>
#include <algorithm>
#include <stdexcept>
#include <functional>
#include "Player.hpp"
#include "units/Unit.hpp"
#include "Coordinates.hpp"

Player::Player()
    : name_("")
{ }

Player::Player(const std::string& name)
    : name_(name)
{ }

std::string Player::getName() const {
    return name_;
}

bool Player::hasUnitAtCoords(const IntRotPoint& coords) const {
    return std::any_of(units_.begin(), units_.end(), [&coords] (const units::Unit& unit) {
        return unit.getCoords() == coords;
    });
}

const units::Unit* Player::getUnitAtCoords(const IntRotPoint& coords) const {
    auto unitIt = std::find_if(units_.begin(), units_.end(), [&coords] (const units::Unit& unit) {
        return unit.getCoords() == coords;
    });

    if (unitIt != units_.end()) {
        return &(*unitIt);
    } else {
        throw std::logic_error("There is no unit at the requested coords.");
    }
}

units::Unit* Player::getUnitAtCoords(const IntRotPoint& coords) {
    return const_cast<units::Unit*>(static_cast<const Player&>(*this).getUnitAtCoords(coords));
}

std::vector<const units::Unit*> Player::getAllUnits() const {
    std::vector<const units::Unit*> res;

    for (auto& unit : units_) {
        res.push_back(&unit);
    }

    return res;
}

void Player::addUnit(const units::Unit& unit) {
    units_.push_back(unit);
}
