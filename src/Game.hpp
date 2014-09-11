/* Copyright 2014 <Piotr Derkowski> */

#ifndef GAME_HPP_
#define GAME_HPP_

#include "map/Map.hpp"
#include "players/Players.hpp"
class Settings;
class Renderer;
namespace map { class MapModel; }
class IntIsoPoint;

class Game {
public:
    explicit Game(const Settings& settings, const Renderer* renderer);

    void draw() const;

    void generateNewMap();

    void toggleFog();

    void addUnit();
    void deleteSelectedUnit();

    void switchToNextPlayer();

    void setPrimarySelection(const IntIsoPoint& selectedPoint);
    void setSecondarySelection(const IntIsoPoint& selectedPoint);

    const map::MapModel* getMapModel() const;
    const players::Players* getPlayers() const;

private:
    map::Map map_;
    players::Players players_;
};

#endif  // GAME_HPP_
