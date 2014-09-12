/* Copyright 2014 <Piotr Derkowski> */

#ifndef PLAYERS_ACTION_HPP_
#define PLAYERS_ACTION_HPP_

#include <vector>
#include "units/Unit.hpp"
#include "Selection.hpp"
#include "Fog.hpp"


namespace players {


enum ActionType {
    PlayerSwitched,
    NewMapCreated,
    PrimarySelectionSet,
    SecondarySelectionSet,
    UnitMoved,
    UnitAdded,
    UnitRemoved,
    FogToggled
};


struct ActionNotification {
    ActionType type;

    std::vector<units::Unit> units;
    Selection selection;
    Fog fog;
};


}  // namespace players;

#endif  // PLAYERS_ACTION_HPP_
