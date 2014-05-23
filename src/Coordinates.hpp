/* Copyright 2014 <Piotr Derkowski> */

#ifndef COORDINATES_HPP_
#define COORDINATES_HPP_

struct IntCartPoint;
struct CartPoint;
struct IntIsoPoint;
struct IsoPoint;
struct IntRotPoint;
struct RotPoint;

struct CartPoint {
    CartPoint(double x, double y);
    CartPoint(const IntCartPoint& p);

    IsoPoint toIsometric() const;
    RotPoint toRotated() const;

    double x;
    double y;
};

struct IntCartPoint {
    IntCartPoint(int x, int y);
    explicit IntCartPoint(const CartPoint& p);

    IsoPoint toIsometric() const;
    RotPoint toRotated() const;

    int x;
    int y;
};

struct IsoPoint {
    IsoPoint(double x, double y);
    IsoPoint(const IntIsoPoint& p);

    RotPoint toRotated() const;
    CartPoint toCartesian() const;

    double x;
    double y;
};

struct IntIsoPoint {
    IntIsoPoint(int x, int y);
    explicit IntIsoPoint(const IsoPoint& p);

    RotPoint toRotated() const;
    CartPoint toCartesian() const;

    int x;
    int y;
};

struct RotPoint {
    RotPoint(double x, double y);
    RotPoint(const IntRotPoint& p);

    IsoPoint toIsometric() const;
    CartPoint toCartesian() const;

    double x;
    double y;
};

struct IntRotPoint {
    IntRotPoint(int x, int y);
    explicit IntRotPoint(const RotPoint& p);

    IsoPoint toIsometric() const;
    CartPoint toCartesian() const;

    int x;
    int y;
};

#endif  // COORDINATES_HPP_
