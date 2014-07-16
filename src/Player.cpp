/* Copyright 2014 <Piotr Derkowski> */

#include <string>
#include "Player.hpp"

Player::Player()
    : name_()
{ }

Player::Player(const std::string& name)
    : name_(name)
{ }

std::string Player::getName() const {
    return name_;
}
