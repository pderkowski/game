/* Copyright 2014 <Piotr Derkowski> */

#ifndef MENU_MENUDRAWER_HPP_
#define MENU_MENUDRAWER_HPP_

#include <memory>
#include <vector>
#include "SFML/Graphics.hpp"
#include "MenuModel.hpp"
#include "MenuItem.hpp"
#include "MenuItemDrawer.hpp"


namespace menu {


class MenuDrawer {
public:
    MenuDrawer(std::shared_ptr<MenuModel> model, std::shared_ptr<sf::RenderTarget> target);

    ~MenuDrawer() { }

    void draw() const;
    void resetItemDrawers();

    void select(std::shared_ptr<const MenuItem> item);
    void clearSelection();

    std::shared_ptr<MenuItem> getObjectByPosition(const sf::Vector2i& position);

private:
    void drawBackground() const;
    void drawItems() const;

    float calculateItemPosition(int itemNo) const;

    std::shared_ptr<MenuItemDrawer> getDrawerByObject(std::shared_ptr<const MenuItem> item);

    static const float fontHeightFactor_;
    static const float lineSpacingFactor_;

    std::shared_ptr<MenuModel> model_;

    std::shared_ptr<sf::RenderTarget> target_;

    sf::Font font_;

    std::vector<std::shared_ptr<MenuItemDrawer>> itemDrawers_;
};


}  // namespace menu


#endif  // MENU_MENUDRAWER_HPP_
