/* Copyright 2014 <Piotr Derkowski> */

#ifndef ATTRIBUTES_HPP_
#define ATTRIBUTES_HPP_

#include "Attribute.hpp"
#include "TileEnums.hpp"

class Attributes {
private:
    class River {
    public:
        River();

        void addDirection(tileenums::Direction direction);
        void resetDirections();
        bool hasDirection(tileenums::Direction direction) const;

    private:
        int directions_;
    };

public:
    Attribute<River> river;
};

#endif  // ATTRIBUTES_HPP_
