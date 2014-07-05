/* Copyright 2014 <Piotr Derkowski> */

#ifndef COORDINATES_HPP_
#define COORDINATES_HPP_

#include <string>

struct IntCartPoint;
struct CartPoint;
struct IntIsoPoint;
struct IsoPoint;
struct IntRotPoint;
struct RotPoint;

struct CartPoint {
    CartPoint();
    CartPoint(double x, double y);
    CartPoint(const IntCartPoint& p);

    IsoPoint toIsometric() const;
    RotPoint toRotated() const;

    std::string toString() const;

    double x;
    double y;
};

bool operator == (const CartPoint& lhs, const CartPoint& rhs);
bool operator != (const CartPoint& lhs, const CartPoint& rhs);

struct IntCartPoint {
    IntCartPoint();
    IntCartPoint(int x, int y);
    explicit IntCartPoint(const CartPoint& p);

    IsoPoint toIsometric() const;
    RotPoint toRotated() const;

    int x;
    int y;
};

bool operator == (const IntCartPoint& lhs, const IntCartPoint& rhs);
bool operator != (const IntCartPoint& lhs, const IntCartPoint& rhs);

struct IsoPoint {
    IsoPoint();
    IsoPoint(double x, double y);
    IsoPoint(const IntIsoPoint& p);

    RotPoint toRotated() const;
    CartPoint toCartesian() const;

    double x;
    double y;
};

bool operator == (const IsoPoint& lhs, const IsoPoint& rhs);
bool operator != (const IsoPoint& lhs, const IsoPoint& rhs);

struct IntIsoPoint {
    IntIsoPoint();
    IntIsoPoint(int x, int y);
    explicit IntIsoPoint(const IsoPoint& p);

    RotPoint toRotated() const;
    CartPoint toCartesian() const;

    int x;
    int y;
};

bool operator == (const IntIsoPoint& lhs, const IntIsoPoint& rhs);
bool operator != (const IntIsoPoint& lhs, const IntIsoPoint& rhs);

struct RotPoint {
    RotPoint();
    RotPoint(double x, double y);
    RotPoint(const IntRotPoint& p);

    IsoPoint toIsometric() const;
    CartPoint toCartesian() const;

    double x;
    double y;
};

bool operator == (const RotPoint& lhs, const RotPoint& rhs);
bool operator != (const RotPoint& lhs, const RotPoint& rhs);

struct IntRotPoint {
    IntRotPoint();
    IntRotPoint(int x, int y);
    explicit IntRotPoint(const RotPoint& p);

    IsoPoint toIsometric() const;
    CartPoint toCartesian() const;

    int x;
    int y;
};

bool operator == (const IntRotPoint& lhs, const IntRotPoint& rhs);
bool operator != (const IntRotPoint& lhs, const IntRotPoint& rhs);

template <class T>
std::string toString(const T& t) {
    return "<" + std::to_string(t.x) + ", " + std::to_string(t.y) + ">";
}

#endif  // COORDINATES_HPP_
