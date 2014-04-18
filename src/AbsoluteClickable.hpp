/* Copyright 2014 <Piotr Derkowski> */

#ifndef ABSOLUTE_CLICKABLE_HPP_
#define ABSOLUTE_CLICKABLE_HPP_

#include "SFML/Graphics.hpp"
#include "Clickable.hpp"

class AbsoluteClickable : public Clickable {
public:
    AbsoluteClickable(const sf::FloatRect& area, const sf::RenderTarget& target);
    virtual bool isClicked(const sf::Event& e) const;
    virtual void handleClick() = 0;
    virtual ~AbsoluteClickable() { }

protected:
    const sf::RenderTarget& target_;
};

#endif  // ABSOLUTE_CLICKABLE_HPP_
