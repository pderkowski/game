/* Copyright 2014 <Piotr Derkowski> */

#ifndef MAP_HPP_
#define MAP_HPP_

#include <vector>
#include <memory>
#include "SFML/Graphics.hpp"
#include "MapModel.hpp"
#include "MapDrawer.hpp"
#include "MapRenderer.hpp"

class Map {
public:
    Map(int rows, int columns, std::shared_ptr<sf::RenderTarget> target);

    void draw() const;

    std::shared_ptr<const MapModel> getModel() const;
    const MapRenderer* getRenderer() const;

    void generateMap();

    void handleMouseWheelMoved(const sf::Event& event);
    sf::Vector2f scrollView();

private:
    int calculateHorizontalShift(int mouseXPosition) const;
    int calculateVerticalShift(int mouseYPosition) const;

    std::shared_ptr<MapModel> model_;

    MapRenderer renderer_;

    MapDrawer mapDrawer_;
};

#endif  // MAP_HPP_
