/* Copyright 2014 <Piotr Derkowski> */

#ifndef UNITS_MOVINGCOSTS_HPP_
#define UNITS_MOVINGCOSTS_HPP_

#include <map>
#include "TileEnums.hpp"
#include "Unit.hpp"

namespace units {


std::map<tileenums::Type, unsigned> getMovingCosts(units::Type type);


}  // namespace units

#endif  // UNITS_MOVINGCOSTS_HPP_
