/* Copyright 2014 <Piotr Derkowski> */

#ifndef PLAYERS_PLAYER_HPP_
#define PLAYERS_PLAYER_HPP_

#include <vector>
#include "units/Unit.hpp"
#include "Coordinates.hpp"
#include "Tile.hpp"
#include "Fog.hpp"
#include "UnitController.hpp"
#include "Selection.hpp"
#include "PlayerDrawer.hpp"
class MapModel;

namespace players {


class Players;


class Player {
public:
    explicit Player(const Players* players, const MapModel* model, const MapRenderer* renderer);

    Player(const Player&);
    Player& operator =(const Player&) = delete;

    void draw() const;

    bool hasUnitAtCoords(const IntRotPoint& coords) const;

    UnitController getUnitAtCoords(const IntRotPoint& coords);
    units::Unit getUnitAtCoords(const IntRotPoint& coords) const;

    std::vector<units::Unit> getAllUnits() const;

    void addUnit(const units::Unit& unit);

    void startTurn();
    void endTurn();
    bool hasTurn() const;

    bool doesSeeTile(const IntRotPoint& coords) const;
    bool doesKnowTile(const IntRotPoint& coords) const;

    int getMovementPointsLeft(const units::Unit& unit) const;
    void setMovementPointsLeft(const units::Unit& unit, int pointsLeft);
    void resetMovementPoints();

    void handleLeftClick(const sf::Event& e);
    void handleRightClick(const sf::Event& e);
    void handleAPressed();
    void handleDPressed();

    void toggleFog();

public:
    friend class UnitController;
    friend class PlayerDrawer;

private:
    std::vector<const Tile*> getSurroundingTiles(const units::Unit& unit) const;

    const Tile& getClickedTile(const sf::Vector2i& clickedPoint) const;

private:
    const Players* players_;

    const MapModel* model_;

    const MapRenderer* renderer_;

    std::vector<units::Unit> units_;
    std::map<unsigned long long, int> movementPoints_;

    Fog fog_;

    Selection selection_;

    bool hasTurn_;

    bool isFogToggledOn_;

    PlayerDrawer drawer_;
};


}  // namespace players

#endif  // PLAYERS_PLAYER_HPP_
