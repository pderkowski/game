/* Copyright 2014 <Piotr Derkowski> */

#include "SFML/Graphics.hpp"
#include "Clickable.hpp"

Clickable::Clickable()
    : area_()
{ }

Clickable::Clickable(const sf::FloatRect& area)
    : area_(area)
{ }

void Clickable::setArea(const sf::FloatRect& area) {
    area_ = area;
}
