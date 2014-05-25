/* Copyright 2014 <Piotr Derkowski> */

#include <cstdlib>
#include <memory>
#include "Map.hpp"
#include "Menu.hpp"
#include "Game.hpp"

Game::Game(int rows, int columns, Resources& resources)
        : window_(std::make_shared<sf::RenderWindow>(
            sf::VideoMode::getFullscreenModes()[0],
            "",
            sf::Style::Fullscreen)),
        map_(rows, columns, window_, resources),
        menu_(window_, resources)
{
    menu_.addItem("Return", [&] () { toggleMenu(); });
    menu_.addItem("New game", [&] () { restart(); });
    menu_.addItem("Quit game", [&] () { quit(); });
}

void Game::start() {
    while (window_->isOpen()) {
        handleEvents();

        window_->clear();
        map_.draw();
        if (menu_.isVisible()) {
            menu_.draw();
        }
        window_->display();
    }
}

void Game::restart() {
    map_.generateMap();
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
        } else if (event.type == sf::Event::MouseButtonPressed
                && event.mouseButton.button == sf::Mouse::Button::Left) {
            handleClick(event);
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

void Game::handleClick(const sf::Event& event) {
    if (menu_.isVisible()) {
        menu_.handleClick(event);
    } else {
        map_.handleClick(event);
    }
}

void Game::handleMouseWheelMoved(const sf::Event& event) {
    if (!menu_.isVisible()) {
        map_.handleMouseWheelMoved(event);
    }
}

void Game::handleMouseMoved(const sf::Event& event) {
    if (menu_.isVisible()) {
        menu_.handleMouseMoved(event);
    } else {
        map_.handleMouseMoved(event);
    }
}
