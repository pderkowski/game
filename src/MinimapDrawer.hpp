/* Copyright 2014 <Piotr Derkowski> */

#ifndef MINIMAPDRAWER_HPP_
#define MINIMAPDRAWER_HPP_

#include <memory>
#include <map>
#include "SFML/Graphics.hpp"
#include "Resources.hpp"
#include "MapModel.hpp"
#include "Tile.hpp"
#include "TileEnums.hpp"

class MinimapDrawer {
public:
    MinimapDrawer(std::shared_ptr<const MapModel>, std::shared_ptr<sf::RenderTarget> target);

    void updateMinimap(const sf::FloatRect& boundsOfDisplayedRectangle);

    void draw() const;

    void setModel(std::shared_ptr<const MapModel> model);

private:
    sf::RectangleShape createMinimapBorders();
    sf::RectangleShape createDisplayedRectangle();
    sf::Texture createMinimapBackground();

    sf::Image createMinimapImage();
    sf::Uint8* createMinimapPixels();

    sf::Color getColorFromModel(int row, int column) const;
    sf::Vector2f getBasePosition() const;

    std::shared_ptr<const MapModel> model_;
    std::shared_ptr<sf::RenderTarget> target_;

    std::map<tileenums::Type, sf::Color> tileColors_;

    int horizontalPixelsPerTile_;
    int verticalPixelsPerTile_;
    int width_;
    int height_;

    sf::RectangleShape minimapBorders_;
    sf::RectangleShape displayedRectangle_;
    sf::Texture minimapBackground_;
    sf::RenderTexture minimap_;
};

#endif  // MINIMAPDRAWER_HPP_
