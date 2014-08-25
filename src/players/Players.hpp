/* Copyright 2014 <Piotr Derkowski> */

#ifndef PLAYERS_PLAYERS_HPP_
#define PLAYERS_PLAYERS_HPP_

#include <vector>
#include "units/Unit.hpp"
#include "Player.hpp"
#include "PlayersDrawer.hpp"
class MapModel;
class Renderer;

namespace players {


class Players {
public:
    Players(int numberOfPlayers, const MapModel* model, const Renderer* renderer);

    void switchToNextPlayer();

    Player* getCurrentPlayer();
    const Player* getCurrentPlayer() const;

    bool isUnitSelected() const;
    units::Unit getSelectedUnit() const;

    void setModel(const MapModel* model);

    void draw() const;

    void handleLeftClick(const sf::Event& e);
    void handleRightClick(const sf::Event& e);
    void handleAPressed();
    void handleFPressed();
    void handleDPressed();

private:
    void updateAllLayers();

    std::vector<units::Unit> getVisibleUnits() const;
    const Tile& getClickedTile(const sf::Vector2i& clickedPoint) const;

private:
    unsigned currentPlayer_;
    std::vector<Player> players_;

    const MapModel* model_;

    const Renderer* renderer_;

    PlayersDrawer drawer_;
};


}  // namespace players

#endif  // PLAYERS_PLAYERS_HPP_
