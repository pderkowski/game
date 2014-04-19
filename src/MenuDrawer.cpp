/* Copyright 2014 <Piotr Derkowski> */

#include <iostream>
#include <vector>
#include <memory>
#include "SFML/Graphics.hpp"
#include "MenuModel.hpp"
#include "MenuDrawer.hpp"
#include "Resources.hpp"

const float MenuDrawer::fontHeightFactor_ = 1.0 / 25;
const float MenuDrawer::lineSpacingFactor_ = fontHeightFactor_ / 4;

MenuDrawer::MenuDrawer(std::shared_ptr<MenuModel> model, std::shared_ptr<sf::RenderTarget> target,
    Resources& resources)
        : model_(model), target_(target), font_(resources.loadFont("fonts/UbuntuMono.ttf")) {
    resetItemDrawers();
}

void MenuDrawer::draw() const {
    drawBackground();
    drawItems();
}

void MenuDrawer::drawBackground() const {
    sf::RectangleShape menuBackground(sf::Vector2f(target_->getSize().x, target_->getSize().y));
    menuBackground.setFillColor(sf::Color(0, 0, 0, 190));

    const auto position = target_->mapPixelToCoords(sf::Vector2i(0, 0));
    menuBackground.setPosition(position.x, position.y);

    target_->draw(menuBackground);
}

void MenuDrawer::drawItems() const {
    for (auto drawer : itemDrawers_) {
        drawer->draw();
    }
}

void MenuDrawer::select(std::shared_ptr<const MenuItem> item) {
    auto drawer = getDrawerByObject(item);
    if (drawer)
        drawer->setColor(sf::Color(100, 100, 100, 255));
}

void MenuDrawer::clearSelection() {
    for (auto drawer : itemDrawers_) {
        drawer->setColor(sf::Color(255, 255, 255, 255));
    }
}

void MenuDrawer::resetItemDrawers() {
    itemDrawers_.clear();

    for (unsigned i = 0; i < model_->items_.size(); ++i) {
        float position = calculateItemPosition(i);

        itemDrawers_.push_back(std::make_shared<MenuItemDrawer>(
            model_->items_[i], fontHeightFactor_, position, target_, font_));
    }
}

std::shared_ptr<MenuItem> MenuDrawer::getObjectByPosition(const sf::Vector2i& position) {
    for (auto itemDrawer : itemDrawers_) {
        auto object = itemDrawer->getObjectByPosition(position);
        if (object)
            return object;
    }

    return std::shared_ptr<MenuItem>();
}

float MenuDrawer::calculateItemPosition(int itemNo) const {
    const float center = 0.5;

    const float itemNoRelativeToCenter = itemNo - (model_->items_.size() - 1) / 2.0;

    return center + itemNoRelativeToCenter * (fontHeightFactor_ + lineSpacingFactor_);
}

std::shared_ptr<MenuItemDrawer> MenuDrawer::getDrawerByObject(
        std::shared_ptr<const MenuItem> item) {
    for (auto drawer : itemDrawers_) {
        if (item == drawer->getObject())
            return drawer;
    }

    return std::shared_ptr<MenuItemDrawer>();
}
