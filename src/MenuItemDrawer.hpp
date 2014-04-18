/* Copyright 2014 <Piotr Derkowski> */

#ifndef MENUITEMDRAWER_HPP_
#define MENUITEMDRAWER_HPP_

#include <memory>
#include "SFML/Graphics.hpp"
#include "RelativeClickable.hpp"
#include "MenuItem.hpp"

class MenuItemDrawer : public RelativeClickable,  public sf::Drawable {
public:
    MenuItemDrawer(std::shared_ptr<MenuItem> menuItem,
        const sf::Vector2i& relativePosition,
        const sf::Font& font);
    virtual ~MenuItemDrawer() { }

    virtual void handleClick();
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

    void centerText(sf::Text& text) const;

private:
    mutable sf::Text text_;
    sf::Vector2i relativePosition_;
    std::shared_ptr<MenuItem> menuItem_;
};

#endif  // MENUITEMDRAWER_HPP_
