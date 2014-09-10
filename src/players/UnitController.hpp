/* Copyright 2014 <Piotr Derkowski> */

#ifndef PLAYERS_UNITCONTROLLER_HPP_
#define PLAYERS_UNITCONTROLLER_HPP_

#include <vector>
#include "units/Unit.hpp"
#include "map/Tile.hpp"


namespace players {


class Player;


class UnitController {
public:
    UnitController(units::Unit* unit, Player* player);

    units::Unit* get();

    bool canMoveTo(const map::Tile& destination) const;
    std::vector<map::Tile> getPathTo(const map::Tile& destination) const;
    void moveTo(const map::Tile& destination);

    void destroyUnit();

private:
    units::Unit* unit_;
    Player* player_;
};


}  // namespace players


#endif  // PLAYERS_UNITCONTROLLER_HPP_
