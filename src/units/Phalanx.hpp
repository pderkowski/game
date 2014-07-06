/* Copyright 2014 <Piotr Derkowski> */

#include "Unit.hpp"

#ifndef UNITS_PHALANX_HPP_
#define UNITS_PHALANX_HPP_

namespace units {

class Phalanx : public Unit {
public:
    using Unit::Unit;
    virtual ~Phalanx() { }

    virtual units::Type getType() const override;
};

}

#endif  // UNITS_PHALANX_HPP_
