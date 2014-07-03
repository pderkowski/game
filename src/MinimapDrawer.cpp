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
    std::shared_ptr<sf::RenderTarget> target)
        : model_(model),
        target_(target),
        tileColors_{
            { Tile::Type::Empty, sf::Color(160, 160, 160) },
            { Tile::Type::Water, sf::Color(127, 201, 255) },
            { Tile::Type::Hills, sf::Color(198, 148, 4) },
            { Tile::Type::Plains, sf::Color(77, 173, 36) },
            { Tile::Type::Forest, sf::Color(77, 173, 36) },
            { Tile::Type::Desert, sf::Color(224, 192, 121) },
            { Tile::Type::Grassland, sf::Color(77, 173, 36) },
            { Tile::Type::Mountains, sf::Color(101, 61, 1) }
        },
        horizontalPixelsPerTile_(2),
        verticalPixelsPerTile_(horizontalPixelsPerTile_ / 2),
        width_(IsoPoint(model->getColumnsNo(), 0 ).toCartesian().x * horizontalPixelsPerTile_),
        height_(IsoPoint(0, model->getRowsNo()).toCartesian().y * verticalPixelsPerTile_),
        minimapBorders_(createMinimapBorders()),
        displayedRectangle_(createDisplayedRectangle()),
        minimapBackground_(createMinimapBackground())
{
    minimap_.create(width_, height_);
}

void MinimapDrawer::setModel(std::shared_ptr<const MapModel> model) {
    model_ = model;
    width_ = IsoPoint(model->getColumnsNo(), 0 ).toCartesian().x * horizontalPixelsPerTile_;
    height_ = IsoPoint(0, model->getRowsNo()).toCartesian().y * verticalPixelsPerTile_;
    minimapBorders_ = createMinimapBorders();
    displayedRectangle_ = createDisplayedRectangle(),
    minimapBackground_ = createMinimapBackground();
}

sf::RectangleShape MinimapDrawer::createMinimapBorders() {
    sf::RectangleShape borders;
    borders.setSize(sf::Vector2f(width_, height_));
    borders.setFillColor(sf::Color(0, 0, 0, 0));
    borders.setOutlineColor(sf::Color(0, 0, 0, 255));
    borders.setOutlineThickness(-1);
    return borders;
}

sf::RectangleShape MinimapDrawer::createDisplayedRectangle() {
    sf::RectangleShape view;
    view.setSize(sf::Vector2f(width_, height_));
    view.setFillColor(sf::Color(255, 255, 255, 100));
    view.setOutlineColor(sf::Color(255, 255, 255, 255));
    view.setOutlineThickness(-1);
    return view;
}

sf::Texture MinimapDrawer::createMinimapBackground() {
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
    target_->setView(target_->getDefaultView());
    sf::Sprite minimapSprite;
    minimapSprite.setTexture(minimap_.getTexture());
    minimapSprite.setPosition(getBasePosition());
    target_->draw(minimapSprite);
}

void MinimapDrawer::updateMinimap(const sf::FloatRect& bounds) {
    minimap_.clear();
    minimap_.draw(sf::Sprite(minimapBackground_));
    displayedRectangle_.setPosition(sf::Vector2f(bounds.left * width_, bounds.top * height_));
    displayedRectangle_.setSize(sf::Vector2f(bounds.width * width_, bounds.height * height_));
    minimap_.draw(displayedRectangle_);
    displayedRectangle_.move(-width_, 0);
    minimap_.draw(displayedRectangle_);
    minimap_.draw(minimapBorders_);
    minimap_.display();
}

sf::Vector2f MinimapDrawer::getBasePosition() const {
    return target_->mapPixelToCoords(
        sf::Vector2i(target_->getSize().x - width_, target_->getSize().y - height_));
}
