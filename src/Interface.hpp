/* Copyright 2014 <Piotr Derkowski> */

#ifndef INTERFACE_HPP_
#define INTERFACE_HPP_

#include <vector>
#include "SFML/Graphics.hpp"
class Renderer;

class Interface {
public:
    Interface(const Renderer* renderer, const sf::Vector2f& minimapSize);

    sf::Vector2f getMinimapSlotPosition() const;

    void draw() const;

private:
    void addBorders(const sf::Vector2f& size, const sf::Vector2f& position);

    sf::RectangleShape createTransparentRectangle(const sf::Vector2f& size,
        const sf::Vector2f& position,
        const sf::Color& outlineColor,
        float thickness) const;

private:
    const Renderer* renderer_;

    std::vector<sf::RectangleShape> components_;

    const sf::Vector2f minimapSize_;
    float thickness_;
};

#endif  // INTERFACE_HPP_
