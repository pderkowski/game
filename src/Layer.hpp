/* Copyright 2014 <Piotr Derkowski> */

#ifndef LAYER_HPP_
#define LAYER_HPP_

#include <memory>
#include <vector>
#include "SFML/Graphics.hpp"
#include "Clickable.hpp"

class Layer {
public:
    void addClickable(std::shared_ptr<Clickable> clickable);
    void clearClickables();

    void handleClick(const sf::Event&);

private:
    std::vector<std::shared_ptr<Clickable>> clickables_;
};

#endif  // LAYER_HPP_
