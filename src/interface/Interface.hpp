/* Copyright 2014 <Piotr Derkowski> */

#ifndef INTERFACE_INTERFACE_HPP_
#define INTERFACE_INTERFACE_HPP_

#include <vector>
#include "SFML/Graphics.hpp"
class Renderer;


namespace interface {


class Interface {
public:
    explicit Interface(const Renderer* renderer);

    sf::Vector2f addSlot(const sf::Vector2f& slotSize,
        const sf::Color& fillColor = sf::Color::Transparent);
    void draw() const;

private:
    void addBorders(const sf::Vector2f& size, const sf::Vector2f& position,
        const sf::Color& fillColor);

    sf::RectangleShape createRectangle(const sf::Vector2f& size,
        const sf::Vector2f& position,
        const sf::Color& outlineColor,
        const sf::Color& fillColor,
        float thickness) const;

private:
    const Renderer* renderer_;

    std::vector<sf::RectangleShape> components_;

    sf::Vector2f availableSlotPosition_;
    float thickness_;
};


}

#endif  // INTERFACE_INTERFACE_HPP_
