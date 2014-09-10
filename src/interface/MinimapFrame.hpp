/* Copyright 2014 <Piotr Derkowski> */

#ifndef INTERFACE_MINIMAPFRAME_HPP_
#define INTERFACE_MINIMAPFRAME_HPP_

#include "SFML/Graphics.hpp"
#include "MinimapRenderer.hpp"
namespace map { class MapModel; }
class Renderer;
namespace players { class Players; }


namespace interface {


class MinimapFrame {
public:
    explicit MinimapFrame(const map::MapModel& model, const Renderer* renderer);

    void setPosition(const sf::Vector2f& position);

    sf::Vector2f getSize() const;

    void updateBackground(const map::MapModel& model, const players::Player& player);
    void updateDisplayedRectangle();

    void draw() const;

private:
    const Renderer* renderer_;

    MinimapRenderer minimapRenderer_;

    sf::Vector2f position_;
};


}  // namespace interface

#endif  // INTERFACE_MINIMAPFRAME_HPP_
