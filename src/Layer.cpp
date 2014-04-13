/* Copyright 2014 <Piotr Derkowski> */

#include <vector>
#include <functional>
#include "SFML/Graphics.hpp"
#include "Layer.hpp"

void Layer::addClickableArea(const sf::FloatRect& area, Handler handler) {
    clickableAreas_.push_back(std::make_pair(area, handler));
}

void Layer::handleClick(const sf::Event& e) {
    auto clickedAreaAndHandler = std::find_if(clickableAreas_.rbegin(), clickableAreas_.rend(),
        [&] (const decltype(clickableAreas_)::value_type& areaAndHandler) {
            return areaAndHandler.first.contains(e.mouseButton.x, e.mouseButton.y); }); //NOLINT

    if (clickedAreaAndHandler != clickableAreas_.rend())
        clickedAreaAndHandler->second(e);
}
