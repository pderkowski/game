/* Copyright 2014 <Piotr Derkowski> */

#ifndef TILE_HPP_
#define TILE_HPP_

#include "Attributes.hpp"
#include "Coordinates.hpp"

class Tile {
public:
    enum class Type {
        Empty,
        Water,
        Grassland,
        Plains,
        Forest,
        Desert,
        Hills,
        Mountains
    };

    explicit Tile(const IntRotPoint& coordinates);
    Tile(const IntRotPoint& coordinates, Type type);

    void toggleVisibility();

    IntRotPoint coords;
    Type type;
    Attributes attributes;

    bool isVisible;
};

bool operator == (const Tile& lhs, const Tile& rhs);
bool operator != (const Tile& lhs, const Tile& rhs);

#endif  // TILE_HPP_
