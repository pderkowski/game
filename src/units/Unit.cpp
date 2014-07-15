/* Copyright 2014 <Piotr Derkowski> */

#include <memory>
#include <stdexcept>
#include <vector>
#include <climits>
#include "Unit.hpp"
#include "Tile.hpp"
#include "Coordinates.hpp"
#include "TileEnums.hpp"
#include "MapModel.hpp"

namespace units {


Unit::Unit(const IntRotPoint& coords, Type type, const MapModel* model)
    : coords_(coords), type_(type), model_(model)
{ }

void Unit::setModel(const MapModel* model) {
    model_ = model;
}

Type Unit::getType() const {
    return type_;
}

std::shared_ptr<const Tile> Unit::getPosition() const {
    if (model_ != nullptr)
        return model_->getTile(IntIsoPoint(coords_.toIsometric()));
    else
        throw std::runtime_error("No model set in unit.");
}

bool Unit::canMoveTo(tileenums::Direction direction) const {
    return getPosition()->hasNeighbor(direction);
}

void Unit::moveTo(tileenums::Direction direction) {
    coords_ = getPosition()->getNeighbor(direction)->coords;
}

std::map<tileenums::Type, unsigned> Unit::getMovingCosts() const {
    return std::map<tileenums::Type, unsigned>{
        { tileenums::Type::Empty, UINT_MAX },
        { tileenums::Type::Water, UINT_MAX },
        { tileenums::Type::Grassland, 1 },
        { tileenums::Type::Plains, 1 },
        { tileenums::Type::Forest, 2 },
        { tileenums::Type::Desert, 1 },
        { tileenums::Type::Hills, 2 },
        { tileenums::Type::Mountains, UINT_MAX }
    };
}


bool operator == (const Unit& lhs, const Unit& rhs) {
    return (lhs.coords_ == rhs.coords_) && (lhs.type_ == rhs.type_) && (lhs.model_ == rhs.model_);
}


}  // namespace units

