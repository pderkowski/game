/* Copyright 2014 <Piotr Derkowski> */

#include <stdexcept>
#include "Unit.hpp"
#include "Tile.hpp"
#include "Coordinates.hpp"
#include "TileEnums.hpp"
#include "MapModel.hpp"
#include "players/Player.hpp"

namespace units {



Unit::Unit(const IntRotPoint& coords, Type type, const MapModel* model, const players::Player* owner)
    : coords_(coords), type_(type), movesLeft_(0), model_(model), owner_(owner)
{ }

// void Unit::setModel(const MapModel* model) {
//     model_ = model;
// }

void Unit::setMovesLeft(int movesLeft) {
    movesLeft_ = movesLeft;
}

Type Unit::getType() const {
    return type_;
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
    return movesLeft_;
}

bool Unit::canMoveTo(tileenums::Direction direction) const {
    return getPosition().hasNeighbor(direction);
}

void Unit::moveTo(tileenums::Direction direction) {
    coords_ = getPosition().getNeighbor(direction).coords;
}

bool operator == (const Unit& lhs, const Unit& rhs) {
    return (lhs.coords_ == rhs.coords_) && (lhs.type_ == rhs.type_) && (lhs.model_ == rhs.model_);
}


}  // namespace units

