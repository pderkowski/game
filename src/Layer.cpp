/* Copyright 2014 <Piotr Derkowski> */

#include <iostream>
#include <vector>
#include <algorithm>
#include "SFML/Graphics.hpp"
#include "Layer.hpp"
#include "Clickable.hpp"

void Layer::addClickable(std::shared_ptr<Clickable> clickable) {
    clickables_.push_back(clickable);
}

void Layer::clearClickables() {
    clickables_.clear();
}

void Layer::handleClick(const sf::Event& e) {
    auto clickable = std::find_if(clickables_.rbegin(), clickables_.rend(),
        [&] (const decltype(clickables_)::value_type& clickable) {
            return clickable->isClicked(e); }); //NOLINT

    if (clickable != clickables_.rend())
        (*clickable)->handleClick();
    else
        std::cout << "Missed!" << std::endl;
}
