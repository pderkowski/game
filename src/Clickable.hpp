/* Copyright 2014 <Piotr Derkowski> */

#ifndef CLICKABLE_HPP_
#define CLICKABLE_HPP_

#include "SFML/Graphics.hpp"

class Clickable {
public:
    Clickable();
    explicit Clickable(const sf::FloatRect& area);
    virtual ~Clickable() { }

    void setArea(const sf::FloatRect& area);
    virtual bool isClicked(const sf::Event& e) const = 0;
    virtual void handleClick() = 0;

protected:
    sf::FloatRect area_;
};

#endif  // CLICKABLE_HPP_
