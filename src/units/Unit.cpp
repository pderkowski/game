/* Copyright 2014 <Piotr Derkowski> */

#include <string>
#include <algorithm>
#include <stdexcept>
#include "Unit.hpp"
#include "Tile.hpp"
#include "Coordinates.hpp"
#include "TileEnums.hpp"
#include "MapModel.hpp"
#include "players/Player.hpp"

namespace units {


Unit::Unit(const IntRotPoint& coords,
    const UnitProperties& properties,
    const MapModel* model,
    const players::Player* owner)
        : coords_(coords), properties_(properties), model_(model), owner_(owner)
{ }

void Unit::resetMoves() {
    properties_.movesLeft = properties_.baseMoves;
}

void Unit::setMovesLeft(int movesLeft) {
    properties_.movesLeft = std::max(movesLeft, 0);
}

void Unit::setHpLeft(int hpLeft) {
    properties_.hpLeft = std::max(hpLeft, 0);
}

std::string Unit::getName() const {
    return properties_.name;
}

Type Unit::getType() const {
    return properties_.type;
}

Tile Unit::getPosition() const {
    if (model_ != nullptr)
        return model_->getTile(IntIsoPoint(coords_.toIsometric()));
    else
        throw std::runtime_error("No model set in unit.");
}

IntRotPoint Unit::getCoords() const {
    return coords_;
}

const players::Player* Unit::getOwner() const {
    return owner_;
}

int Unit::getMovesLeft() const {
    return properties_.movesLeft;
}

int Unit::getHpLeft() const {
    return properties_.hpLeft;
}

bool Unit::canMoveTo(tileenums::Direction direction) const {
    return getPosition().hasNeighbor(direction);
}

void Unit::moveTo(tileenums::Direction direction) {
    coords_ = getPosition().getNeighbor(direction).coords;
}

bool operator == (const Unit& lhs, const Unit& rhs) {
    return (lhs.coords_ == rhs.coords_) && (lhs.properties_ == rhs.properties_)
        && (lhs.model_ == rhs.model_) && (lhs.owner_ == rhs.owner_);
}


}  // namespace units

