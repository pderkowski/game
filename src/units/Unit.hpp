/* Copyright 2014 <Piotr Derkowski> */

#ifndef UNITS_UNIT_HPP_
#define UNITS_UNIT_HPP_

#include <memory>
#include "Tile.hpp"

namespace units {

enum class Type {
    Phalanx
};

class Unit {
public:
    explicit Unit(std::shared_ptr<const Tile> position);
    virtual ~Unit() { }

    virtual Type getType() const = 0;
    std::shared_ptr<const Tile> getPosition() const;

protected:
    std::shared_ptr<const Tile> position_;
};

}  // namespace units

#endif  // UNITS_UNIT_HPP_
