/* Copyright 2014 <Piotr Derkowski> */

#include <memory>
#include <string>
#include <vector>
#include <functional>
#include "Menu.hpp"
#include "MenuDrawer.hpp"
#include "MenuModel.hpp"
#include "MenuItem.hpp"

Menu::Menu(std::shared_ptr<sf::RenderWindow> target)
    : model_(std::make_shared<MenuModel>()),
    drawer_(model_, target),
    isVisible_(false)
{ }

void Menu::addItem(const std::string& itemName, Callback callback) {
    model_->addItem(itemName, callback);
    drawer_.resetItemDrawers();
}

void Menu::draw() const {
    drawer_.draw();
}

void Menu::handleClick(const sf::Event& e) {
    std::shared_ptr<MenuItem> clickedObject
        = drawer_.getObjectByPosition(sf::Vector2i(e.mouseButton.x, e.mouseButton.y));

    if (clickedObject) {
        clickedObject->execute();
    }
}

void Menu::handleMouseMoved(const sf::Event& e) {
    std::shared_ptr<MenuItem> pointedObject
        = drawer_.getObjectByPosition(sf::Vector2i(e.mouseMove.x, e.mouseMove.y));

    if (pointedObject) {
        drawer_.select(pointedObject);
    } else {
        drawer_.clearSelection();
    }
}

bool Menu::isVisible() const {
    return isVisible_;
}

void Menu::toggleVisibility() {
    isVisible_ = !isVisible_;
}
