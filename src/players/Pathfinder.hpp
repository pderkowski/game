/* Copyright 2014 <Piotr Derkowski> */

#ifndef PLAYERS_PATHFINDER_HPP_
#define PLAYERS_PATHFINDER_HPP_

#include <vector>
#include <map>
#include <unordered_map>
#include "Tile.hpp"
#include "TileEnums.hpp"
#include "Fog.hpp"


namespace players {


class Pathfinder {
public:
    Pathfinder(const std::map<tileenums::Type, unsigned>& cost, const Fog& fog);

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
    bool isPassable(const Tile& tile) const;

private:
    std::map<tileenums::Type, unsigned> cost_;

    Fog fog_;
};


}  // namespace players


#endif  // PLAYERS_PATHFINDER_HPP_
