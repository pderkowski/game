/* Copyright 2014 <Piotr Derkowski> */

#ifndef GAME_HPP_
#define GAME_HPP_

#include <memory>
#include <vector>
#include "SFML/Graphics.hpp"
#include "Map.hpp"
#include "menu/Menu.hpp"
#include "players/Players.hpp"
#include "Minimap.hpp"
#include "Interface.hpp"
#include "Timer.hpp"
#include "Renderer.hpp"
#include "UnitFrame.hpp"


class Game {
public:
    Game(int rows, int columns, int numberOfPlayers);

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
    std::shared_ptr<sf::RenderWindow> window_;
    Renderer renderer_;

    Map map_;
    players::Players players_;
    Minimap minimap_;
    Interface interface_;
    menu::Menu menu_;
    UnitFrame unitFrame_;

    std::vector<Timer> timers_;
};

#endif  // GAME_HPP_
