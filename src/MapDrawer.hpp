/* Copyright 2014 <Piotr Derkowski> */

#ifndef MAPDRAWER_HPP_
#define MAPDRAWER_HPP_

#include <vector>
#include "SFML/Graphics.hpp"
#include "MapModel.hpp"
#include "Tile.hpp"
#include "Layer.hpp"
#include "Renderer.hpp"

class MapDrawer {
public:
    MapDrawer(const MapModel& model, const Renderer* renderer);

    void draw() const;

    void setModel(const MapModel& model);

private:
    void addTileToLayers(const Tile& tile);

private:
    std::vector<Layer<Tile>> layers_;

    const Renderer* renderer_;
};

#endif  // MAPDRAWER_HPP_
