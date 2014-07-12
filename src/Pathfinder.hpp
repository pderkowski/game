/* Copyright 2014 <Piotr Derkowski> */

#ifndef PATHFINDER_HPP_
#define PATHFINDER_HPP_

#include <vector>
#include "Tile.hpp"
#include "TileEnums.hpp"

class Pathfinder {
public:
    bool doesPathExist(const Tile& source, const Tile& goal) const;
    std::vector<tileenums::Direction> findPath(const Tile& source, const Tile& goal) const;

private:
    tileenums::Direction findNextStep(const Tile& source, const Tile& goal) const;
};

#endif  // PATHFINDER_HPP_
