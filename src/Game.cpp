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
}

void Game::addUnit() {
    players_.handleAPressed();
}

void Game::toggleFog() {
    players_.handleFPressed();
}

void Game::deleteSelectedUnit() {
    players_.handleDPressed();
}

void Game::switchToNextPlayer() {
    players_.switchToNextPlayer();
}

const map::MapModel* Game::getMapModel() const {
    return map_.getModel();
}

const players::Players* Game::getPlayers() const {
    return &players_;
}

void Game::setPrimarySelection(const IntIsoPoint& selectedPoint) {
    players_.handleLeftClick(getMapModel()->getTile(selectedPoint));
}

void Game::setSecondarySelection(const IntIsoPoint& selectedPoint) {
    players_.handleRightClick(getMapModel()->getTile(selectedPoint));
}
