/* Copyright 2014 <Piotr Derkowski> */

#ifndef MENU_DRAWER_HPP_
#define MENU_DRAWER_HPP_

#include <memory>
#include <vector>
#include "SFML/Graphics.hpp"
#include "MenuModel.hpp"
#include "Resources.hpp"
#include "MenuItem.hpp"
#include "MenuItemDrawer.hpp"

class MenuDrawer {
public:
    MenuDrawer(std::shared_ptr<MenuModel> model, std::shared_ptr<sf::RenderTarget> target,
        Resources& resources);

    ~MenuDrawer() { }

    void draw() const;
    void resetItemDrawers();

    std::shared_ptr<MenuItem> getObjectByPosition(const sf::Vector2i& position);

private:
    void drawBackground() const;
    void drawItems() const;

    static const float fontHeightFactor_;
    static const float lineSpacingFactor_;

    float calculateItemPosition(int itemNo) const;

    std::shared_ptr<MenuModel> model_;

    std::shared_ptr<sf::RenderTarget> target_;

    sf::Font font_;

    std::vector<std::shared_ptr<MenuItemDrawer>> itemDrawers_;
};

#endif  // MENU_DRAWER_HPP_
