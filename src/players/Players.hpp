/* Copyright 2014 <Piotr Derkowski> */

#ifndef PLAYERS_PLAYERS_HPP_
#define PLAYERS_PLAYERS_HPP_

#include <vector>
#include "units/Unit.hpp"
#include "Player.hpp"
class MapModel;
class MapRenderer;

namespace players {


class Players {
public:
    Players(int numberOfPlayers, const MapModel* model, const MapRenderer* renderer);

    void switchToNextPlayer();

    Player* getCurrentPlayer();
    const Player* getCurrentPlayer() const;

    std::vector<units::Unit> getVisibleUnits() const;

    void draw() const;

    void handleLeftClick(const sf::Event& e);
    void handleRightClick(const sf::Event& e);
    void handleAPressed();
    void handleFPressed();
    void handleDPressed();

private:
    unsigned currentPlayer_;
    std::vector<Player> players_;
};


}  // namespace players

#endif  // PLAYERS_PLAYERS_HPP_
