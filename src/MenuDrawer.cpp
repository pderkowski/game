/* Copyright 2014 <Piotr Derkowski> */

#include <vector>
#include <memory>
#include "SFML/Graphics.hpp"
#include "Menu.hpp"
#include "MenuDrawer.hpp"
#include "Resources.hpp"

MenuDrawer::MenuDrawer(std::shared_ptr<Menu> menu, Resources& resources)
    : menu_(menu), font_(resources.loadFont("fonts/UbuntuMono.ttf")), isVisible_(false)
{ }

void MenuDrawer::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    sf::RectangleShape menuBackground(sf::Vector2f(target.getSize().x, target.getSize().y));
    menuBackground.setFillColor(sf::Color(0, 0, 0, 190));

    const auto position = target.mapPixelToCoords(sf::Vector2i(0, 0));
    menuBackground.setPosition(position.x, position.y);

    target.draw(menuBackground, states);

    const auto menuTexts = createMenuTexts(target);

    for (const auto& text : menuTexts) {
        target.draw(text, states);
    }
}

std::vector<sf::Text> MenuDrawer::createMenuTexts(sf::RenderTarget& target) const {
    std::vector<sf::Text> res;

    const auto center
        = target.mapPixelToCoords(sf::Vector2i(target.getSize().x / 2, target.getSize().y / 2));

    for (unsigned i = 0; i < menu_->items_.size(); ++i) {
        sf::Vector2f position(center.x, center.y + i * 40);
        sf::Text text(menu_->items_[i].first, font_, 30);
        centerTextAt(text, position);
        res.push_back(text);
    }

    return res;
}

void MenuDrawer::centerTextAt(sf::Text& text, const sf::Vector2f& position) const {
    sf::FloatRect textRect = text.getLocalBounds();
    text.setOrigin(textRect.left + textRect.width / 2, textRect.top + textRect.height / 2);
    text.setPosition(position);
}

bool MenuDrawer::isVisible() const {
    return isVisible_;
}

void MenuDrawer::toggleVisibility() {
    isVisible_ = !isVisible_;
}
