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

std::vector<tileenums::Direction> Pathfinder::findPath(const Tile& source, const Tile& goal) const {
    std::cerr << "Source: " << toString(source.coords) << "\n";
    std::cerr << "Goal: " << toString(goal.coords) << "\n";

    std::vector<tileenums::Direction> res;

    Tile current = source;
    while (current != goal) {
        tileenums::Direction nextStep = findNextStep(current, goal);
        res.push_back(nextStep);
        current = *(current.getNeighbor(nextStep));
    }

    return res;
}

tileenums::Direction Pathfinder::findNextStep(const Tile& source, const Tile& goal) const {
    if (source.coords.y < goal.coords.y) {
        if (source.coords.x < goal.coords.x) {
            return tileenums::Direction::BottomRight;
        } else if (source.coords.x > goal.coords.x) {
            return tileenums::Direction::BottomLeft;
        } else {
            return tileenums::Direction::Bottom;
        }
    } else if (source.coords.y > goal.coords.y) {
        if (source.coords.x < goal.coords.x) {
            return tileenums::Direction::TopRight;
        } else if (source.coords.x > goal.coords.x) {
            return tileenums::Direction::TopLeft;
        } else {
            return tileenums::Direction::Top;
        }
    } else {
        if (source.coords.x < goal.coords.x) {
            return tileenums::Direction::Right;
        } else if (source.coords.x > goal.coords.x) {
            return tileenums::Direction::Left;
        } else {
            throw std::logic_error("Can't find next step: source and goal are equal.");
        }
    }
}
