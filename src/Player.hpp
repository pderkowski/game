/* Copyright 2014 <Piotr Derkowski> */

#ifndef PLAYER_HPP_
#define PLAYER_HPP_

#include <string>
#include <vector>
#include "units/Unit.hpp"

class Player {
public:
    Player();
    explicit Player(const std::string& name);
    std::string getName() const;

private:
    std::string name_;

    std::vector<units::Unit> units_;
};

#endif  // PLAYER_HPP_
