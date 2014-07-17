/* Copyright 2014 <Piotr Derkowski> */

#ifndef MAP_HPP_
#define MAP_HPP_

#include <vector>
#include <memory>
#include "SFML/Graphics.hpp"
#include "MapModel.hpp"
#include "MapDrawer.hpp"
#include "MinimapDrawer.hpp"
#include "Tile.hpp"
#include "TileEnums.hpp"
#include "units/Unit.hpp"
#include "Selection.hpp"
#include "Player.hpp"

class Map {
public:
    Map(int rows, int columns, std::shared_ptr<sf::RenderWindow> target);

    void draw() const;

    void generateMap();

    void handleLeftClick(const sf::Event& e);
    void handleRightClick(const sf::Event& e);
    void handleMouseWheelMoved(const sf::Event& event);
    void handleMouseMoved(const sf::Event& event);
    void handleAPressed();

    void setPlayer(Player* player);

private:
    void moveUnit(tileenums::Direction direction);

    int calculateHorizontalShift(float mouseXPosition) const;
    int calculateVerticalShift(float mouseYPosition) const;

    std::shared_ptr<MapModel> model_;
    MapDrawer mapDrawer_;
    MinimapDrawer minimapDrawer_;
    Selection selection_;
    Player* currentPlayer_;
};

#endif  // MAP_HPP_
