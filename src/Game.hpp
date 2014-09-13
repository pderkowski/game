/* Copyright 2014 <Piotr Derkowski> */

#ifndef GAME_HPP_
#define GAME_HPP_

#include "map/Map.hpp"
#include "players/Players.hpp"
#include "Subject.hpp"
#include "GameNotification.hpp"
class Settings;
class Renderer;


class Game : public Subject<GameNotification> {
public:
    explicit Game(const Settings& settings, const Renderer* renderer);
    virtual ~Game() { }

    void draw() const;


    void generateNewMap();

    void toggleFog();

    void addUnit();
    void removeSelectedUnit();

    void switchToNextPlayer();

    void setPrimarySelection(const IntIsoPoint& selectedPoint);
    void setSecondarySelection(const IntIsoPoint& selectedPoint);

private:
    virtual void notify(GameNotification::Type notificationType) const;

private:
    map::Map map_;
    players::Players players_;
};

#endif  // GAME_HPP_
