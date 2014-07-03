/* Copyright 2014 <Piotr Derkowski> */

#ifndef ATTRIBUTES_HPP_
#define ATTRIBUTES_HPP_

#include "Attribute.hpp"

class Attributes {
public:
    enum RiverDirection {
        Top = 1 << 0,
        Right = 1 << 1,
        Bottom = 1 << 2,
        Left = 1 << 3
    };

private:
    class River {
    public:
        River();

        void addDirection(RiverDirection direction);
        void resetDirections();
        bool hasDirection(RiverDirection direction) const;

    private:
        int directions_;
    };

public:
    Attribute<River> river;
};

#endif  // ATTRIBUTES_HPP_
