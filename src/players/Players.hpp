/* Copyright 2014 <Piotr Derkowski> */

#ifndef PLAYERS_PLAYERS_HPP_
#define PLAYERS_PLAYERS_HPP_

#include <vector>
#include <memory>
#include "Player.hpp"
#include "PlayersDrawer.hpp"
#include "MapRenderer.hpp"
#include "Selection.hpp"
#include "Tile.hpp"
#include "units/Unit.hpp"
class MapModel;


namespace players {


class Players {
public:
    Players(int numberOfPlayers, const MapModel* model, const MapRenderer* renderer);

    void switchToNextPlayer();
    Player* getCurrentPlayer();

    void draw() const;

    std::vector<units::Unit> getAllUnits() const;

    void handleLeftClick(const sf::Event& e);
    void handleRightClick(const sf::Event& e);
    void handleAPressed();

private:
    std::shared_ptr<const Tile> getClickedTile(const sf::Vector2i& clickedPoint);

    bool isDestinationConfirmed(const Tile& destination) const;

private:
    unsigned currentPlayer_;
    std::vector<Player> players_;

    Selection selection_;

    const MapModel* model_;

    const MapRenderer* renderer_;
    PlayersDrawer drawer_;
};


}  // namespace players

#endif  // PLAYERS_PLAYERS_HPP_
