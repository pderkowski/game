/* Copyright 2014 <Piotr Derkowski> */

#include <iostream>
#include <algorithm>
#include <stdexcept>
#include <memory>
#include <queue>
#include "Tile.hpp"
#include "Coordinates.hpp"
#include "MapModel.hpp"
#include "TileEnums.hpp"

using namespace tileenums;

Tile::Tile(const IntRotPoint& coords, Type type, MapModel* model)
    : coords(coords), type(type), model_(model)
{ }

void Tile::setModel(MapModel* model) {
    model_ = model;
}

bool Tile::hasNeighbor(Direction direction) const {
    auto neighborCoords = getNeighborCoords(direction);
    return model_->isInBounds(model_->getTile(IntIsoPoint(neighborCoords.toIsometric())));
}

std::shared_ptr<const Tile> Tile::getNeighbor(Direction direction) const {
    if (isValid()) {
        if (hasNeighbor(direction)) {
            return model_->getTile(IntIsoPoint(getNeighborCoords(direction).toIsometric()));
        } else {
            throw std::logic_error("Requested neighbor doesn't exist.");
        }
    } else {
        throw std::logic_error("Trying to find neighbors of invalid tile.");
    }
}

std::vector<std::shared_ptr<const Tile>> Tile::getNeighbors() const {
    std::vector<std::shared_ptr<const Tile>> neighbors;

    if (hasNeighbor(Direction::Top))
        neighbors.push_back(getNeighbor(Direction::Top));
    if (hasNeighbor(Direction::TopRight))
        neighbors.push_back(getNeighbor(Direction::TopRight));
    if (hasNeighbor(Direction::Right))
        neighbors.push_back(getNeighbor(Direction::Right));
    if (hasNeighbor(Direction::BottomRight))
        neighbors.push_back(getNeighbor(Direction::BottomRight));
    if (hasNeighbor(Direction::Bottom))
        neighbors.push_back(getNeighbor(Direction::Bottom));
    if (hasNeighbor(Direction::BottomLeft))
        neighbors.push_back(getNeighbor(Direction::BottomLeft));
    if (hasNeighbor(Direction::Left))
        neighbors.push_back(getNeighbor(Direction::Left));
    if (hasNeighbor(Direction::TopLeft))
        neighbors.push_back(getNeighbor(Direction::TopLeft));

    return neighbors;
}

std::vector<std::shared_ptr<const Tile>> Tile::getAdjacentNeighbors() const {
    std::vector<std::shared_ptr<const Tile>> neighbors;

    if (hasNeighbor(Direction::Top))
        neighbors.push_back(getNeighbor(Direction::Top));
    if (hasNeighbor(Direction::Right))
        neighbors.push_back(getNeighbor(Direction::Right));
    if (hasNeighbor(Direction::Bottom))
        neighbors.push_back(getNeighbor(Direction::Bottom));
    if (hasNeighbor(Direction::Left))
        neighbors.push_back(getNeighbor(Direction::Left));

    return neighbors;
}

Direction Tile::getDirection(std::shared_ptr<const Tile> neighbor) const {
    if (hasNeighbor(Direction::Top) && *neighbor == *getNeighbor(Direction::Top)) {
        return Direction::Top;
    } else if (hasNeighbor(Direction::TopRight) && *neighbor == *getNeighbor(Direction::TopRight)) {
        return Direction::TopRight;
    } else if (hasNeighbor(Direction::Right) && *neighbor == *getNeighbor(Direction::Right)) {
        return Direction::Right;
    } else if (hasNeighbor(Direction::BottomRight) && *neighbor == *getNeighbor(Direction::BottomRight)) {
        return Direction::BottomRight;
    } else if (hasNeighbor(Direction::Bottom) && *neighbor == *getNeighbor(Direction::Bottom)) {
        return Direction::Bottom;
    } else if (hasNeighbor(Direction::BottomLeft) && *neighbor == *getNeighbor(Direction::BottomLeft)) {
        return Direction::BottomLeft;
    } else if (hasNeighbor(Direction::Left) && *neighbor == *getNeighbor(Direction::Left)) {
        return Direction::Left;
    } else if (hasNeighbor(Direction::TopLeft) && *neighbor == *getNeighbor(Direction::TopLeft)) {
        return Direction::TopLeft;
    } else {
        throw std::invalid_argument("Tile " + toString(neighbor->coords) + " is not a neighbor of "
            + toString(coords) + ".");
    }
}

bool Tile::isValid() const {
    return model_ != nullptr;
}

IntRotPoint Tile::getNeighborCoords(Direction direction) const {
    switch (direction) {
    case Direction::Top:
        return IntRotPoint(coords.x, coords.y - 1);
    case Direction::TopRight:
        return IntRotPoint(coords.x + 1, coords.y - 1);
    case Direction::Right:
        return IntRotPoint(coords.x + 1, coords.y);
    case Direction::BottomRight:
        return IntRotPoint(coords.x + 1, coords.y + 1);
    case Direction::Bottom:
        return IntRotPoint(coords.x, coords.y + 1);
    case Direction::BottomLeft:
        return IntRotPoint(coords.x - 1, coords.y + 1);
    case Direction::Left:
        return IntRotPoint(coords.x - 1, coords.y);
    case Direction::TopLeft:
        return IntRotPoint(coords.x - 1, coords.y - 1);
    default:
        throw std::logic_error("Unrecognized direction.");
    }
}

std::vector<units::Unit*> Tile::getUnits() {
    std::vector<units::Unit*> res = model_->getUnits();

    std::remove_if(res.begin(), res.end(), [this] (units::Unit* unit) {
        return *(unit->getPosition()) == *this;
    });

    return res;
}



bool operator == (const Tile& lhs, const Tile& rhs) {
    return lhs.coords == rhs.coords && lhs.model_ == rhs.model_;
}

bool operator != (const Tile& lhs, const Tile& rhs) {
    return !(lhs == rhs);
}
