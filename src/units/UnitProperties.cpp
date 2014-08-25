/* Copyright 2014 <Piotr Derkowski> */

#include <string>
#include "UnitProperties.hpp"


namespace units {


bool operator ==(const UnitProperties& lhs, const UnitProperties& rhs) {
    return (lhs.name == rhs.name) && (lhs.type == rhs.type) && (lhs.baseHP == rhs.baseHP)
        && (lhs.hpLeft == rhs.hpLeft) && (lhs.baseMoves == rhs.baseMoves)
        && (lhs.movesLeft == rhs.movesLeft);
}


}

