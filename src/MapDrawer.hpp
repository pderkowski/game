/* Copyright 2014 <Piotr Derkowski> */

#ifndef MAPDRAWER_HPP_
#define MAPDRAWER_HPP_

#include <memory>
#include <map>
#include <vector>
#include "SFML/Graphics.hpp"
#include "MapModel.hpp"
#include "Tile.hpp"
#include "Coordinates.hpp"
#include "Layer.hpp"
#include "TextureSet.hpp"

class MapDrawer {
public:
    MapDrawer(std::shared_ptr<MapModel> model, std::shared_ptr<sf::RenderTarget> target);

    void draw() const;

    void setModel(std::shared_ptr<MapModel> model);

    std::shared_ptr<const sf::RenderTarget> getTarget() const;

    std::shared_ptr<Tile> getObjectByPosition(const sf::Vector2i& position);
    std::shared_ptr<const Tile> getObjectByPosition(const sf::Vector2i& position) const;
    void scrollView(int x, int y);
    void zoomViem(int delta, const sf::Vector2i& mousePosition);

    sf::FloatRect getDisplayedRectangle() const;

private:
    void makeLayers();
    void addTileToLayers(std::shared_ptr<const Tile> tile);

    IntIsoPoint mapPixelToMapCoords(const sf::Vector2i& position);

    unsigned getMapWidth() const;
    unsigned getMapHeight() const;

    bool canZoom(float delta) const;
    sf::Vector2f boundShift(int x, int y) const;

    std::shared_ptr<MapModel> model_;
    std::shared_ptr<sf::RenderTarget> target_;

    int tileWidth_;
    int tileHeight_;

    sf::View mapView_;

    std::vector<Layer> layers_;
};

#endif  // MAPDRAWER_HPP_
