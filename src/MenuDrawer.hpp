/* Copyright 2014 <Piotr Derkowski> */

#ifndef MENU_DRAWER_HPP_
#define MENU_DRAWER_HPP_

#include <memory>
#include "SFML/Graphics.hpp"
#include "Menu.hpp"

class MenuDrawer : public sf::Drawable {
public:
    explicit MenuDrawer(std::shared_ptr<Menu> menu);

    virtual ~MenuDrawer() { }

    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

    bool isVisible() const;
    void toggleVisibility();

private:
    std::shared_ptr<Menu> menu_;
    bool isVisible_;
};

#endif  // MENU_DRAWER_HPP_
