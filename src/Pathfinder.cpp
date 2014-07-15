/* Copyright 2014 <Piotr Derkowski> */

#include <iostream>
#include <vector>
#include "Tile.hpp"
#include "TileEnums.hpp"
#include "Pathfinder.hpp"
#include "Coordinates.hpp"

bool Pathfinder::doesPathExist(__attribute__((unused)) const Tile& source,
    __attribute__((unused)) const Tile& goal) const
{
    return true;
}

std::vector<Tile> Pathfinder::findPath(const Tile& source, const Tile& goal) const {
    std::vector<Tile> res;

    Tile current = source;
    while (current != goal) {
        res.push_back(current);
        current = findNextStep(current, goal);
    }
    res.push_back(goal);

    return res;
}

Tile Pathfinder::findNextStep(const Tile& source, const Tile& goal) const {
    if (source.coords.y < goal.coords.y) {
        if (source.coords.x < goal.coords.x) {
            return *(source.getNeighbor(tileenums::Direction::BottomRight));
        } else if (source.coords.x > goal.coords.x) {
            return *(source.getNeighbor(tileenums::Direction::BottomLeft));
        } else {
            return *(source.getNeighbor(tileenums::Direction::Bottom));
        }
    } else if (source.coords.y > goal.coords.y) {
        if (source.coords.x < goal.coords.x) {
            return *(source.getNeighbor(tileenums::Direction::TopRight));
        } else if (source.coords.x > goal.coords.x) {
            return *(source.getNeighbor(tileenums::Direction::TopLeft));
        } else {
            return *(source.getNeighbor(tileenums::Direction::Top));
        }
    } else {
        if (source.coords.x < goal.coords.x) {
            return *(source.getNeighbor(tileenums::Direction::Right));
        } else if (source.coords.x > goal.coords.x) {
            return *(source.getNeighbor(tileenums::Direction::Left));
        } else {
            throw std::logic_error("Can't find next step: source and goal are equal.");
        }
    }
}
