/* Copyright 2014 <Piotr Derkowski> */

#ifndef PLAYERS_PLAYER_HPP_
#define PLAYERS_PLAYER_HPP_

#include <string>
#include <vector>
#include "units/Unit.hpp"
#include "Coordinates.hpp"
#include "Tile.hpp"
#include "Fog.hpp"
class MapModel;

namespace players {


class Player {
public:
    explicit Player(const MapModel* model, const std::string& name = "");

    std::string getName() const;
    Fog getFog() const;

    bool hasUnitAtCoords(const IntRotPoint& coords) const;

    class UnitControler;
    UnitControler getUnitAtCoords(const IntRotPoint& coords);
    units::Unit getUnitAtCoords(const IntRotPoint& coords) const;

    std::vector<units::Unit> getAllUnits() const;

    void addUnit(const units::Unit& unit);

public:
    class UnitControler {
    public:
        units::Unit get() const;

        bool canMoveTo(const Tile& destination) const;
        std::vector<Tile> getPathTo(const Tile& destination) const;
        void moveTo(const Tile& destination);

    private:
        friend class Player;

        UnitControler(units::Unit* unit, Player* player);

        units::Unit* unit_;
        Player* player_;
    };

private:
    std::vector<Tile> getSurroundingTiles(const units::Unit& unit) const;

private:
    std::string name_;

    std::vector<units::Unit> units_;

    Fog fog_;
};


}  // namespace players

#endif  // PLAYERS_PLAYER_HPP_
