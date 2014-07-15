/* Copyright 2014 <Piotr Derkowski> */

#include <iostream>
#include <vector>
#include <functional>
#include <unordered_map>
#include <set>
#include <memory>
#include <algorithm>
#include <queue>
#include <limits>
#include "Tile.hpp"
#include "TileEnums.hpp"
#include "Pathfinder.hpp"
#include "Coordinates.hpp"

Pathfinder::Pathfinder(const std::map<tileenums::Type, unsigned>& cost)
    : cost_(cost)
{ }

bool Pathfinder::doesPathExist(__attribute__((unused)) const Tile& source,
    __attribute__((unused)) const Tile& goal) const
{
    return true;
}

std::vector<Tile> Pathfinder::findPath(const Tile& source, const Tile& goal) const {
    std::unordered_map<Tile, unsigned> distance;
    std::unordered_map<Tile, Tile> previous;
    std::set<Tile> visited;
    std::priority_queue<Node, std::vector<Node>, std::greater<Node>> queue;

    queue.push(Node{ source, 0 });
    distance[source] = 0;

    while (!queue.empty()) {
        Node current = queue.top();
        queue.pop();

        if (current.tile == goal) {
            break;
        } else if (!visited.count(current.tile)) {
            visited.insert(current.tile);

            std::vector<std::shared_ptr<const Tile>> neighbors = current.tile.getNeighbors();
            for (auto neighbor : neighbors) {
                if (isPassable(neighbor->type) && !visited.count(*neighbor)) {
                    unsigned newDistance = current.distance + cost_.at(neighbor->type);
                    if (!distance.count(*neighbor) || (newDistance < distance.at(*neighbor))) {
                        distance[*neighbor] = newDistance;
                        previous[*neighbor] = current.tile;
                        queue.push(Node{ *neighbor, newDistance });
                    }
                }
            }
        }
    }

    return readPath(source, goal, previous);
}

std::vector<Tile> Pathfinder::readPath(const Tile& source, const Tile& goal,
    const std::unordered_map<Tile, Tile>& previous) const
{
    std::vector<Tile> pathBackwards;

    for (Tile current = goal; current != source; current = previous.at(current)) {
        pathBackwards.push_back(current);
    }
    pathBackwards.push_back(source);

    std::reverse(pathBackwards.begin(), pathBackwards.end());
    return pathBackwards;
}

bool Pathfinder::isPassable(tileenums::Type type) const {
    return cost_.at(type) != std::numeric_limits<unsigned>::max();
}

bool Pathfinder::Node::operator > (const Node& rhs) const {
    return distance > rhs.distance;
}
