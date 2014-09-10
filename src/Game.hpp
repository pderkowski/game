/* Copyright 2014 <Piotr Derkowski> */

#ifndef GAME_HPP_
#define GAME_HPP_

#include <memory>
#include <vector>
#include "SFML/Graphics.hpp"
#include "map/Map.hpp"
#include "menu/Menu.hpp"
#include "players/Players.hpp"
#include "interface/Interface.hpp"
#include "Timer.hpp"
#include "Renderer.hpp"


class Game {
public:
    Game(int rows, int columns);

    void start();

    void restart();
    void quit();
    void toggleMenu();
    void captureScreenToFile();

    void addUnit();
    void toggleFog();
    void deleteSelectedUnit();
    void switchToNextPlayer();

    void scrollView();
    void zoomView(float delta);

private:
    void handleEvents();
    void handleTimers();

    void handleLeftClick(const sf::Event& event);
    void handleRightClick(const sf::Event& event);
    void handleMouseMoved(const sf::Event& event);

private:
    unsigned numberOfPlayers_;

    std::shared_ptr<sf::RenderWindow> window_;
    Renderer renderer_;

    map::Map map_;
    players::Players players_;
    interface::Interface interface_;
    menu::Menu menu_;

    std::vector<Timer> timers_;
};

#endif  // GAME_HPP_
