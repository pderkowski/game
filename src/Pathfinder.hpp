/* Copyright 2014 <Piotr Derkowski> */

#ifndef PATHFINDER_HPP_
#define PATHFINDER_HPP_

#include <vector>
#include <map>
#include <unordered_map>
#include "Tile.hpp"
#include "TileEnums.hpp"

class Pathfinder {
public:
    explicit Pathfinder(const std::map<tileenums::Type, unsigned>& cost);

    bool doesPathExist(const Tile& source, const Tile& goal) const;
    std::vector<Tile> findPath(const Tile& source, const Tile& goal) const;

private:
    struct Node {

        Tile tile;
        unsigned distance;

        bool operator > (const Node& rhs) const;
    };

private:
    std::vector<Tile> readPath(const Tile& source, const Tile& goal,
        const std::unordered_map<Tile, Tile>& previous) const;
    bool isPassable(tileenums::Type type) const;

    std::map<tileenums::Type, unsigned> cost_;
};

#endif  // PATHFINDER_HPP_
