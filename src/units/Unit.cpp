/* Copyright 2014 <Piotr Derkowski> */

#include <stdexcept>
#include "Unit.hpp"
#include "Tile.hpp"
#include "Coordinates.hpp"
#include "TileEnums.hpp"
#include "MapModel.hpp"

namespace units {


unsigned long long Unit::idSequence = 0;


Unit::Unit(const IntRotPoint& coords, Type type, const MapModel* model)
    : coords_(coords), type_(type), model_(model), id_(idSequence++)
{ }

void Unit::setModel(const MapModel* model) {
    model_ = model;
}

Type Unit::getType() const {
    return type_;
}

unsigned long long Unit::getId() const {
    return id_;
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

