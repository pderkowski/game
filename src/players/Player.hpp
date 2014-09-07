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
#include "MiscellaneousEnums.hpp"
class MapModel;
namespace units { class Units; }



namespace players {


class Player {
public:
    Player(miscellaneous::Flag flag, const MapModel* model, units::Units* units);

    bool isUnitSelected() const;

    UnitController getSelectedUnit();
    units::Unit getSelectedUnit() const;

    bool hasUnitAtTile(const Tile& tile) const;
    UnitController getUnitAtTile(const Tile& tile);

    Fog getFog() const;
    Selection getSelection() const;
    miscellaneous::Flag getFlag() const;

    void addUnit(const units::Unit& unit);

    bool doesSeeTile(const IntRotPoint& coords) const;
    bool doesKnowTile(const IntRotPoint& coords) const;

    void setModel(const MapModel* model);

    void resetMoves();

    void handleLeftClick(const Tile& clickedTile);
    void handleRightClick(const Tile& clickedTile);
    void handleAPressed();
    void handleDPressed();
    void handleFPressed();

public:
    friend class UnitController;

private:
    std::vector<const Tile*> getSurroundingTiles(const units::Unit& unit) const;

private:
    miscellaneous::Flag flag_;

    Fog fog_;

    Selection selection_;

    const MapModel* model_;

    units::Units* units_;
};


}  // namespace players

#endif  // PLAYERS_PLAYER_HPP_
