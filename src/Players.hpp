/* Copyright 2014 <Piotr Derkowski> */

#ifndef PLAYERS_HPP_
#define PLAYERS_HPP_

#include <vector>
#include <memory>
#include "Player.hpp"
#include "PlayersDrawer.hpp"
#include "MapRenderer.hpp"
#include "Selection.hpp"
class MapModel;

class Players {
public:
    Players(int numberOfPlayers, const MapModel* model, const MapRenderer* renderer);

    void switchToNextPlayer();
    Player* getCurrentPlayer();

    void draw() const;

    std::vector<const units::Unit*> getAllUnits() const;

    void handleLeftClick(const sf::Event& e);

private:
    unsigned currentPlayer_;
    std::vector<Player> players_;

    Selection selection_;

    const MapModel* model_;

    const MapRenderer* renderer_;
    PlayersDrawer drawer_;
};

#endif  // PLAYERS_HPP_
