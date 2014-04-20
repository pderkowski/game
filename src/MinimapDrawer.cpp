/* Copyright 2014 <Piotr Derkowski> */

#include <iostream>
#include <memory>
#include <map>
#include "SFML/Graphics.hpp"
#include "MapModel.hpp"
#include "Resources.hpp"
#include "MinimapDrawer.hpp"
#include "Tile.hpp"

MinimapDrawer::MinimapDrawer(std::shared_ptr<const MapModel> model,
    std::shared_ptr<sf::RenderTarget> target,
    Resources& resources)
        : model_(model),
        target_(target),
        tileColors_{  // NOLINT
            { Tile::Type::Empty, resources.loadImage("tiles/empty.png").getPixel(0, 0) },
            { Tile::Type::Water, resources.loadImage("tiles/water.png").getPixel(0, 0) },
            { Tile::Type::Hills, resources.loadImage("tiles/hills.png").getPixel(0, 0) },
            { Tile::Type::Plains, resources.loadImage("tiles/plains.png").getPixel(0, 0) },
            { Tile::Type::Mountains, resources.loadImage("tiles/mountains.png").getPixel(0, 0) }
        },
        pixelsPerTile_(2),
        width_(pixelsPerTile_ * model->getColumnsNo()),
        height_(pixelsPerTile_ * model->getRowsNo()) {
    createMinimap();
}

void MinimapDrawer::createMinimap() {
    borders_ = createBorders();

    minimapTexture_.loadFromImage(createMinimapImage());
    minimapSprite_.setTexture(minimapTexture_);
}

void MinimapDrawer::draw() const {
    sf::Vector2f position = target_->mapPixelToCoords(
        sf::Vector2i(target_->getSize().x - width_, target_->getSize().y - height_));

    borders_.setPosition(position);
    minimapSprite_.setPosition(position);
    target_->draw(borders_);
    target_->draw(minimapSprite_);
}

sf::Image MinimapDrawer::createMinimapImage() {
    sf::Uint8* pixels;
    try {
        pixels = createMinimapPixels();
        sf::Image image;
        image.create(width_, height_, pixels);
        delete[] pixels;
        return image;
    } catch (...) {  // NOLINT
        delete[] pixels;
        throw;
    }
}

sf::RectangleShape MinimapDrawer::createBorders() {
    sf::RectangleShape borders;
    borders.setSize(sf::Vector2f(width_, height_));
    borders.setFillColor(sf::Color(0, 0, 0, 0));
    borders.setOutlineColor(sf::Color(0, 0, 0, 255));
    borders.setOutlineThickness(2);
    return borders;
}

sf::Uint8* MinimapDrawer::createMinimapPixels() {
    sf::Uint8* pixels = new sf::Uint8[4 * width_ * height_];

    int columns = model_->getColumnsNo() * pixelsPerTile_;
    int rows = model_->getRowsNo() * pixelsPerTile_;
    for (int r = 0; r < rows; ++r) {
        for (int c = 0; c < columns; ++c) {
            int pixelNo = (r * columns + c) * 4;

            sf::Color color = getColorFromModel(r / pixelsPerTile_, c / pixelsPerTile_);
            pixels[pixelNo + 0] = color.r;
            pixels[pixelNo + 1] = color.g;
            pixels[pixelNo + 2] = color.b;
            pixels[pixelNo + 3] = color.a;
        }
    }

    return pixels;
}

sf::Color MinimapDrawer::getColorFromModel(int row, int column) const {
    return tileColors_.at(model_->getTile(row, column)->getType());
}
