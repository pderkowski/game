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

std::shared_ptr<const Tile> Tile::getNeighbor(Direction direction) const {
    if (isValid()) {
        IntRotPoint neighborCoords;

        switch (direction) {
        case Direction::Top:
            neighborCoords = IntRotPoint(coords.x, coords.y - 1);
            break;
        case Direction::TopRight:
            neighborCoords = IntRotPoint(coords.x + 1, coords.y - 1);
            break;
        case Direction::Right:
            neighborCoords = IntRotPoint(coords.x + 1, coords.y);
            break;
        case Direction::BottomRight:
            neighborCoords = IntRotPoint(coords.x + 1, coords.y + 1);
            break;
        case Direction::Bottom:
            neighborCoords = IntRotPoint(coords.x, coords.y + 1);
            break;
        case Direction::BottomLeft:
            neighborCoords = IntRotPoint(coords.x - 1, coords.y + 1);
            break;
        case Direction::Left:
            neighborCoords = IntRotPoint(coords.x - 1, coords.y);
            break;
        case Direction::TopLeft:
            neighborCoords = IntRotPoint(coords.x - 1, coords.y - 1);
            break;
        };

        return model_->getTile(IntIsoPoint(neighborCoords.toIsometric()));
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

bool operator == (const Tile& lhs, const Tile& rhs) {
    return lhs.coords == rhs.coords && lhs.model_ == rhs.model_;
}

bool operator != (const Tile& lhs, const Tile& rhs) {
    return !(lhs == rhs);
}
