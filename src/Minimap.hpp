/* Copyright 2014 <Piotr Derkowski> */

#ifndef MINIMAP_HPP_
#define MINIMAP_HPP_

#include <map>
#include "SFML/Graphics.hpp"
#include "MapModel.hpp"
#include "TileEnums.hpp"
#include "MapRenderer.hpp"
#include "players/Fog.hpp"

class Minimap {
public:
    Minimap(const MapModel* model, const players::Fog& fog, const MapRenderer* renderer);

    void draw() const;

    void updateFocus();
    void rebuild(const MapModel* model, const players::Fog& fog);

private:
    sf::RectangleShape createMinimapBorders();
    sf::RectangleShape createDisplayedRectangle();
    sf::Texture createMinimapBackground();

    sf::Image createMinimapImage();
    sf::Uint8* createMinimapPixels();

    sf::Color getPixelColor(int row, int column) const;

private:
    const MapModel* model_;

    players::Fog fog_;

    const MapRenderer* renderer_;

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

#endif  // MINIMAP_HPP_
