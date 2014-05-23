/* Copyright 2014 <Piotr Derkowski> */

#ifndef MINIMAPDRAWER_HPP_
#define MINIMAPDRAWER_HPP_

#include <memory>
#include <map>
#include "SFML/Graphics.hpp"
#include "Resources.hpp"
#include "MapModel.hpp"
#include "Tile.hpp"

class MinimapDrawer {
public:
    MinimapDrawer(std::shared_ptr<const MapModel>, std::shared_ptr<sf::RenderTarget> target,
        Resources& resources);

    void updateView(const sf::FloatRect& bounds);

    void draw() const;

    void rebuild();

private:
    sf::RectangleShape createBorders();
    sf::RectangleShape createView();
    sf::Texture createBackground();

    sf::Image createMinimapImage();
    sf::Uint8* createMinimapPixels();

    sf::Color getColorFromModel(int row, int column) const;
    sf::Vector2f getBasePosition() const;

    std::shared_ptr<const MapModel> model_;
    std::shared_ptr<sf::RenderTarget> target_;

    int horizontalPixelsPerTile_;
    int verticalPixelsPerTile_;
    int width_;
    int height_;

    std::map<Tile::Type, sf::Color> tileColors_;

    sf::RectangleShape borders_;
    sf::RectangleShape view_;
    sf::Texture background_;
    sf::RenderTexture minimap_;
};

#endif  // MINIMAPDRAWER_HPP_
