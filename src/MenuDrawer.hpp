/* Copyright 2014 <Piotr Derkowski> */

#ifndef MENU_DRAWER_HPP_
#define MENU_DRAWER_HPP_

#include <memory>
#include <vector>
#include "SFML/Graphics.hpp"
#include "Menu.hpp"
#include "Resources.hpp"

class MenuDrawer : public sf::Drawable {
public:
    MenuDrawer(std::shared_ptr<Menu> menu, Resources& resources);

    virtual ~MenuDrawer() { }

    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

    bool isVisible() const;
    void toggleVisibility();

private:
    std::vector<sf::Text> createMenuTexts(sf::RenderTarget& target) const;
    void centerTextAt(sf::Text& text, const sf::Vector2f& position) const;

    std::shared_ptr<Menu> menu_;

    sf::Font font_;

    bool isVisible_;
};

#endif  // MENU_DRAWER_HPP_
