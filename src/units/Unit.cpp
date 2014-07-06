/* Copyright 2014 <Piotr Derkowski> */

#include <memory>
#include "Unit.hpp"
#include "Tile.hpp"

namespace units {

Unit::Unit(std::shared_ptr<const Tile> position)
    : position_(position)
{ }

std::shared_ptr<const Tile> Unit::getPosition() const {
    return position_;
}

}
