/* Copyright 2014 <Piotr Derkowski> */

#ifndef TILE_HPP_
#define TILE_HPP_

#include <memory>
#include "Attributes.hpp"
#include "Coordinates.hpp"
#include "TileEnums.hpp"
class MapModel;

using namespace tileenums;

class Tile {
public:
    Tile(const IntRotPoint& coords, Type type = Type::Empty);

    void setModel(const MapModel* model);

    bool hasNeighbor(Direction direction) const;
    std::shared_ptr<const Tile> getNeighbor(Direction direction) const;
    std::vector<std::shared_ptr<const Tile>> getNeighbors() const;
    std::vector<std::shared_ptr<const Tile>> getAdjacentNeighbors() const;

    Direction getDirection(std::shared_ptr<const Tile> neighbor) const;

    IntRotPoint coords;
    Type type;
    Attributes attributes;

private:
    friend bool operator == (const Tile& lhs, const Tile& rhs);
    friend bool operator != (const Tile& lhs, const Tile& rhs);

    IntRotPoint getNeighborCoords(Direction direction) const;
    bool isValid() const;

    const MapModel* model_;
};

bool operator == (const Tile& lhs, const Tile& rhs);
bool operator != (const Tile& lhs, const Tile& rhs);

#endif  // TILE_HPP_
