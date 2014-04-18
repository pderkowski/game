/* Copyright 2014 <Piotr Derkowski> */

#ifndef MENU_DRAWER_HPP_
#define MENU_DRAWER_HPP_

#include <memory>
#include <vector>
#include "SFML/Graphics.hpp"
#include "Menu.hpp"
#include "Resources.hpp"
#include "Layer.hpp"
#include "MenuItemDrawer.hpp"

class MenuDrawer : public sf::Drawable {
public:
    MenuDrawer(std::shared_ptr<Menu> menu, Resources& resources, sf::RenderTarget& target);

    virtual ~MenuDrawer() { }

    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

    bool isVisible() const;
    void toggleVisibility();

    void reload(sf::RenderTarget& target);
    void handle(const sf::Event& e);

private:
    void initializeMenuItemDrawers(sf::RenderTarget& target);
    sf::Vector2i calculateMenuItemPosition(int itemNo, sf::RenderTarget& target) const;

    std::shared_ptr<Menu> menu_;

    sf::Font font_;

    std::vector<std::shared_ptr<MenuItemDrawer>> itemDrawers_;
    mutable Layer layer_;

    bool isVisible_;
};

#endif  // MENU_DRAWER_HPP_
