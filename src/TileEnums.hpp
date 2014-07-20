/* Copyright 2014 <Piotr Derkowski> */

#ifndef TILEENUMS_HPP_
#define TILEENUMS_HPP_

#include <string>
#include <stdexcept>
#include <functional>

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

}  // namespace tileenums


namespace std {

template <>
struct hash<tileenums::Direction>
{
    std::size_t operator()(const tileenums::Direction& direction) const
    {
        static std::hash<int> typeHasher;
        return typeHasher(static_cast<int>(direction));
    }
};

}  // namespace std

inline std::string toString(tileenums::Direction direction) {
    switch (direction) {
    case tileenums::Direction::Top:
        return "Top";
    case tileenums::Direction::TopRight:
        return "TopRight";
    case tileenums::Direction::Right:
        return "Right";
    case tileenums::Direction::BottomRight:
        return "BottomRight";
    case tileenums::Direction::Bottom:
        return "Bottom";
    case tileenums::Direction::BottomLeft:
        return "BottomLeft";
    case tileenums::Direction::Left:
        return "Left";
    case tileenums::Direction::TopLeft:
        return "TopLeft";
    default:
        throw std::logic_error("Unrecognized direction.");
    }
}

#endif  // TILEENUMS_HPP_
