/* Copyright 2014 <Piotr Derkowski> */

#ifndef GRADIENT_HPP_
#define GRADIENT_HPP_

#include <map>
#include "Tile.hpp"

class Gradient {
public:
    void addPoint(double point, Tile::Type value);
    Tile::Type getValue(double point) const;

private:
    std::map<double, Tile::Type> points_;
};

#endif  // GRADIENT_HPP_
