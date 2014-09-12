/* Copyright 2014 <Piotr Derkowski> */

#include <vector>
#include "units/Unit.hpp"
#include "units/Units.hpp"
#include "Player.hpp"
#include "Players.hpp"
#include "PlayersDrawer.hpp"
#include "map/MapModel.hpp"
#include "Renderer.hpp"
#include "MiscellaneousEnums.hpp"
#include "Combat.hpp"
#include "Action.hpp"


namespace players {


Players::Players(int numberOfPlayers, const map::MapModel* model, const Renderer* renderer)
    : currentPlayer_(0), drawer_(renderer)
{
    std::vector<miscellaneous::Flag> flags = { miscellaneous::Flag::Blue, miscellaneous::Flag::Red };

    for (int i = 0; i < numberOfPlayers; ++i) {
        players_.emplace_back(flags[i], model, &units_);
        players_[i].addObserver(this);
    }

    addObserver(&drawer_);
    notify(PlayerSwitched);
}

void Players::switchToNextPlayer() {
    currentPlayer_ = (currentPlayer_ + 1) % players_.size();
    getCurrentPlayer()->resetMoves();

    notify(PlayerSwitched);
}

Player* Players::getCurrentPlayer() {
    return &players_[currentPlayer_];
}

const Player* Players::getCurrentPlayer() const {
    return &players_[currentPlayer_];
}

bool Players::isUnitSelected() const {
    if (getCurrentPlayer()->getSelection().isSourceSelected()) {
        const IntRotPoint coords = getCurrentPlayer()->getSelection().getSource().coords;

        std::vector<units::Unit> visibleUnits = getVisibleUnits();
        return std::any_of(visibleUnits.begin(), visibleUnits.end(),
            [&coords] (const units::Unit& unit) {
                return unit.getCoords() == coords;
            }
        );
    } else {
        return false;
    }
}

units::Unit Players::getSelectedUnit() const {
    const IntRotPoint coords = getCurrentPlayer()->getSelection().getSource().coords;

    std::vector<units::Unit> visibleUnits = getVisibleUnits();
    auto unitIt = std::find_if(visibleUnits.begin(), visibleUnits.end(),
        [&coords] (const units::Unit& unit) {
            return unit.getCoords() == coords;
        }
    );

    if (unitIt != visibleUnits.end()) {
        return *unitIt;
    } else {
        throw std::logic_error("There is no unit at the requested coords.");
    }
}

std::vector<units::Unit> Players::getVisibleUnits() const {
    std::vector<units::Unit> res;

    for (const Player& player : players_) {
        auto playerUnits = units_.select().playerEqual(&player);

        for (auto& unit : playerUnits) {
            if (getCurrentPlayer()->doesSeeTile(unit.getPosition().coords)) {
                res.push_back(unit);
            }
        }
    }

    return res;
}

void Players::setModel(const map::MapModel* model) {
    for (auto& player : players_) {
        player.setModel(model);
    }

    units_.clear();

    notify(NewMapCreated);
}

void Players::draw() const {
    drawer_.draw();
}


void Players::handleLeftClick(const map::Tile& clickedTile) {
    getCurrentPlayer()->setPrimarySelection(clickedTile);
}

void Players::handleRightClick(const map::Tile& clickedTile) {
    getCurrentPlayer()->handleRightClick(clickedTile);
}

void Players::handleAPressed() {
    getCurrentPlayer()->handleAPressed();
}

void Players::handleFPressed() {
    getCurrentPlayer()->toggleFog();
}

void Players::handleDPressed() {
    getCurrentPlayer()->handleDPressed();
}

void Players::notify(ActionType action) const {
    Subject::notify(ActionNotification{ action, getVisibleUnits(),
        getCurrentPlayer()->getSelection(),
        getCurrentPlayer()->getFog() });
}

void Players::onNotify(const ActionType& ntion) {
    notify(ntion);
}


}  // namespace players
