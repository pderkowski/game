/* Copyright 2014 <Piotr Derkowski> */

#include <map>
#include "SFML/Graphics.hpp"
#include "MapModel.hpp"
#include "Resources.hpp"
#include "Minimap.hpp"
#include "Tile.hpp"
#include "Coordinates.hpp"
#include "TileEnums.hpp"
#include "Renderer.hpp"

Minimap::Minimap(const MapModel* model, const players::Players* players, const Renderer* renderer)
    : players_(players),
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
    displayedRectangle_(createDisplayedRectangle())
{
    setModel(model);
}

void Minimap::setModel(const MapModel* model) {
    model_ = model;

    width_ = IsoPoint(model->getColumnsNo(), 0 ).toCartesian().x * horizontalPixelsPerTile_;
    height_ = IsoPoint(0, model->getRowsNo()).toCartesian().y * verticalPixelsPerTile_;

    minimap_.create(width_, height_);
}

void Minimap::updateBackground() {
    minimapBackground_ = createTexture();

    render();
}

sf::RectangleShape Minimap::createDisplayedRectangle() {
    sf::RectangleShape view;
    view.setFillColor(sf::Color(255, 255, 255, 100));
    view.setOutlineColor(sf::Color(255, 255, 255, 255));
    view.setOutlineThickness(-1);
    return view;
}

sf::Color Minimap::getPixel(int row, int column) const {
    IntIsoPoint pixelIsoCoords(CartPoint(column, row).toIsometric());
    auto tile = model_->getTile(pixelIsoCoords);

    if (players_->getCurrentPlayer()->doesKnowTile(tile.coords)) {
        return tileColors_.at(model_->getTile(pixelIsoCoords).type);
    } else {
        return sf::Color(0, 0, 0);
    }
}

sf::Texture Minimap::createTexture() {
    sf::Texture texture;
    texture.loadFromImage(createImageFromPixels(createPixels()));
    return texture;
}

sf::Image Minimap::createImageFromPixels(sf::Uint8* pixels) {
    try {
        sf::Image image;
        image.create(width_, height_, pixels);
        delete[] pixels;
        return image;
    } catch (...) {
        delete[] pixels;
        throw;
    }
}

sf::Uint8* Minimap::createPixels() {
    sf::Uint8* pixels = new sf::Uint8[4 * width_ * height_];

    for (int r = 0; r < height_; ++r) {
        for (int c = 0; c < width_; ++c) {
            int pixelNo = (r * width_ + c) * 4;

            sf::Color color = getPixel(r / verticalPixelsPerTile_, c / horizontalPixelsPerTile_);

            pixels[pixelNo + 0] = color.r;
            pixels[pixelNo + 1] = color.g;
            pixels[pixelNo + 2] = color.b;
            pixels[pixelNo + 3] = color.a;
        }
    }

    return pixels;
}


void Minimap::draw() const {
    sf::Sprite minimapSprite;
    minimapSprite.setTexture(minimap_.getTexture());
    minimapSprite.setPosition(basePosition_);

    Renderer::TargetProxy target = renderer_->getFixedTarget();
    target.get()->draw(minimapSprite);
}

void Minimap::updateDisplayedRectangle() {
    sf::FloatRect bounds = renderer_->getDisplayedRectangle();
    displayedRectangle_.setPosition(sf::Vector2f(bounds.left * width_, bounds.top * height_));
    displayedRectangle_.setSize(sf::Vector2f(bounds.width * width_, bounds.height * height_));

    render();
}

void Minimap::render() {
    minimap_.clear();
    minimap_.draw(sf::Sprite(minimapBackground_));
    minimap_.draw(displayedRectangle_);
    displayedRectangle_.move(-width_, 0); // needed to draw the rectangle wrapped around the borders
    minimap_.draw(displayedRectangle_);
    displayedRectangle_.move(width_, 0);
    minimap_.display();
}


sf::Vector2f Minimap::getSize() {
    return sf::Vector2f(width_, height_);
}

void Minimap::setPosition(const sf::Vector2f& position) {
    basePosition_ = position;
}
