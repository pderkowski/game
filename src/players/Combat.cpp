/* Copyright 2014 <Piotr Derkowski> */

#include "Combat.hpp"
#include "Random.hpp"


namespace players {


int Combat::simulate(int attackerHp, int defenderHp) {
    int attackerChance = Random::getNumber() % attackerHp;
    int defenderChance = Random::getNumber() % defenderHp;

    return attackerChance - defenderChance;
}


}
