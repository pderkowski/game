/* Copyright 2014 <Piotr Derkowski> */

#ifndef MAP_MAP_HPP_
#define MAP_MAP_HPP_

#include "MapModel.hpp"
#include "MapDrawer.hpp"
class Renderer;


namespace map {


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


}  // namespace map

#endif  // MAP_MAP_HPP_

