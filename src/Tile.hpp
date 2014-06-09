/* Copyright 2014 <Piotr Derkowski> */

#ifndef TILE_HPP_
#define TILE_HPP_

#include "Coordinates.hpp"

class Tile {
public:
    enum Type {
        Empty = 0,  // don't assign other values
        Water,
        Grassland,
        Plains,
        Forest,
        Desert,
        Hills,
        Mountains,
        NumberOfTileTypes  // this has to be the last one in this enum
    };

    Tile(const IntRotPoint& coordinates);
    Tile(const IntRotPoint& coordinates, Type type);

    void toggleVisibility();

    IntRotPoint coords;
    Type type;

    bool isVisible;
};

#endif  // TILE_HPP_
