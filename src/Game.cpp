/* Copyright 2014 <Piotr Derkowski> */

#include "map/Map.hpp"
#include "Game.hpp"
#include "players/Players.hpp"
#include "Settings.hpp"
#include "map/MapModel.hpp"
#include "map/Tile.hpp"
class Renderer;


Game::Game(const Settings& settings, const Renderer* renderer)
    : map_(settings.rows, settings.columns, renderer),
    players_(2, map_.getModel(), renderer)
{ }

void Game::draw() const {
    map_.draw();
    players_.draw();
}

void Game::generateNewMap() {
    map_.generateMap();
    players_.setModel(map_.getModel());
    notify(GameNotification::NewMapGenerated);
}

void Game::addUnit() {
    players_.handleAPressed();
    notify(GameNotification::UnitAdded);
}

void Game::toggleFog() {
    players_.handleFPressed();
    notify(GameNotification::FogToggled);
}

void Game::removeSelectedUnit() {
    players_.handleDPressed();
    notify(GameNotification::UnitRemoved);
}

void Game::switchToNextPlayer() {
    players_.switchToNextPlayer();
    notify(GameNotification::PlayerSwitched);
}

void Game::setPrimarySelection(const IntIsoPoint& selectedPoint) {
    players_.handleLeftClick(map_.getModel()->getTile(selectedPoint));
    notify(GameNotification::PrimarySelectionSet);
}

void Game::setSecondarySelection(const IntIsoPoint& selectedPoint) {
    players_.handleRightClick(map_.getModel()->getTile(selectedPoint));
    notify(GameNotification::SecondarySelectionSet);
}

void Game::notify(GameNotification::Type ntionType) const {
    Subject::notify(GameNotification{ ntionType, map_.getModel(), players_.getCurrentPlayer() });
}
