/* Copyright 2014 <Piotr Derkowski> */

#ifndef MAPDRAWER_HPP_
#define MAPDRAWER_HPP_

#include <vector>
#include "SFML/Graphics.hpp"
#include "MapModel.hpp"
#include "Tile.hpp"
#include "Layer.hpp"
#include "MapRenderer.hpp"

class MapDrawer {
public:
    MapDrawer(const MapModel& model, const MapRenderer* renderer);

    void draw() const;

    void setModel(const MapModel& model);

private:
    void addTileToLayers(const Tile& tile);

private:
    std::vector<Layer<Tile>> layers_;

    const MapRenderer* renderer_;
};

#endif  // MAPDRAWER_HPP_
