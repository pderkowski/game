/* Copyright 2014 <Piotr Derkowski> */

#ifndef MINIMAP_HPP_
#define MINIMAP_HPP_

#include <map>
#include <functional>
#include "SFML/Graphics.hpp"
#include "MapModel.hpp"
#include "TileEnums.hpp"
#include "MapRenderer.hpp"
#include "players/Fog.hpp"

class Minimap {
public:
    Minimap(const MapModel* model, const players::Fog& fog, const MapRenderer* renderer);

    void draw() const;

    void updateDisplayedRectangle();
    void updateFog(const players::Fog& fog);

    void toggleFog();

    void rebuild(const MapModel* model, const players::Fog& fog);

private:
    sf::RectangleShape createMinimapBorders();

    sf::RectangleShape createDisplayedRectangle();

    sf::Texture createTexture(std::function<sf::Color(int row, int column)> pixelGetter);
    sf::Image createImageFromPixels(sf::Uint8* pixels);
    sf::Uint8* createPixels(std::function<sf::Color(int row, int column)> pixelGetter);

    sf::Color getBackgroundPixel(int row, int column) const;
    sf::Color getFogPixel(int row, int column) const;

    void render();

private:
    const MapModel* model_;

    players::Fog fog_;

    const MapRenderer* renderer_;

    std::map<tileenums::Type, sf::Color> tileColors_;

    int horizontalPixelsPerTile_;
    int verticalPixelsPerTile_;
    int width_;
    int height_;

    bool isFogToggledOn_;

    sf::RectangleShape minimapBorders_;
    sf::RectangleShape displayedRectangle_;
    sf::Texture minimapBackground_;
    sf::Texture fogTexture_;
    sf::RenderTexture minimap_;
};

#endif  // MINIMAP_HPP_
