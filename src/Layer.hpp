/* Copyright 2014 <Piotr Derkowski> */

#ifndef LAYER_HPP_
#define LAYER_HPP_

#include <vector>
#include <utility>
#include <functional>
#include "SFML/Graphics.hpp"

class Layer {
public:
    typedef std::function<void(const sf::Event&)> Handler;

    void addClickableArea(const sf::FloatRect& area, Handler handler);

    void handleClick(const sf::Event&);

private:
    std::vector<std::pair<sf::FloatRect, Handler>> clickableAreas_;
};

#endif  // LAYER_HPP_
