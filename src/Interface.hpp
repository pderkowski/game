/* Copyright 2014 <Piotr Derkowski> */

#ifndef INTERFACE_HPP_
#define INTERFACE_HPP_

#include <vector>
#include "SFML/Graphics.hpp"
class Renderer;

class Interface {
public:
    explicit Interface(const Renderer* renderer);

    sf::Vector2f addSlot(const sf::Vector2f& slotSize);

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

    sf::Vector2f availableSlotPosition_;
    float thickness_;
};

#endif  // INTERFACE_HPP_
