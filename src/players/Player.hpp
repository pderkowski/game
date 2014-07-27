/* Copyright 2014 <Piotr Derkowski> */

#ifndef PLAYERS_PLAYER_HPP_
#define PLAYERS_PLAYER_HPP_

#include <string>
#include <vector>
#include "units/Unit.hpp"
#include "Coordinates.hpp"
#include "Tile.hpp"
#include "Fog.hpp"
#include "UnitController.hpp"
class MapModel;

namespace players {


class Player {
public:
    explicit Player(const MapModel* model, const std::string& name = "");

    Player(const Player&) = delete;
    Player& operator =(const Player&) = delete;

    Player(Player&&) = default;
    Player& operator =(Player&&) = default;

    std::string getName() const;
    Fog getFog() const;

    bool hasUnitAtCoords(const IntRotPoint& coords) const;

    UnitController getUnitAtCoords(const IntRotPoint& coords);
    units::Unit getUnitAtCoords(const IntRotPoint& coords) const;

    std::vector<units::Unit> getAllUnits() const;

    void addUnit(const units::Unit& unit);

    int getMovementPointsLeft(const units::Unit& unit) const;
    void setMovementPointsLeft(const units::Unit& unit, int pointsLeft);
    void resetMovementPoints();

public:
    friend class UnitController;

private:
    std::vector<const Tile*> getSurroundingTiles(const units::Unit& unit) const;

private:
    std::string name_;

    std::vector<units::Unit> units_;
    std::map<unsigned long long, int> movementPoints_;

    Fog fog_;
};


}  // namespace players

#endif  // PLAYERS_PLAYER_HPP_
