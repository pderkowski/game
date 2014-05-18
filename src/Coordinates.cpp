/* Copyright 2014 <Piotr Derkowski> */

#include <cmath>
#include <functional>
#include "Coordinates.hpp"
#include "Converter.hpp"

using namespace coordinates;

const Converter<CartesianPoint, IsometricPoint> coordinates::cartesian_isometric(
    [] (const CartesianPoint& car) {
        return IsometricPoint{ std::lrint(car.x * 0.5 - car.y * 0.5), std::lrint(car.y) };
    },
    [] (const IsometricPoint& iso) {
        return CartesianPoint{ std::lrint(iso.x * 2 + iso.y), std::lrint(iso.y) };
    }
);

const Converter<IsometricPoint, RotatedPoint> coordinates::isometric_rotated(
    [] (const IsometricPoint& iso) {
        return RotatedPoint{ std::lrint(iso.x), std::lrint(iso.x + iso.y) };
    },
    [] (const RotatedPoint& rot) {
        return IsometricPoint{ std::lrint(rot.x), std::lrint(rot.y - rot.x) };
    }
);

const Converter<RotatedPoint, CartesianPoint> coordinates::rotated_cartesian(
    [] (const RotatedPoint& rot) {
        return CartesianPoint{ std::lrint(rot.x + rot.y), std::lrint(rot.y - rot.x) };
    },
    [] (const CartesianPoint& car) {
        return RotatedPoint{ std::lrint(car.x * 0.5 - car.y * 0.5), std::lrint(car.x * 0.5 + car.y * 0.5) };
    }
);
