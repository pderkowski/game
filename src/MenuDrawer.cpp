/* Copyright 2014 <Piotr Derkowski> */

#include <memory>
#include "SFML/Graphics.hpp"
#include "Menu.hpp"
#include "MenuDrawer.hpp"
#include "Resources.hpp"

MenuDrawer::MenuDrawer(std::shared_ptr<Menu> menu)
    : menu_(menu), isVisible_(false)
{ }

void MenuDrawer::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    sf::RectangleShape menuBackground(sf::Vector2f(target.getSize().x, target.getSize().y));
    menuBackground.setFillColor(sf::Color(0, 0, 0, 190));

    sf::Vector2f coords = target.mapPixelToCoords(sf::Vector2i(0, 0));
    menuBackground.setPosition(coords.x, coords.y);

    target.draw(menuBackground, states);
}

bool MenuDrawer::isVisible() const {
    return isVisible_;
}

void MenuDrawer::toggleVisibility() {
    isVisible_ = !isVisible_;
}
