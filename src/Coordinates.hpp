/* Copyright 2014 <Piotr Derkowski> */

#ifndef COORDINATES_HPP_
#define COORDINATES_HPP_

#include "Converter.hpp"

namespace coordinates {
    struct CartesianPoint {
        int x;
        int y;
    };

    struct IsometricPoint {
        int x;
        int y;
    };

    struct RotatedPoint {
        int x;
        int y;
    };

    extern const Converter<CartesianPoint, IsometricPoint> cartesian_isometric;
    extern const Converter<IsometricPoint, RotatedPoint> isometric_rotated;
    extern const Converter<RotatedPoint, CartesianPoint> rotated_cartesian;
}  // namespace coordinates

#endif  // COORDINATES_HPP_
