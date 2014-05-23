/* Copyright 2014 <Piotr Derkowski> */

#ifndef MAPDRAWER_HPP_
#define MAPDRAWER_HPP_

#include <memory>
#include <map>
#include "SFML/Graphics.hpp"
#include "MapModel.hpp"
#include "Resources.hpp"
#include "Tile.hpp"
#include "Coordinates.hpp"

class MapDrawer {
public:
    MapDrawer(std::shared_ptr<MapModel> model, std::shared_ptr<sf::RenderTarget> target,
        Resources& resources);

    void draw() const;

    std::shared_ptr<const sf::RenderTarget> getTarget() const;

    std::shared_ptr<Tile> getObjectByPosition(const sf::Vector2i& position);
    std::shared_ptr<const Tile> getObjectByPosition(const sf::Vector2i& position) const;
    void scrollView(int x, int y);
    void zoomViem(int delta, const sf::Vector2i& mousePosition);

    sf::FloatRect getDisplayedRect() const;

private:
    IntIsoPoint mapPixelToMapCoords(const sf::Vector2i& position);

    unsigned getMapWidth() const;
    unsigned getMapHeight() const;

    bool canZoom(int delta) const;
    sf::Vector2f boundShift(int x, int y) const;
    sf::Vector2f getCoordsAfterZoom(int delta, const sf::Vector2i& mousePosition) const;

    std::shared_ptr<MapModel> model_;
    std::shared_ptr<sf::RenderTarget> target_;

    sf::View mapView_;
    std::map<Tile::Type, sf::Texture> tileTextures_;

    int tileWidth_;
    int tileHeight_;
};

#endif  // MAPDRAWER_HPP_
