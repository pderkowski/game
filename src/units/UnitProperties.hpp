/* Copyright 2014 <Piotr Derkowski> */

#ifndef UNITS_UNITPROPERTIES_HPP_
#define UNITS_UNITPROPERTIES_HPP_

#include <string>


namespace units {


enum class Type {
    Phalanx,
    Trireme
};

struct UnitProperties {
    std::string name;
    Type type;
    int baseHp;
    int hpLeft;
    int baseMoves;
    int movesLeft;
};


bool operator ==(const UnitProperties& lhs, const UnitProperties& rhs);

}


#endif  // UNITS_UNITPROPERTIES_HPP_
