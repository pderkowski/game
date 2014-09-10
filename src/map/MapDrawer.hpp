/* Copyright 2014 <Piotr Derkowski> */

#ifndef MAP_MAPDRAWER_HPP_
#define MAP_MAPDRAWER_HPP_


#include <vector>
#include "SFML/Graphics.hpp"
#include "MapModel.hpp"
#include "Tile.hpp"
#include "Layer.hpp"
#include "Renderer.hpp"


namespace map {


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


}  // namespace map

#endif  // MAP_MAPDRAWER_HPP_
