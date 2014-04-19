/* Copyright 2014 <Piotr Derkowski> */

#include "SFML/Graphics.hpp"
#include "MenuItemDrawer.hpp"
#include "MenuItem.hpp"

MenuItemDrawer::MenuItemDrawer(std::shared_ptr<MenuItem> item,
    float fontHeightFactor,
    float relativeYPosition,
    std::shared_ptr<sf::RenderTarget> target,
    const sf::Font& font)
        : item_(item),
        text_(item->getName(), font),
        fontHeightFactor_(fontHeightFactor),
        relativeYPosition_(relativeYPosition),
        target_(target)
{ }

void MenuItemDrawer::centerText(sf::Text& text) const {
    sf::FloatRect textRect = text.getLocalBounds();
    text.setOrigin(textRect.left + textRect.width / 2, textRect.top + textRect.height / 2);
}

void MenuItemDrawer::draw() const {
    moveTextToAbsolutePosition();
    target_->draw(text_);
}

void MenuItemDrawer::moveTextToAbsolutePosition() const {
    text_.setCharacterSize(fontHeightFactor_ * target_->getSize().y);
    centerText(text_);
    sf::Vector2i position(target_->getSize().x * 0.5, target_->getSize().y * relativeYPosition_);
    text_.setPosition(target_->mapPixelToCoords(position));
}

std::shared_ptr<MenuItem> MenuItemDrawer::getObjectByPosition(const sf::Vector2i& position) {
    moveTextToAbsolutePosition();
    sf::FloatRect bounds = text_.getGlobalBounds();

    if (bounds.contains(target_->mapPixelToCoords(position)))
        return item_;
    else
        return std::shared_ptr<MenuItem>();
}
