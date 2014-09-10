/* Copyright 2014 <Piotr Derkowski> */

#ifndef PLAYERS_PATHFINDER_HPP_
#define PLAYERS_PATHFINDER_HPP_

#include <vector>
#include <map>
#include <unordered_map>
#include "map/Tile.hpp"
#include "TileEnums.hpp"
#include "Fog.hpp"


namespace players {


class Pathfinder {
public:
    Pathfinder(const std::map<tileenums::Type, unsigned>& cost, const Fog& fog);

    bool doesPathExist(const map::Tile& source, const map::Tile& goal) const;
    std::vector<map::Tile> findPath(const map::Tile& source, const map::Tile& goal) const;

private:
    struct Node {

        map::Tile tile;
        unsigned distance;

        bool operator > (const Node& rhs) const;
    };

private:
    std::vector<map::Tile> readPath(const map::Tile& source, const map::Tile& goal,
        const std::unordered_map<map::Tile, map::Tile>& previous) const;
    bool isPassable(const map::Tile& tile) const;

private:
    std::map<tileenums::Type, unsigned> cost_;

    Fog fog_;
};


}  // namespace players


#endif  // PLAYERS_PATHFINDER_HPP_
