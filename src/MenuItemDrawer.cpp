/* Copyright 2014 <Piotr Derkowski> */

#include "SFML/Graphics.hpp"
#include "MenuItemDrawer.hpp"
#include "MenuItem.hpp"

MenuItemDrawer::MenuItemDrawer(std::shared_ptr<MenuItem> item,
    float fontHeightFactor,
    float relativeYPosition,
    const sf::Font& font)
        : item_(item),
        text_(item->getName(), font),
        fontHeightFactor_(fontHeightFactor),
        relativeYPosition_(relativeYPosition)
{ }

void MenuItemDrawer::centerText(sf::Text& text) const {
    sf::FloatRect textRect = text.getLocalBounds();
    text.setOrigin(textRect.left + textRect.width / 2, textRect.top + textRect.height / 2);
}

void MenuItemDrawer::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    moveTextToAbsolutePosition(target);
    target.draw(text_, states);
}

void MenuItemDrawer::moveTextToAbsolutePosition(const sf::RenderTarget& target) const {
    text_.setCharacterSize(fontHeightFactor_ * target.getSize().y);
    centerText(text_);
    sf::Vector2i position(target.getSize().x * 0.5, target.getSize().y * relativeYPosition_);
    text_.setPosition(target.mapPixelToCoords(position));
}

std::shared_ptr<MenuItem> MenuItemDrawer::getObjectByPosition(const sf::Vector2i& position,
        sf::RenderTarget& target) {
    moveTextToAbsolutePosition(target);
    sf::FloatRect bounds = text_.getGlobalBounds();

    if (bounds.contains(target.mapPixelToCoords(position)))
        return item_;
    else
        return std::shared_ptr<MenuItem>();
}
