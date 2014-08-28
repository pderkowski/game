/* Copyright 2014 <Piotr Derkowski> */

#include "SFML/Graphics.hpp"
#include "Renderer.hpp"
#include "Layout.hpp"


namespace interface {


Layout::Layout(const Renderer* renderer)
    : renderer_(renderer),
    availableSlotPosition_(renderer_->getSize()),
    thickness_(1.0f)
{
    addBorders(sf::Vector2f(renderer_->getSize()), sf::Vector2f(), sf::Color::Transparent);
}

sf::Vector2f Layout::addSlot(const sf::Vector2f& slotSize, const sf::Color& fillColor) {
    const sf::Vector2f border(4 * thickness_, 4 * thickness_);
    const sf::Vector2f totalBorder = 2.0f * border;

    const sf::Vector2f position = availableSlotPosition_ - (slotSize + totalBorder);
    availableSlotPosition_.x -= (slotSize.x + totalBorder.x);

    addBorders(slotSize + totalBorder, position, fillColor);

    return position + border;
}

void Layout::addBorders(const sf::Vector2f& size, const sf::Vector2f& position,
    const sf::Color& fillColor)
{
    sf::Vector2f shift(thickness_, thickness_);

    components_.push_back(createRectangle(size, position, sf::Color::White, sf::Color::Transparent,
        thickness_));
    components_.push_back(createRectangle(size - 2.0f * shift, position + shift, sf::Color::Black,
        sf::Color::Transparent, 2.0f * thickness_));
    components_.push_back(createRectangle(size - 4.0f * shift, position + 2.0f * shift,
        sf::Color::White, fillColor, thickness_));
}

sf::RectangleShape Layout::createRectangle(const sf::Vector2f& size,
    const sf::Vector2f& position,
    const sf::Color& outlineColor,
    const sf::Color& fillColor,
    float thickness) const
{
    sf::RectangleShape rectangle(size);
    rectangle.setPosition(position);
    rectangle.setFillColor(fillColor);
    rectangle.setOutlineThickness(-thickness);
    rectangle.setOutlineColor(outlineColor);
    return rectangle;
}

void Layout::draw() const {
    Renderer::TargetProxy target = renderer_->getFixedTarget();

    for (const auto& component : components_) {
        target.get()->draw(component);
    }
}


}
