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

    virtual ~MapDrawer() { }

    virtual void draw() const;

    std::shared_ptr<Tile> getObjectByPosition(const sf::Vector2i& position);
    void scrollView(int x, int y);
    void zoomViemBy(int delta);

    sf::IntRect getDisplayedTilesRect() const;

private:
    float getMapWidth() const;
    float getMapHeight() const;

    int mapXCoordsToColumn(int x) const;
    int mapYCoordsToRow(int y) const;

    float calculateHorizontalShift(float mouseXPosition) const;
    float calculateVerticalShift(float mouseYPosition) const;

    std::shared_ptr<MapModel> model_;
    std::shared_ptr<sf::RenderTarget> target_;

    sf::View mapView_;
    std::map<Tile::Type, sf::Texture> tileTextures_;
    sf::Vector2f offset_;

    static const int scrollMarginSize_ = 20;

    int tileSize_;
};

#endif  // MAPDRAWER_HPP_
