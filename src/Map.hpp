/* Copyright 2014 <Piotr Derkowski> */

#ifndef MAP_HPP_
#define MAP_HPP_

#include <vector>
#include <memory>
#include "SFML/Graphics.hpp"
#include "MapModel.hpp"
#include "MapDrawer.hpp"
class Renderer;


class Map {
public:
    Map(int rows, int columns, Renderer* renderer);

    void draw() const;

    std::shared_ptr<const MapModel> getModel() const;

    void generateMap();

    void handleMouseWheelMoved(const sf::Event& event);
    sf::Vector2f scrollView();

private:
    int calculateHorizontalShift(int mouseXPosition) const;
    int calculateVerticalShift(int mouseYPosition) const;

private:
    std::shared_ptr<MapModel> model_;

    Renderer* renderer_;

    MapDrawer mapDrawer_;
};

#endif  // MAP_HPP_
