/* Copyright 2014 <Piotr Derkowski> */

#include <map>
#include <utility>
#include <string>
#include <algorithm>
#include <stdexcept>
#include <functional>
#include <vector>
#include "Player.hpp"
#include "units/Unit.hpp"
#include "units/UnitFactory.hpp"
#include "Coordinates.hpp"
#include "map/Tile.hpp"
#include "Fog.hpp"
#include "map/MapModel.hpp"
#include "Selection.hpp"
#include "MiscellaneousEnums.hpp"
#include "units/Units.hpp"


namespace players {


Player::Player(miscellaneous::Flag flag, const map::MapModel* model, units::Units* units)
    : flag_(flag), fog_(model->getRowsNo(), model->getColumnsNo()), model_(model), units_(units)
{ }

bool Player::isUnitSelected() const {
    if (selection_.isSourceSelected()) {
        return !units_->select().playerEqual(this).tileEqual(selection_.getSource()).empty();
    } else {
        return false;
    }
}

void Player::addUnit(const units::Unit& unit) {
    units_->add(unit);

    fog_.addVisible(getSurroundingTiles(unit));
}

UnitController Player::getSelectedUnit() {
    if (isUnitSelected()) {
        units::Unit* unit = &units_->select().playerEqual(this).tileEqual(selection_.getSource())[0];
        return UnitController(unit, this);
    } else {
        throw std::logic_error("There is no unit at the requested coords.");
    }
}

units::Unit Player::getSelectedUnit() const {
    if (isUnitSelected()) {
        return units_->select().playerEqual(this).tileEqual(selection_.getSource())[0];
    } else {
        throw std::logic_error("There is no unit at the requested coords.");
    }
}

bool Player::hasUnitAtTile(const map::Tile& tile) const {
    return !units_->select().playerEqual(this).tileEqual(tile).empty();
}

UnitController Player::getUnitAtTile(const map::Tile& tile) {
    return UnitController(&units_->select().playerEqual(this).tileEqual(tile)[0], this);
}

Fog Player::getFog() const {
    return fog_;
}

Selection Player::getSelection() const {
    return selection_;
}

miscellaneous::Flag Player::getFlag() const {
    return flag_;
}


bool Player::doesSeeTile(const IntRotPoint& coords) const {
    IntIsoPoint isoCoords(coords.toIsometric());
    return fog_(isoCoords.y, isoCoords.x) == TileVisibility::VisibleKnown;
}

bool Player::doesKnowTile(const IntRotPoint& coords) const {
    IntIsoPoint isoCoords(coords.toIsometric());
    return (fog_(isoCoords.y, isoCoords.x) == TileVisibility::VisibleKnown)
        || (fog_(isoCoords.y, isoCoords.x) == TileVisibility::UnvisibleKnown);
}

void Player::setModel(const map::MapModel* model) {
    model_ = model;
    fog_.clear();
    selection_.clear();
}

void Player::resetMoves() {
    for (units::Unit& unit : units_->select().playerEqual(this)) {
        unit.resetMoves();
    }
}

std::vector<const map::Tile*> Player::getSurroundingTiles(const units::Unit& unit) const {
    map::Tile position = unit.getPosition();
    return position.getTilesInRadius(2);
}

void Player::handleLeftClick(const map::Tile& clickedTile) {
    selection_.clear();
    selection_.setSource(clickedTile);
}

void Player::handleAPressed() {
    if (selection_.isSourceSelected()) {
        if (selection_.getSource().type == tileenums::Type::Water) {
            addUnit(units::UnitFactory::createTrireme(selection_.getSource().coords, model_, this));
        } else {
            addUnit(units::UnitFactory::createPhalanx(selection_.getSource().coords, model_, this));
        }
    }
}

void Player::handleRightClick(const map::Tile& clickedTile) {
    if (isUnitSelected()) {
        auto destination = clickedTile;

        UnitController unit = getSelectedUnit();
        if (unit.canMoveTo(destination)) {
            if (selection_.isDestinationConfirmed(destination)) {
                unit.moveTo(destination);

                selection_.setSource(unit.get()->getPosition());
                selection_.setPath(unit.getPathTo(destination));
            } else {
                selection_.setDestination(destination);
                selection_.setPath(unit.getPathTo(destination));
            }
        }
    }
}

void Player::handleDPressed() {
    if (isUnitSelected()) {
        UnitController unit = getSelectedUnit();
        unit.destroyUnit();

        selection_.clear();
    }
}

void Player::handleFPressed() {
    fog_.toggle();
}


}  // namespace players
