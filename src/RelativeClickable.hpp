/* Copyright 2014 <Piotr Derkowski> */

#ifndef RELATIVE_CLICKABLE_HPP_
#define RELATIVE_CLICKABLE_HPP_

#include "SFML/Graphics.hpp"
#include "Clickable.hpp"

class RelativeClickable : public Clickable {
public:
    using Clickable::Clickable;
    virtual bool isClicked(const sf::Event& e) const;
    virtual void handleClick() = 0;
    virtual ~RelativeClickable() { }
};

#endif  // RELATIVE_CLICKABLE_HPP_
