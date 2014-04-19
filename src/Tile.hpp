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

    Tile();
    explicit Tile(Type type);

    Type getType();
    void setType(Type type);

    void toggleVisibility();
    bool isVisible() const;

private:
    Type type_;

    bool isVisible_;
};

#endif  // TILE_HPP_
