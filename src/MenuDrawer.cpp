/* Copyright 2014 <Piotr Derkowski> */

#include <iostream>
#include <vector>
#include <memory>
#include "SFML/Graphics.hpp"
#include "Menu.hpp"
#include "MenuDrawer.hpp"
#include "Resources.hpp"
#include "Layer.hpp"

MenuDrawer::MenuDrawer(std::shared_ptr<Menu> menu, Resources& resources, sf::RenderTarget& target)
        : menu_(menu), font_(resources.loadFont("fonts/UbuntuMono.ttf")), isVisible_(false) {
    initializeMenuItemDrawers(target);
}

void MenuDrawer::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    sf::RectangleShape menuBackground(sf::Vector2f(target.getSize().x, target.getSize().y));
    menuBackground.setFillColor(sf::Color(0, 0, 0, 190));

    const auto position = target.mapPixelToCoords(sf::Vector2i(0, 0));
    menuBackground.setPosition(position.x, position.y);

    target.draw(menuBackground, states);

    for (auto itemDrawer : itemDrawers_) {
        target.draw(*itemDrawer, states);
    }
}

void MenuDrawer::initializeMenuItemDrawers(sf::RenderTarget& target) {
    for (unsigned i = 0; i < menu_->items_.size(); ++i) {
        sf::Vector2i position = calculateMenuItemPosition(i, target);

        itemDrawers_.push_back(
            std::make_shared<MenuItemDrawer>(menu_->items_[i], position, font_));

        layer_.addClickable(itemDrawers_.back());
    }
}

sf::Vector2i MenuDrawer::calculateMenuItemPosition(int itemNo, sf::RenderTarget& target) const {
    const auto center = sf::Vector2i(target.getSize().x / 2, target.getSize().y / 2);

    const float itemNoRelativeToCenter = itemNo - (menu_->items_.size() - 1) / 2.0;
    const int fontHeight = 30;
    const int lineSpacing = 10;

    return sf::Vector2i(center.x, center.y + itemNoRelativeToCenter * (fontHeight + lineSpacing));
}

bool MenuDrawer::isVisible() const {
    return isVisible_;
}

void MenuDrawer::toggleVisibility() {
    isVisible_ = !isVisible_;
}

void MenuDrawer::reload(sf::RenderTarget& target) {
    initializeMenuItemDrawers(target);
}

void MenuDrawer::handle(const sf::Event& e) {
    layer_.handleClick(e);
}
