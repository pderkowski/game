/* Copyright 2014 <Piotr Derkowski> */

#include "SFML/Graphics.hpp"
#include "MapRenderer.hpp"
#include "Interface.hpp"

Interface::Interface(const MapRenderer* renderer, const sf::Vector2f& minimapSize)
    : renderer_(renderer),
    minimapSize_(minimapSize),
    thickness_(1.0f)
{
    const sf::Vector2f totalShift(8 * thickness_, 8 * thickness_);
    const sf::Vector2f rendererSize = sf::Vector2f(renderer_->getSize());

    addBorders(sf::Vector2f(renderer_->getSize()), sf::Vector2f());
    addBorders(minimapSize + totalShift, rendererSize - minimapSize - totalShift);
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
    MapRenderer::TargetProxy target = renderer_->getFixedTarget();

    for (const auto& component : components_) {
        target.get()->draw(component);
    }
}

sf::Vector2f Interface::getMinimapSlotPosition() const {
    const sf::Vector2f border(4 * thickness_, 4 * thickness_);
    const sf::Vector2f rendererSize = sf::Vector2f(renderer_->getSize());

    return rendererSize - minimapSize_ - border;
}


