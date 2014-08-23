/* Copyright 2014 <Piotr Derkowski> */

#include "Map.hpp"
#include "Renderer.hpp"
#include "MapGenerator.hpp"

Map::Map(int rows, int columns, const Renderer* renderer)
    : model_(MapGenerator::generateMap(rows, columns)),
    mapDrawer_(model_, renderer)
{ }

void Map::draw() const {
    mapDrawer_.draw();
}
const MapModel* Map::getModel() const {
    return &model_;
}

void Map::generateMap() {
    model_ = MapGenerator::generateMap(model_.getRowsNo(), model_.getColumnsNo());
    mapDrawer_.setModel(model_);
}
