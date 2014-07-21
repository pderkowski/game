/* Copyright 2014 <Piotr Derkowski> */

#include <map>
#include "SFML/Graphics.hpp"
#include "MapModel.hpp"
#include "Resources.hpp"
#include "Minimap.hpp"
#include "Tile.hpp"
#include "Coordinates.hpp"
#include "TileEnums.hpp"
#include "MapRenderer.hpp"

Minimap::Minimap(const MapModel* model, const MapRenderer* renderer)
    : model_(model),
    renderer_(renderer),
    tileColors_{
        { tileenums::Type::Empty, sf::Color(160, 160, 160) },
        { tileenums::Type::Water, sf::Color(127, 201, 255) },
        { tileenums::Type::Hills, sf::Color(198, 148, 4) },
        { tileenums::Type::Plains, sf::Color(77, 173, 36) },
        { tileenums::Type::Forest, sf::Color(77, 173, 36) },
        { tileenums::Type::Desert, sf::Color(224, 192, 121) },
        { tileenums::Type::Grassland, sf::Color(77, 173, 36) },
        { tileenums::Type::Mountains, sf::Color(101, 61, 1) }
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

    update();
}

void Minimap::setModel(const MapModel* model) {
    model_ = model;
    width_ = IsoPoint(model->getColumnsNo(), 0 ).toCartesian().x * horizontalPixelsPerTile_;
    height_ = IsoPoint(0, model->getRowsNo()).toCartesian().y * verticalPixelsPerTile_;
    minimapBorders_ = createMinimapBorders();
    displayedRectangle_ = createDisplayedRectangle(),
    minimapBackground_ = createMinimapBackground();

    update();
}

sf::RectangleShape Minimap::createMinimapBorders() {
    sf::RectangleShape borders;
    borders.setSize(sf::Vector2f(width_, height_));
    borders.setFillColor(sf::Color(0, 0, 0, 0));
    borders.setOutlineColor(sf::Color(0, 0, 0, 255));
    borders.setOutlineThickness(-1);
    return borders;
}

sf::RectangleShape Minimap::createDisplayedRectangle() {
    sf::RectangleShape view;
    view.setSize(sf::Vector2f(width_, height_));
    view.setFillColor(sf::Color(255, 255, 255, 100));
    view.setOutlineColor(sf::Color(255, 255, 255, 255));
    view.setOutlineThickness(-1);
    return view;
}

sf::Texture Minimap::createMinimapBackground() {
    sf::Texture background;
    background.loadFromImage(createMinimapImage());
    return background;
}

sf::Image Minimap::createMinimapImage() {
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

sf::Uint8* Minimap::createMinimapPixels() {
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

sf::Color Minimap::getColorFromModel(int row, int column) const {
    IntIsoPoint p(CartPoint(column, row).toIsometric());
    return tileColors_.at(model_->getTile(p)->type);
}

void Minimap::draw() const {
    sf::Sprite minimapSprite;
    minimapSprite.setTexture(minimap_.getTexture());

    MapRenderer::TargetProxy target = renderer_->getFixedTarget();

    sf::Vector2f basePosition = target.get()->mapPixelToCoords(
        sf::Vector2i(renderer_->getSize().x - width_, renderer_->getSize().y - height_));
    minimapSprite.setPosition(basePosition);

    target.get()->draw(minimapSprite);
}

void Minimap::update() {
    sf::FloatRect bounds = renderer_->getDisplayedRectangle();

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
