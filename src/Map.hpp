/* Copyright 2014 <Piotr Derkowski> */

#ifndef MAP_HPP_
#define MAP_HPP_

#include "MapModel.hpp"
#include "MapDrawer.hpp"
class Renderer;


class Map {
public:
    Map(int rowsNo, int columnsNo, const Renderer* renderer);

    void draw() const;

    const MapModel* getModel() const;

    void generateMap();

private:
    MapModel model_;

    MapDrawer mapDrawer_;

};

#endif  // MAP_HPP_

