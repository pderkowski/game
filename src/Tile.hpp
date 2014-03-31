/* Copyright 2014 <Piotr Derkowski> */

#ifndef TILE_HPP_
#define TILE_HPP_

class Tile {
public:
    enum Type {
        Empty,
        Water,
        Plains,
        Hills,
        Mountains
    };

    Tile();
    explicit Tile(Type type);

    Type getType();
    void setType(Type type);

private:
    Type type_;
};

#endif  // TILE_HPP_
