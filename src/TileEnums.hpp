/* Copyright 2014 <Piotr Derkowski> */

#ifndef TILEENUMS_HPP_
#define TILEENUMS_HPP_

namespace tileenums {

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

enum class Unit {
    Phalanx
};

enum class Direction {
    Top = 1 << 0,
    TopRight = 1 << 1,
    Right = 1 << 2,
    BottomRight = 1 << 3,
    Bottom = 1 << 4,
    BottomLeft = 1 << 5,
    Left = 1 << 6,
    TopLeft = 1 << 7
};

}

#endif  // TILEENUMS_HPP_
