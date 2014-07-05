/* Copyright 2014 <Piotr Derkowski> */

#include <stdexcept>
#include <memory>
#include <queue>
#include "Tile.hpp"
#include "Coordinates.hpp"
#include "MapModel.hpp"
#include "TileEnums.hpp"

using namespace tileenums;

Tile::Tile(const IntRotPoint& coords, Type type)
    : coords(coords), type(type), model_(nullptr)
{ }

void Tile::setModel(const MapModel* model) {
    model_ = model;
}

bool Tile::hasNeighbor(Direction direction) const {
    auto neighborCoords = getNeighborCoords(direction);
    return model_->isInBounds(model_->getTile(IntIsoPoint(neighborCoords.toIsometric())));
}

std::shared_ptr<const Tile> Tile::getNeighbor(Direction direction) const {
    if (isValid()) {
        return model_->getTile(IntIsoPoint(getNeighborCoords(direction).toIsometric()));
    } else {
        throw std::logic_error("Trying to find neighbors of invalid tile.");
    }
}

std::vector<std::shared_ptr<const Tile>> Tile::getNeighbors() const {
    std::vector<std::shared_ptr<const Tile>> neighbors;

    neighbors.push_back(getNeighbor(Direction::Top));
    neighbors.push_back(getNeighbor(Direction::TopRight));
    neighbors.push_back(getNeighbor(Direction::Right));
    neighbors.push_back(getNeighbor(Direction::BottomRight));
    neighbors.push_back(getNeighbor(Direction::Bottom));
    neighbors.push_back(getNeighbor(Direction::BottomLeft));
    neighbors.push_back(getNeighbor(Direction::Left));
    neighbors.push_back(getNeighbor(Direction::TopLeft));

    return neighbors;
}

std::vector<std::shared_ptr<const Tile>> Tile::getAdjacentNeighbors() const {
    std::vector<std::shared_ptr<const Tile>> neighbors;

    neighbors.push_back(getNeighbor(Direction::Top));
    neighbors.push_back(getNeighbor(Direction::Right));
    neighbors.push_back(getNeighbor(Direction::Bottom));
    neighbors.push_back(getNeighbor(Direction::Left));

    return neighbors;
}

Direction Tile::getDirection(std::shared_ptr<const Tile> neighbor) const {
    if (*neighbor == *getNeighbor(Direction::Top)) {
        return Direction::Top;
    } else if (*neighbor == *getNeighbor(Direction::TopRight)) {
        return Direction::TopRight;
    } else if (*neighbor == *getNeighbor(Direction::Right)) {
        return Direction::Right;
    } else if (*neighbor == *getNeighbor(Direction::BottomRight)) {
        return Direction::BottomRight;
    } else if (*neighbor == *getNeighbor(Direction::Bottom)) {
        return Direction::Bottom;
    } else if (*neighbor == *getNeighbor(Direction::BottomLeft)) {
        return Direction::BottomLeft;
    } else if (*neighbor == *getNeighbor(Direction::Left)) {
        return Direction::Left;
    } else if (*neighbor == *getNeighbor(Direction::TopLeft)) {
        return Direction::TopLeft;
    } else {
        throw std::invalid_argument("Tile " + toString(neighbor->coords) + " is not adjacent to " + toString(coords) + ".");
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


bool operator == (const Tile& lhs, const Tile& rhs) {
    return lhs.coords == rhs.coords && lhs.model_ == rhs.model_;
}

bool operator != (const Tile& lhs, const Tile& rhs) {
    return !(lhs == rhs);
}
