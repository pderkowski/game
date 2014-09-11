/* Copyright 2014 <Piotr Derkowski> */

#ifndef APPLICATION_HPP_
#define APPLICATION_HPP_

#include <vector>
#include <memory>
#include "SFML/Graphics.hpp"
#include "Game.hpp"
#include "interface/Interface.hpp"
#include "menu/Menu.hpp"
#include "Timer.hpp"
#include "Renderer.hpp"
class Settings;
class IntIsoPoint;


class Application {
public:
    explicit Application(const Settings& settings);

    void run();
    void restart();
    void quit();

    void toggleMenu();

    void captureScreenToFile();

private:
    void addUnit();
    void deleteSelectedUnit();

    void switchToNextPlayer();

    void toggleFog();

    void scrollView();
    void zoomView(float delta);

    void handleMouseMoved(const sf::Event& event);

    void handleLeftClick(const sf::Event& event);
    void handleRightClick(const sf::Event& event);

    void handleEvents();
    void handleTimers();

    IntIsoPoint getClickedMapCoords(const sf::Event& event) const;

private:
    std::shared_ptr<sf::RenderWindow> window_;
    Renderer renderer_;

    Game game_;
    interface::Interface interface_;
    menu::Menu menu_;

    std::vector<Timer> timers_;
};


#endif  // APPLICATION_HPP_
