/* Copyright 2014 <Piotr Derkowski> */

#ifndef MAPRENDERER_HPP_
#define MAPRENDERER_HPP_

#include <vector>
#include <memory>
#include "Coordinates.hpp"
#include "SFML/Graphics.hpp"

class MapRenderer {
public:
    class TargetProxy;

public:
    MapRenderer(int rows, int columns, int tileWidth, int tileHeight,
        std::shared_ptr<sf::RenderTarget> target);

    sf::Vector2f getPosition(const IntIsoPoint& coords) const;
    sf::Vector2f getDualPosition(const IntIsoPoint& coords) const;

    unsigned getMapWidth() const;
    unsigned getMapHeight() const;

    sf::Vector2u getSize() const;

    TargetProxy getFixedTarget() const;
    TargetProxy getDynamicTarget() const;

    IntIsoPoint getMapCoords(const sf::Vector2i& position) const;

    sf::Vector2f scrollView(int x, int y);
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

public:
    class TargetProxy {
    public:
        TargetProxy(const TargetProxy&) = delete;
        TargetProxy& operator =(const TargetProxy&) = delete;

        TargetProxy(TargetProxy&&) = default;
        TargetProxy& operator =(TargetProxy&&) = default;

        ~TargetProxy();

        std::shared_ptr<sf::RenderTarget> get() const;
    private:
        friend class MapRenderer;

        TargetProxy(const MapRenderer* renderer, const sf::View& savedView);

    private:
        const MapRenderer* renderer_;

        sf::View savedView_;
    };
};

#endif  // MAPRENDERER_HPP_
