/* Copyright 2014 <Piotr Derkowski> */

#include <cstdlib>
#include "Game.hpp"
#include "interface/Interface.hpp"
#include "menu/Menu.hpp"
#include "Application.hpp"
#include "Timer.hpp"
#include "SFML/Graphics.hpp"
class Settings;


Application::Application(const Settings& settings)
    : window_(std::make_shared<sf::RenderWindow>(
        sf::VideoMode::getFullscreenModes()[0],
        "",
        sf::Style::Fullscreen)),
    renderer_(settings, window_),
    game_(settings, &renderer_),
    interface_(game_.getMapModel(), game_.getPlayers(), &renderer_),
    menu_(window_)
{
    menu_.addItem("Return", [this] () { toggleMenu(); });
    menu_.addItem("New game", [this] () { restart(); });
    menu_.addItem("Quit game", [this] () { quit(); });

    timers_.push_back(Timer(50, [this] () { scrollView(); }));

    renderer_.addObserver(&interface_);
}

void Application::run() {
    while (window_->isOpen()) {
        handleEvents();
        handleTimers();

        window_->clear();
        game_.draw();
        interface_.draw();
        if (menu_.isVisible()) {
            menu_.draw();
        }
        window_->display();
    }
}

void Application::quit() {
    exit(EXIT_SUCCESS);
}

void Application::toggleMenu() {
    menu_.toggleVisibility();
}

void Application::captureScreenToFile() {
    window_->capture().saveToFile("screenshot.png");
}

void Application::scrollView() {
    if (!menu_.isVisible()) {
        renderer_.scrollView(sf::Mouse::getPosition(*window_));
    }
}

void Application::zoomView(float delta) {
    if (!menu_.isVisible()) {
        renderer_.zoomView(delta, sf::Mouse::getPosition(*window_));
    }
}

void Application::handleMouseMoved(const sf::Event& event) {
    if (menu_.isVisible()) {
        menu_.handleMouseMoved(event);
    }
}

void Application::handleEvents() {
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

void Application::handleTimers() {
    for (auto& timer : timers_) {
        if (timer.elapsed()) {
            timer.executeCallback();
        }
    }
}

void Application::handleLeftClick(const sf::Event& event) {
    if (menu_.isVisible()) {
        menu_.handleLeftClick(event);
    } else {
        game_.setPrimarySelection(getClickedMapCoords(event));
        interface_.updateSelectedUnitFrame();
    }
}

void Application::handleRightClick(const sf::Event& event) {
    if (!menu_.isVisible()) {
        game_.setSecondarySelection(getClickedMapCoords(event));
        interface_.updateMinimapBackground();
        interface_.updateSelectedUnitFrame();
    }
}

IntIsoPoint Application::getClickedMapCoords(const sf::Event& event) const {
    return renderer_.getMapCoords(sf::Vector2i{ event.mouseButton.x, event.mouseButton.y });
}

void Application::restart() {
    game_.generateNewMap();
    interface_.setModel(game_.getMapModel());
}

void Application::addUnit() {
    if (!menu_.isVisible()) {
        game_.addUnit();
        interface_.updateMinimapBackground();
        interface_.updateSelectedUnitFrame();
    }
}

void Application::toggleFog() {
    if (!menu_.isVisible()) {
        game_.toggleFog();
        interface_.updateMinimapBackground();
    }
}

void Application::deleteSelectedUnit() {
    if (!menu_.isVisible()) {
        game_.deleteSelectedUnit();
        interface_.updateSelectedUnitFrame();
    }
}

void Application::switchToNextPlayer() {
    if (!menu_.isVisible()) {
        game_.switchToNextPlayer();
        interface_.updateMinimapBackground();
        interface_.updateSelectedUnitFrame();
    }
}

