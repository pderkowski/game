/* Copyright 2014 <Piotr Derkowski> */

#include <iostream>
#include <memory>
#include <map>
#include "SFML/Graphics.hpp"
#include "MapModel.hpp"
#include "Resources.hpp"
#include "MinimapDrawer.hpp"
#include "Tile.hpp"
#include "Coordinates.hpp"

MinimapDrawer::MinimapDrawer(std::shared_ptr<const MapModel> model,
    std::shared_ptr<sf::RenderTarget> target,
    Resources& resources)
        : model_(model),
        target_(target),
        horizontalPixelsPerTile_(2),
        verticalPixelsPerTile_(horizontalPixelsPerTile_ / 2),
        width_(IsoPoint(model->getColumnsNo(), 0 ).toCartesian().x * horizontalPixelsPerTile_),
        height_(IsoPoint(0, model->getRowsNo()).toCartesian().y * verticalPixelsPerTile_),
        tileColors_{
            { Tile::Type::Empty, resources.loadImage("tiles/empty.png").getPixel(0, 0) },
            { Tile::Type::Water, resources.loadImage("tiles/water.png").getPixel(0, 0) },
            { Tile::Type::Hills, resources.loadImage("tiles/hills.png").getPixel(0, 0) },
            { Tile::Type::Plains, resources.loadImage("tiles/plains.png").getPixel(0, 0) },
            { Tile::Type::Mountains, resources.loadImage("tiles/mountains.png").getPixel(0, 0) }
        },
        borders_(createBorders()),
        view_(createView()),
        background_(createBackground())
{
    minimap_.create(width_, height_);
}

void MinimapDrawer::rebuild() {
    background_ = createBackground();
}

sf::RectangleShape MinimapDrawer::createBorders() {
    sf::RectangleShape borders;
    borders.setSize(sf::Vector2f(width_, height_));
    borders.setFillColor(sf::Color(0, 0, 0, 0));
    borders.setOutlineColor(sf::Color(0, 0, 0, 255));
    borders.setOutlineThickness(-1);
    return borders;
}

sf::RectangleShape MinimapDrawer::createView() {
    sf::RectangleShape view;
    view.setSize(sf::Vector2f(width_, height_));
    view.setFillColor(sf::Color(255, 255, 255, 100));
    view.setOutlineColor(sf::Color(255, 255, 255, 255));
    view.setOutlineThickness(-1);
    return view;
}

sf::Texture MinimapDrawer::createBackground() {
    sf::Texture background;
    background.loadFromImage(createMinimapImage());
    return background;
}

sf::Image MinimapDrawer::createMinimapImage() {
    sf::Uint8* pixels;
    try {
        pixels = createMinimapPixels();
        sf::Image image;
        image.create(width_, height_, pixels);
        delete[] pixels;
        return image;
    } catch (...) {
        delete[] pixels;
        throw;
    }
}

sf::Uint8* MinimapDrawer::createMinimapPixels() {
    sf::Uint8* pixels = new sf::Uint8[4 * width_ * height_];

    for (int r = 0; r < height_; ++r) {
        for (int c = 0; c < width_; ++c) {
            int pixelNo = (r * width_ + c) * 4;

            sf::Color color = getColorFromModel(r / verticalPixelsPerTile_,
                c / horizontalPixelsPerTile_);
            pixels[pixelNo + 0] = color.r;
            pixels[pixelNo + 1] = color.g;
            pixels[pixelNo + 2] = color.b;
            pixels[pixelNo + 3] = color.a;
        }
    }

    return pixels;
}

sf::Color MinimapDrawer::getColorFromModel(int row, int column) const {
    IntIsoPoint p(CartPoint(column, row).toIsometric());
    return tileColors_.at(model_->getTile(p)->type);
}

void MinimapDrawer::draw() const {
    sf::Sprite minimapSprite;
    minimapSprite.setTexture(minimap_.getTexture());
    minimapSprite.setPosition(getBasePosition());
    target_->draw(minimapSprite);
}

void MinimapDrawer::updateView(const sf::FloatRect& bounds) {
    minimap_.clear();
    minimap_.draw(sf::Sprite(background_));
    view_.setPosition(sf::Vector2f(bounds.left * width_, bounds.top * height_));
    view_.setSize(sf::Vector2f(bounds.width * width_, bounds.height * height_));
    minimap_.draw(view_);
    view_.move(-width_, 0);
    minimap_.draw(view_);
    minimap_.draw(borders_);
    minimap_.display();
}

sf::Vector2f MinimapDrawer::getBasePosition() const {
    return target_->mapPixelToCoords(
        sf::Vector2i(target_->getSize().x - width_, target_->getSize().y - height_));
}
