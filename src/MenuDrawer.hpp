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

class MenuDrawer : public sf::Drawable {
public:
    MenuDrawer(std::shared_ptr<MenuModel> model, Resources& resources);

    virtual ~MenuDrawer() { }

    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
    void drawBackground(sf::RenderTarget& target, sf::RenderStates states) const;
    void drawItems(sf::RenderTarget& target, sf::RenderStates states) const;

    void resetItemDrawers();

    std::shared_ptr<MenuItem> getObjectByPosition(const sf::Vector2i& position,
        sf::RenderTarget& target);

private:
    static const float fontHeightFactor_;
    static const float lineSpacingFactor_;

    float calculateItemPosition(int itemNo) const;

    std::shared_ptr<MenuModel> model_;

    sf::Font font_;

    std::vector<std::shared_ptr<MenuItemDrawer>> itemDrawers_;
};

#endif  // MENU_DRAWER_HPP_
