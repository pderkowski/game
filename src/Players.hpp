/* Copyright 2014 <Piotr Derkowski> */

#ifndef PLAYERS_HPP_
#define PLAYERS_HPP_

#include <vector>
#include "Player.hpp"

class Players {
public:
    explicit Players(int numberOfPlayers);
    void switchToNextPlayer();
    Player* getCurrentPlayer();

private:
    unsigned currentPlayer_;
    std::vector<Player> players_;
};

#endif  // PLAYERS_HPP_
