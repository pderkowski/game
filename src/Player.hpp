/* Copyright 2014 <Piotr Derkowski> */

#ifndef PLAYER_HPP_
#define PLAYER_HPP_

#include <string>

class Player {
public:
    Player();
    explicit Player(const std::string& name);
    std::string getName() const;

private:
    std::string name_;
};

#endif  // PLAYER_HPP_
