/* Copyright 2014 <Piotr Derkowski> */

#include <vector>
#include "units/Unit.hpp"
#include "units/Units.hpp"
#include "Player.hpp"
#include "Players.hpp"
#include "PlayersDrawer.hpp"
#include "MapModel.hpp"
#include "Renderer.hpp"
#include "MiscellaneousEnums.hpp"
#include "Combat.hpp"

namespace players {


Players::Players(int numberOfPlayers, const MapModel* model, const Renderer* renderer)
    : currentPlayer_(0), model_(model), renderer_(renderer), drawer_(renderer)
{
    std::vector<miscellaneous::Flag> flags = { miscellaneous::Flag::Blue, miscellaneous::Flag::Red };

    for (int i = 1; i <= numberOfPlayers; ++i) {
        players_.emplace_back(flags[i - 1], model, &units_);
    }

    updateAllLayers();
}

void Players::switchToNextPlayer() {
    currentPlayer_ = (currentPlayer_ + 1) % players_.size();
    getCurrentPlayer()->resetMoves();

    updateAllLayers();
}

Player* Players::getCurrentPlayer() {
    return &players_[currentPlayer_];
}

Player* Players::getOtherPlayer() {
    return &players_[(currentPlayer_ + 1) % 2];
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

void Players::setModel(const MapModel* model) {
    for (auto& player : players_) {
        player.setModel(model);
    }

    units_.clear();

    updateAllLayers();
}

void Players::draw() const {
    drawer_.draw();
}


void Players::handleLeftClick(const sf::Event& e) {
    getCurrentPlayer()->handleLeftClick(getClickedTile(sf::Vector2i(e.mouseButton.x, e.mouseButton.y)));

    drawer_.updatePathLayer(getCurrentPlayer()->getSelection());
    drawer_.updateSelectionLayer(getCurrentPlayer()->getSelection());
}

void Players::handleRightClick(const sf::Event& e) {
    getCurrentPlayer()->handleRightClick(getClickedTile(sf::Vector2i(e.mouseButton.x, e.mouseButton.y)));

    if (getCurrentPlayer()->isUnitSelected()) {
        Tile selectedTile = getCurrentPlayer()->getSelectedUnit().get()->getPosition();

        if (getOtherPlayer()->hasUnitAtTile(selectedTile)) {
            UnitController attacker = getCurrentPlayer()->getSelectedUnit();
            UnitController defender = getOtherPlayer()->getUnitAtTile(selectedTile);

            int outcome = Combat::simulate(attacker.get()->getHpLeft(), defender.get()->getHpLeft());

            if (outcome > 0) {
                defender.destroyUnit();
                attacker.get()->setHpLeft(outcome);
            } else if (outcome == 0) {
                attacker.destroyUnit();
                defender.get()->setHpLeft(1);
            } else {
                attacker.destroyUnit();
                defender.get()->setHpLeft(-outcome);
            }
        }
    }

    updateAllLayers();
}

void Players::handleAPressed() {
    getCurrentPlayer()->handleAPressed();

    drawer_.updateFlagLayer(getVisibleUnits());
    drawer_.updateUnitLayer(getVisibleUnits());
    drawer_.updateFogLayer(getCurrentPlayer()->getFog());
}

void Players::handleFPressed() {
    getCurrentPlayer()->handleFPressed();

    drawer_.updateFogLayer(getCurrentPlayer()->getFog());
    drawer_.updateFlagLayer(getVisibleUnits());
    drawer_.updateUnitLayer(getVisibleUnits());
}

void Players::handleDPressed() {
    getCurrentPlayer()->handleDPressed();

    updateAllLayers();
}

const Tile& Players::getClickedTile(const sf::Vector2i& clickedPoint) const {
    IntIsoPoint clickedCoords = renderer_->getMapCoords(clickedPoint);
    return model_->getTile(clickedCoords);
}

void Players::updateAllLayers() {
    drawer_.updateFogLayer(getCurrentPlayer()->getFog());
    drawer_.updateFlagLayer(getVisibleUnits());
    drawer_.updateUnitLayer(getVisibleUnits());
    drawer_.updateSelectionLayer(getCurrentPlayer()->getSelection());
    drawer_.updatePathLayer(getCurrentPlayer()->getSelection());
}


}  // namespace players
