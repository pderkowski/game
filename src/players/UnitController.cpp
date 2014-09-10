/* Copyright 2014 <Piotr Derkowski> */

#include <iostream>
#include <vector>
#include "units/Unit.hpp"
#include "units/MovingCosts.hpp"
#include "map/Tile.hpp"
#include "Player.hpp"
#include "Pathfinder.hpp"
#include "UnitController.hpp"
#include "units/Units.hpp"


namespace players {


UnitController::UnitController(units::Unit* unit, Player* player)
    : unit_(unit), player_(player)
{ }

units::Unit* UnitController::get() {
    return unit_;
}

bool UnitController::canMoveTo(const map::Tile& destination) const {
    Pathfinder pathfinder(units::getMovingCosts(unit_->getType()), player_->fog_);
    return pathfinder.doesPathExist(unit_->getPosition(), destination);
}

std::vector<map::Tile> UnitController::getPathTo(const map::Tile& destination) const {
    Pathfinder pathfinder(units::getMovingCosts(unit_->getType()), player_->fog_);
    return pathfinder.findPath(unit_->getPosition(), destination);
}

void UnitController::moveTo(const map::Tile& destination) {
    auto path = getPathTo(destination);

    for (size_t i = 0; i + 1 < path.size() && unit_->getMovesLeft() > 0; ++i) {
        player_->fog_.removeVisible(player_->getSurroundingTiles(*unit_));

        auto direction = path[i].getDirection(path[i + 1]);
        unit_->moveTo(direction);

        player_->fog_.addVisible(player_->getSurroundingTiles(*unit_));

        std::map<tileenums::Type, unsigned> movingCosts = units::getMovingCosts(unit_->getType());
        unsigned cost = movingCosts.at(path[i + 1].type);

        unit_->setMovesLeft(unit_->getMovesLeft() - cost);
    }
}

void UnitController::destroyUnit() {
    player_->fog_.removeVisible(player_->getSurroundingTiles(*unit_));

    player_->units_->remove(*unit_);

    unit_ = nullptr;
}


}  // namespace players
