/* Copyright 2014 <Piotr Derkowski> */

#ifndef PLAYERS_HPP_
#define PLAYERS_HPP_

#include <vector>
#include <memory>
#include "Player.hpp"
#include "PlayersDrawer.hpp"
#include "MapRenderer.hpp"

class Players {
public:
    Players(int numberOfPlayers, const MapRenderer* renderer);

    void switchToNextPlayer();
    Player* getCurrentPlayer();

    void draw() const;

    std::vector<const units::Unit*> getAllUnits() const;

private:
    unsigned currentPlayer_;
    std::vector<Player> players_;

    PlayersDrawer drawer_;
};

#endif  // PLAYERS_HPP_
