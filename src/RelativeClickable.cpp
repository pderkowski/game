/* Copyright 2014 <Piotr Derkowski> */

#include <iostream>
#include "SFML/Graphics.hpp"
#include "RelativeClickable.hpp"

bool RelativeClickable::isClicked(const sf::Event& e) const {
    return area_.contains(e.mouseButton.x, e.mouseButton.y);
}
