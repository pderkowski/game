/* Copyright 2014 <Piotr Derkowski> */

#include <string>
#include <stdexcept>
#include "Gradient.hpp"

void Gradient::addPoint(double point, Tile::Type value) {
    if (0.0 > point || point > 1.0) {
        throw std::out_of_range(
            "Trying to add " + std::to_string(point) + " which is out of range.");
    } else {
        points_[point] = value;
    }
}

Tile::Type Gradient::getValue(double point) const {
    auto upperBound = points_.upper_bound(point);
    if (upperBound != points_.begin()) {
        return (--upperBound)->second;
    } else {
        throw std::out_of_range(
            "Trying to get " + std::to_string(point) + " which is out of range.");
    }
}
