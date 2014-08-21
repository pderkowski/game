/* Copyright 2014 <Piotr Derkowski> */

#ifndef MINIMAP_HPP_
#define MINIMAP_HPP_

#include <map>
#include "SFML/Graphics.hpp"
#include "MapModel.hpp"
#include "TileEnums.hpp"
#include "Renderer.hpp"
#include "players/Players.hpp"

class Minimap {
public:
    Minimap(const MapModel* model, const players::Players* players, const Renderer* renderer);

    void draw() const;

    void updateDisplayedRectangle();
    void updateBackground();

    void setModel(const MapModel* model);

    sf::Vector2f getSize();

    void setPosition(const sf::Vector2f& position);

private:
    sf::RectangleShape createDisplayedRectangle();

    sf::Texture createTexture();
    sf::Image createImageFromPixels(sf::Uint8* pixels);
    sf::Uint8* createPixels();

    sf::Color getPixel(int row, int column) const;

    void render();

private:
    const MapModel* model_;

    const players::Players* players_;

    const Renderer* renderer_;

    std::map<tileenums::Type, sf::Color> tileColors_;

    int horizontalPixelsPerTile_;
    int verticalPixelsPerTile_;
    int width_;
    int height_;

    sf::RectangleShape displayedRectangle_;
    sf::Texture minimapBackground_;
    sf::RenderTexture minimap_;

    sf::Vector2f basePosition_;
};

#endif  // MINIMAP_HPP_
