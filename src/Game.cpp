/* Copyright 2014 <Piotr Derkowski> */

#include <cstdlib>
#include <memory>
#include <string>
#include "Map.hpp"
#include "menu/Menu.hpp"
#include "Game.hpp"
#include "TileEnums.hpp"
#include "players/Players.hpp"
#include "Renderer.hpp"
#include "interface/Interface.hpp"
#include "Timer.hpp"
#include "SFML/Graphics/Color.hpp"


Game::Game(int rows, int columns)
    : numberOfPlayers_(2),
    window_(std::make_shared<sf::RenderWindow>(
        sf::VideoMode::getFullscreenModes()[0],
        "",
        sf::Style::Fullscreen)),
    renderer_(rows, columns, 96, 48, window_),
    map_(rows, columns, &renderer_),
    players_(numberOfPlayers_, map_.getModel(), &renderer_),
    interface_(map_.getModel(), &players_, &renderer_),
    menu_(window_)
{
    menu_.addItem("Return", [this] () { toggleMenu(); });
    menu_.addItem("New game", [this] () { restart(); });
    menu_.addItem("Quit game", [this] () { quit(); });

    timers_.push_back(Timer(50, [this] () { scrollView(); }));
}

void Game::start() {
    while (window_->isOpen()) {
        handleEvents();
        handleTimers();

        window_->clear();
        map_.draw();
        players_.draw();
        interface_.draw();
        if (menu_.isVisible()) {
            menu_.draw();
        }
        window_->display();
    }
}

void Game::restart() {
    map_.generateMap();
    players_.setModel(map_.getModel());
    interface_.setModel(map_.getModel());
}

void Game::quit() {
    exit(EXIT_SUCCESS);
}

void Game::toggleMenu() {
    menu_.toggleVisibility();
}

void Game::handleEvents() {
    sf::Event event;
    while (window_->pollEvent(event)) {
        if (event.type == sf::Event::Closed) {
            window_->close();
        } else if (event.type == sf::Event::MouseButtonPressed) {
            if (event.mouseButton.button == sf::Mouse::Button::Left) {
                handleLeftClick(event);
            } else if (event.mouseButton.button == sf::Mouse::Button::Right) {
                handleRightClick(event);
            }
        } else if (event.type == sf::Event::KeyPressed) {
            switch (event.key.code) {
            case sf::Keyboard::Key::Space:
                restart();
                break;
            case sf::Keyboard::Key::Escape:
                quit();
                break;
            case sf::Keyboard::Key::M:
                toggleMenu();
                break;
            case sf::Keyboard::Key::A:
                addUnit();
                break;
            case sf::Keyboard::Key::F:
                toggleFog();
                break;
            case sf::Keyboard::Key::D:
                deleteSelectedUnit();
                break;
            case sf::Keyboard::Key::Return:
                switchToNextPlayer();
                break;
            case sf::Keyboard::Key::P:
                captureScreenToFile();
                break;
            default:
                break;
            }
        } else if (event.type == sf::Event::MouseWheelMoved) {
            zoomView(event.mouseWheel.delta);
        } else if (event.type == sf::Event::MouseMoved) {
            handleMouseMoved(event);
        }
    }
}

void Game::handleTimers() {
    for (auto& timer : timers_) {
        if (timer.elapsed()) {
            timer.executeCallback();
        }
    }
}

void Game::handleLeftClick(const sf::Event& event) {
    if (menu_.isVisible()) {
        menu_.handleLeftClick(event);
    } else {
        players_.handleLeftClick(event);
        interface_.updateSelectedUnitFrame();
    }
}

void Game::handleRightClick(const sf::Event& event) {
    if (!menu_.isVisible()) {
        players_.handleRightClick(event);
        interface_.updateMinimapBackground();
        interface_.updateSelectedUnitFrame();
    }
}

void Game::handleMouseMoved(const sf::Event& event) {
    if (menu_.isVisible()) {
        menu_.handleMouseMoved(event);
    }
}

void Game::addUnit() {
    if (!menu_.isVisible()) {
        players_.handleAPressed();
        interface_.updateMinimapBackground();
        interface_.updateSelectedUnitFrame();
    }
}

void Game::toggleFog() {
    if (!menu_.isVisible()) {
        players_.handleFPressed();
        interface_.updateMinimapBackground();
    }
}

void Game::deleteSelectedUnit() {
    if (!menu_.isVisible()) {
        players_.handleDPressed();
        interface_.updateSelectedUnitFrame();
    }
}

void Game::switchToNextPlayer() {
    if (!menu_.isVisible()) {
        players_.switchToNextPlayer();
        interface_.updateMinimapBackground();
        interface_.updateSelectedUnitFrame();
    }
}

void Game::captureScreenToFile() {
    window_->capture().saveToFile("screenshot.png");
}

void Game::scrollView() {
    if (!menu_.isVisible()) {
        sf::Vector2f actualShift = renderer_.scrollView(sf::Mouse::getPosition(*window_));

        if (actualShift != sf::Vector2f(0, 0)) {
            interface_.updateMinimapDisplayedRectangle();
        }
    }
}

void Game::zoomView(float delta) {
    if (!menu_.isVisible()) {
        renderer_.zoomView(delta, sf::Mouse::getPosition(*window_));
        interface_.updateMinimapDisplayedRectangle();
    }
}
