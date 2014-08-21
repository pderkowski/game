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
class MapModel;

namespace players {


class Players;


class Player {
public:
    explicit Player(const Players* players, const MapModel* model);

    Player(const Player&);
    Player& operator =(const Player&) = delete;

    bool hasUnitAtCoords(const IntRotPoint& coords) const;

    UnitController getUnitAtCoords(const IntRotPoint& coords);
    units::Unit getUnitAtCoords(const IntRotPoint& coords) const;

    std::vector<units::Unit> getUnits() const;
    Fog getFog() const;
    Selection getSelection() const;

    void addUnit(const units::Unit& unit);

    bool doesSeeTile(const IntRotPoint& coords) const;
    bool doesKnowTile(const IntRotPoint& coords) const;

    int getMovementPointsLeft(const units::Unit& unit) const;
    void setMovementPointsLeft(const units::Unit& unit, int pointsLeft);
    void resetMovementPoints();

    void handleLeftClick(const Tile& tile);
    void handleRightClick(const Tile& tile);
    void handleAPressed();
    void handleDPressed();
    void handleFPressed();

public:
    friend class UnitController;

private:
    std::vector<const Tile*> getSurroundingTiles(const units::Unit& unit) const;

private:
    const Players* players_;

    const MapModel* model_;

    std::vector<units::Unit> units_;
    std::map<unsigned long long, int> movementPoints_;

    Fog fog_;

    Selection selection_;
};


}  // namespace players

#endif  // PLAYERS_PLAYER_HPP_
