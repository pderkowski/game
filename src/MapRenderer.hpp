/* Copyright 2014 <Piotr Derkowski> */

#ifndef MAPRENDERER_HPP_
#define MAPRENDERER_HPP_

#include <vector>
#include <memory>
#include "Coordinates.hpp"
#include "SFML/Graphics.hpp"

class MapRenderer {
public:
    MapRenderer(int rows, int columns, int tileWidth, int tileHeight,
        std::shared_ptr<sf::RenderTarget> target);

    sf::Vector2f getPosition(const IntIsoPoint& coords) const;
    sf::Vector2f getDualPosition(const IntIsoPoint& coords) const;

    unsigned getMapWidth() const;
    unsigned getMapHeight() const;

    sf::Vector2u getSize() const;

    std::shared_ptr<sf::RenderTarget> getFixedView() const;
    std::shared_ptr<sf::RenderTarget> getDynamicView() const;

    IntIsoPoint getMapCoords(const sf::Vector2i& position) const;

    void scrollView(int x, int y);
    void zoomView(int delta, const sf::Vector2i& mousePosition);

    sf::FloatRect getDisplayedRectangle() const;

private:
    bool canZoom(float delta) const;
    sf::Vector2f boundShift(int x, int y) const;

private:
    int rows_;
    int columns_;
    int tileWidth_;
    int tileHeight_;

    std::shared_ptr<sf::RenderTarget> target_;

    sf::View mapView_;
};

#endif  // MAPRENDERER_HPP_
