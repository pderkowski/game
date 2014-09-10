/* Copyright 2014 <Piotr Derkowski> */

#ifndef MAP_ATTRIBUTES_HPP_
#define MAP_ATTRIBUTES_HPP_

#include "Attribute.hpp"
#include "TileEnums.hpp"


namespace map {


class Attributes {
private:
    class River {
    public:
        River();

        void addDirection(tileenums::Direction direction);
        void resetDirections();
        bool hasDirection(tileenums::Direction direction) const;

        bool operator == (const Attributes::River& rhs) const;

    private:
        int directions_;
    };

public:
    bool operator == (const Attributes& rhs) const;

    Attribute<River> river;
};


}  // namespace map

#endif  // MAP_ATTRIBUTES_HPP_
