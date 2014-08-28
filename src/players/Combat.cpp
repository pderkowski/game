/* Copyright 2014 <Piotr Derkowski> */

#include "Combat.hpp"
#include "global/Random.hpp"


namespace players {


int Combat::simulate(int attackerHp, int defenderHp) {
    int attackerChance = global::Random::getNumber() % attackerHp;
    int defenderChance = global::Random::getNumber() % defenderHp;

    return attackerChance - defenderChance;
}


}
