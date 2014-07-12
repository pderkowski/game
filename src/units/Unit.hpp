/* Copyright 2014 <Piotr Derkowski> */

#ifndef UNITS_UNIT_HPP_
#define UNITS_UNIT_HPP_

#include <memory>
#include "TileEnums.hpp"
#include "Coordinates.hpp"
class MapModel;
class Tile;

namespace units {

enum class Type {
    Phalanx
};

class Unit {
public:
    Unit(const IntRotPoint& coords, Type type, const MapModel* model = nullptr);

    void setModel(const MapModel* model);

    Type getType() const;
    std::shared_ptr<const Tile> getPosition() const;
    bool canMoveTo(tileenums::Direction direction) const;
    void moveTo(tileenums::Direction direction);

private:
    IntRotPoint coords_;
    Type type_;
    const MapModel* model_;
};

}  // namespace units

#endif  // UNITS_UNIT_HPP_
