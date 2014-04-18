/* Copyright 2014 <Piotr Derkowski> */

#include <iostream>
#include <memory>
#include "SFML/Graphics.hpp"
#include "RelativeClickable.hpp"
#include "MenuItemDrawer.hpp"
#include "MenuItem.hpp"

MenuItemDrawer::MenuItemDrawer(std::shared_ptr<MenuItem> menuItem,
    const sf::Vector2i& relativePosition,
    const sf::Font& font)
        : RelativeClickable(),
        text_(menuItem->getName(), font, 30),
        relativePosition_(relativePosition),
        menuItem_(menuItem) {
    centerText(text_);
    text_.setPosition(relativePosition_.x, relativePosition_.y);
    setArea(text_.getGlobalBounds());
}

void MenuItemDrawer::centerText(sf::Text& text) const {
    sf::FloatRect textRect = text.getLocalBounds();
    text.setOrigin(textRect.left + textRect.width / 2, textRect.top + textRect.height / 2);
}

void MenuItemDrawer::handleClick() {
    menuItem_->execute();
}

void MenuItemDrawer::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    text_.setPosition(target.mapPixelToCoords(relativePosition_));
    target.draw(text_, states);
}
