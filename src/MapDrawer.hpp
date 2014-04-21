/* Copyright 2014 <Piotr Derkowski> */

#ifndef MAPDRAWER_HPP_
#define MAPDRAWER_HPP_

#include <memory>
#include <map>
#include "SFML/Graphics.hpp"
#include "MapModel.hpp"
#include "Resources.hpp"
#include "Tile.hpp"

class MapDrawer {
public:
    MapDrawer(std::shared_ptr<MapModel> model, std::shared_ptr<sf::RenderTarget> target,
        Resources& resources);

    void draw() const;

    std::shared_ptr<const sf::RenderTarget> getTarget() const;

    std::shared_ptr<Tile> getObjectByPosition(const sf::Vector2i& position);
    void scrollView(float x, float y);
    void zoomViem(int delta, const sf::Vector2i& mousePosition);

    sf::IntRect getDisplayedTilesRect() const;

private:
    float getMapWidth(int tileSize) const;
    float getMapHeight(int tileSize) const;

    int mapXCoordsToColumn(int x) const;
    int mapYCoordsToRow(int y) const;

    bool canZoom(int delta) const;
    sf::Vector2f boundShift(float x, float y) const;
    sf::Vector2f getCoordsAfterZoom(int delta, const sf::Vector2i& mousePosition) const;

    std::shared_ptr<MapModel> model_;
    std::shared_ptr<sf::RenderTarget> target_;

    sf::View mapView_;
    std::map<Tile::Type, sf::Texture> tileTextures_;
    sf::Vector2f offset_;

    int tileSize_;
};

#endif  // MAPDRAWER_HPP_
