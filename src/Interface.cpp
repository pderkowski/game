/* Copyright 2014 <Piotr Derkowski> */

#include "SFML/Graphics.hpp"
#include "Renderer.hpp"
#include "Interface.hpp"

Interface::Interface(const Renderer* renderer)
    : renderer_(renderer),
    availableSlotPosition_(renderer_->getSize()),
    thickness_(1.0f)
{
    addBorders(sf::Vector2f(renderer_->getSize()), sf::Vector2f());
}

sf::Vector2f Interface::addSlot(const sf::Vector2f& slotSize) {
    const sf::Vector2f border(4 * thickness_, 4 * thickness_);
    const sf::Vector2f totalBorder = 2.0f * border;

    const sf::Vector2f position = availableSlotPosition_ - (slotSize + totalBorder);
    availableSlotPosition_.y -= (slotSize.y + totalBorder.y);

    addBorders(slotSize + totalBorder, position);

    return position + border;
}

void Interface::addBorders(const sf::Vector2f& size, const sf::Vector2f& position) {
    sf::Vector2f shift(thickness_, thickness_);

    components_.push_back(createTransparentRectangle(size, position, sf::Color::White, thickness_));
    components_.push_back(createTransparentRectangle(size - 2.0f * shift,
        position + shift,
        sf::Color::Black,
        2.0f * thickness_));
    components_.push_back(createTransparentRectangle(size - 4.0f * shift,
        position + 2.0f * shift,
        sf::Color::White,
        thickness_));
}

sf::RectangleShape Interface::createTransparentRectangle(const sf::Vector2f& size,
    const sf::Vector2f& position,
    const sf::Color& outlineColor,
    float thickness) const
{
    sf::RectangleShape rectangle(size);
    rectangle.setPosition(position);
    rectangle.setFillColor(sf::Color::Transparent);
    rectangle.setOutlineThickness(-thickness);
    rectangle.setOutlineColor(outlineColor);
    return rectangle;
}

void Interface::draw() const {
    Renderer::TargetProxy target = renderer_->getFixedTarget();

    for (const auto& component : components_) {
        target.get()->draw(component);
    }
}
