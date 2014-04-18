/* Copyright 2014 <Piotr Derkowski> */

#include <memory>
#include "SFML/Graphics.hpp"
#include "AbsoluteClickable.hpp"

AbsoluteClickable::AbsoluteClickable(const sf::FloatRect& area, const sf::RenderTarget& target)
    : Clickable(area), target_(target)
{ }

bool AbsoluteClickable::isClicked(const sf::Event& e) const {
    return area_.contains(target_.mapPixelToCoords(sf::Vector2i(e.mouseButton.x, e.mouseButton.y)));
}
