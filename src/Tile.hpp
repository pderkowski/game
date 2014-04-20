/* Copyright 2014 <Piotr Derkowski> */

#ifndef TILE_HPP_
#define TILE_HPP_

class Tile {
public:
    enum Type {
        Empty = 0,  // don't assign other values
        Water,
        Plains,
        Hills,
        Mountains,
        NumberOfTileTypes  // this has to be the last one in this enum
    };

    Tile(int row, int column);
    Tile(int row, int column, Type type);

    void toggleVisibility();

    int row;
    int column;
    Type type;

    bool isVisible;
};

#endif  // TILE_HPP_
