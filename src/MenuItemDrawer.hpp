/* Copyright 2014 <Piotr Derkowski> */

#ifndef MENUITEMDRAWER_HPP_
#define MENUITEMDRAWER_HPP_

#include <memory>
#include "SFML/Graphics.hpp"
#include "MenuItem.hpp"

class MenuItemDrawer {
public:
    MenuItemDrawer(std::shared_ptr<MenuItem> item,
        float fontHeightFactor,
        float relativeYPosition,
        std::shared_ptr<sf::RenderTarget> target,
        const sf::Font& font);
    virtual ~MenuItemDrawer() { }

    virtual void draw() const;

    std::shared_ptr<MenuItem> getObjectByPosition(const sf::Vector2i& position);

private:
    void centerText(sf::Text& text) const;
    void moveTextToAbsolutePosition() const;

    std::shared_ptr<MenuItem> item_;
    mutable sf::Text text_;
    float fontHeightFactor_;
    float relativeYPosition_;

    std::shared_ptr<sf::RenderTarget> target_;
};

#endif  // MENUITEMDRAWER_HPP_
