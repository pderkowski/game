/* Copyright 2014 <Piotr Derkowski> */

#ifndef MENUITEMDRAWER_HPP_
#define MENUITEMDRAWER_HPP_

#include <memory>
#include "SFML/Graphics.hpp"
#include "MenuItem.hpp"

class MenuItemDrawer : public sf::Drawable {
public:
    MenuItemDrawer(std::shared_ptr<MenuItem> item,
        float fontHeightFactor,
        float relativeYPosition,
        const sf::Font& font);
    virtual ~MenuItemDrawer() { }

    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

    std::shared_ptr<MenuItem> getObjectByPosition(const sf::Vector2i& position,
        sf::RenderTarget& target);

private:
    void centerText(sf::Text& text) const;
    void moveTextToAbsolutePosition(const sf::RenderTarget& target) const;

    std::shared_ptr<MenuItem> item_;
    mutable sf::Text text_;
    float fontHeightFactor_;
    float relativeYPosition_;
};

#endif  // MENUITEMDRAWER_HPP_
