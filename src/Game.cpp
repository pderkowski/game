/* Copyright 2014 <Piotr Derkowski> */

#include <cstdlib>
#include <memory>
#include <string>
#include "Map.hpp"
#include "menu/Menu.hpp"
#include "Game.hpp"
#include "TileEnums.hpp"
#include "players/Players.hpp"
#include "MapRenderer.hpp"
#include "Minimap.hpp"
#include "Interface.hpp"


Game::Game(int rows, int columns, int numberOfPlayers)
        : window_(std::make_shared<sf::RenderWindow>(
            sf::VideoMode::getFullscreenModes()[0],
            "",
            sf::Style::Fullscreen)),
        map_(rows, columns, window_),
        players_(numberOfPlayers, map_.getModel().get(), map_.getRenderer()),
        minimap_(map_.getModel().get(), players_.getCurrentPlayer()->getFog(), map_.getRenderer()),
        interface_(map_.getRenderer(), minimap_.getSize()),
        menu_(window_)
{
    minimap_.setPosition(interface_.getMinimapSlotPosition());

    menu_.addItem("Return", [this] () { toggleMenu(); });
    menu_.addItem("New game", [this] () { restart(); });
    menu_.addItem("Quit game", [this] () { quit(); });
}

void Game::start() {
    while (window_->isOpen()) {
        handleEvents();

        window_->clear();
        map_.draw();
        players_.draw();
        interface_.draw();
        minimap_.draw();
        if (menu_.isVisible()) {
            menu_.draw();
        }
        window_->display();
    }
}

void Game::restart() {
    map_.generateMap();
    minimap_.rebuild(map_.getModel().get(), players_.getCurrentPlayer()->getFog());
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
                handleAPressed();
                break;
            case sf::Keyboard::Key::F:
                handleFPressed();
                break;
            case sf::Keyboard::Key::D:
                handleDPressed();
                break;
            case sf::Keyboard::Key::Return:
                handleEnterPressed();
                break;
            case sf::Keyboard::Key::P:
                handlePrintScreenPressed();
                break;
            default:
                break;
            }
        } else if (event.type == sf::Event::MouseWheelMoved) {
            handleMouseWheelMoved(event);
        } else if (event.type == sf::Event::MouseMoved) {
            handleMouseMoved(event);
        }
    }
}

void Game::handleLeftClick(const sf::Event& event) {
    if (menu_.isVisible()) {
        menu_.handleLeftClick(event);
    } else {
        players_.handleLeftClick(event);
    }
}

void Game::handleRightClick(const sf::Event& event) {
    if (!menu_.isVisible()) {
        players_.handleRightClick(event);
        minimap_.rebuild(map_.getModel().get(), players_.getCurrentPlayer()->getFog());
    }
}

void Game::handleMouseWheelMoved(const sf::Event& event) {
    if (!menu_.isVisible()) {
        map_.handleMouseWheelMoved(event);
        minimap_.updateDisplayedRectangle();
    }
}

void Game::handleMouseMoved(const sf::Event& event) {
    if (menu_.isVisible()) {
        menu_.handleMouseMoved(event);
    } else {
        map_.handleMouseMoved(event);
        minimap_.updateDisplayedRectangle();
    }
}

void Game::handleAPressed() {
    if (!menu_.isVisible()) {
        players_.handleAPressed();
        minimap_.updateFog(players_.getCurrentPlayer()->getFog());
    }
}

void Game::handleFPressed() {
    if (!menu_.isVisible()) {
        players_.handleFPressed();
        minimap_.toggleFog();
    }
}

void Game::handleDPressed() {
    if (!menu_.isVisible()) {
        players_.handleDPressed();
    }
}

void Game::handleEnterPressed() {
    if (!menu_.isVisible()) {
        players_.switchToNextPlayer();
        minimap_.updateFog(players_.getCurrentPlayer()->getFog());
    }
}

void Game::handlePrintScreenPressed() {
    window_->capture().saveToFile("screenshot.png");
}
