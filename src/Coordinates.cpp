/* Copyright 2014 <Piotr Derkowski> */

#include <cmath>
#include "Coordinates.hpp"

namespace {

IsoPoint cartesian_isometric(const CartPoint& cart) {
    return IsoPoint(cart.x * 0.5 - cart.y * 0.5, cart.y);
}

CartPoint isometric_cartesian(const IsoPoint& iso) {
    return CartPoint(iso.x * 2 + iso.y, iso.y);
}

RotPoint isometric_rotated(const IsoPoint& iso) {
    return RotPoint(iso.x, iso.x + iso.y);
}

IsoPoint rotated_isometric(const RotPoint& rot) {
    return IsoPoint(rot.x, rot.y - rot.x);
}

CartPoint rotated_cartesian(const RotPoint& rot) {
    return CartPoint(rot.x + rot.y, rot.y - rot.x);
}

RotPoint cartesian_rotated(const CartPoint& cart) {
    return RotPoint(cart.x * 0.5 - cart.y * 0.5, cart.x * 0.5 + cart.y * 0.5);
}

}


CartPoint::CartPoint(double x, double y)
    : x(x), y(y)
{ }

CartPoint::CartPoint(const IntCartPoint& p)
    : x(p.x), y(p.y)
{ }

IsoPoint CartPoint::toIsometric() const {
    return ::cartesian_isometric(*this);
}

RotPoint CartPoint::toRotated() const {
    return ::cartesian_rotated(*this);
}

bool operator == (const CartPoint& lhs, const CartPoint& rhs) {
    return lhs.x == rhs.x && lhs.y == rhs.y;
}

bool operator != (const CartPoint& lhs, const CartPoint& rhs) {
    return lhs.x != rhs.x || lhs.y != rhs.y;
}


IntCartPoint::IntCartPoint(int x, int y)
    : x(x), y(y)
{ }

IntCartPoint::IntCartPoint(const CartPoint& p)
    : x(std::lround(p.x)), y(std::lround(p.y))
{ }

IsoPoint IntCartPoint::toIsometric() const {
    return ::cartesian_isometric(*this);
}

RotPoint IntCartPoint::toRotated() const {
    return ::cartesian_rotated(*this);
}

bool operator == (const IntCartPoint& lhs, const IntCartPoint& rhs) {
    return lhs.x == rhs.x && lhs.y == rhs.y;
}

bool operator != (const IntCartPoint& lhs, const IntCartPoint& rhs) {
    return lhs.x != rhs.x || lhs.y != rhs.y;
}


IsoPoint::IsoPoint(double x, double y)
    : x(x), y(y)
{ }

IsoPoint::IsoPoint(const IntIsoPoint& p)
    : x(p.x), y(p.y)
{ }

CartPoint IsoPoint::toCartesian() const {
    return ::isometric_cartesian(*this);
}

RotPoint IsoPoint::toRotated() const {
    return ::isometric_rotated(*this);
}

bool operator == (const IsoPoint& lhs, const IsoPoint& rhs) {
    return lhs.x == rhs.x && lhs.y == rhs.y;
}

bool operator != (const IsoPoint& lhs, const IsoPoint& rhs) {
    return lhs.x != rhs.x || lhs.y != rhs.y;
}


IntIsoPoint::IntIsoPoint(int x, int y)
    : x(x), y(y)
{ }

IntIsoPoint::IntIsoPoint(const IsoPoint& p)
    : x(std::lround(p.x)), y(std::lround(p.y))
{ }

CartPoint IntIsoPoint::toCartesian() const {
    return ::isometric_cartesian(*this);
}

RotPoint IntIsoPoint::toRotated() const {
    return ::isometric_rotated(*this);
}

bool operator == (const IntIsoPoint& lhs, const IntIsoPoint& rhs) {
    return lhs.x == rhs.x && lhs.y == rhs.y;
}

bool operator != (const IntIsoPoint& lhs, const IntIsoPoint& rhs) {
    return lhs.x != rhs.x || lhs.y != rhs.y;
}


RotPoint::RotPoint(double x, double y)
    : x(x), y(y)
{ }

RotPoint::RotPoint(const IntRotPoint& p)
    : x(p.x), y(p.y)
{ }

CartPoint RotPoint::toCartesian() const {
    return ::rotated_cartesian(*this);
}

IsoPoint RotPoint::toIsometric() const {
    return ::rotated_isometric(*this);
}

bool operator == (const RotPoint& lhs, const RotPoint& rhs) {
    return lhs.x == rhs.x && lhs.y == rhs.y;
}

bool operator != (const RotPoint& lhs, const RotPoint& rhs) {
    return lhs.x != rhs.x || lhs.y != rhs.y;
}


IntRotPoint::IntRotPoint(int x, int y)
    : x(x), y(y)
{ }

IntRotPoint::IntRotPoint(const RotPoint& p)
    : x(std::lround(p.x)), y(std::lround(p.y))
{ }

CartPoint IntRotPoint::toCartesian() const {
    return ::rotated_cartesian(*this);
}

IsoPoint IntRotPoint::toIsometric() const {
    return ::rotated_isometric(*this);
}

bool operator == (const IntRotPoint& lhs, const IntRotPoint& rhs) {
    return lhs.x == rhs.x && lhs.y == rhs.y;
}

bool operator != (const IntRotPoint& lhs, const IntRotPoint& rhs) {
    return lhs.x != rhs.x || lhs.y != rhs.y;
}

