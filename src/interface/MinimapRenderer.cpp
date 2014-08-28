/* Copyright 2014 <Piotr Derkowski> */

#include <map>
#include "SFML/Graphics.hpp"
#include "MinimapRenderer.hpp"
#include "Tile.hpp"
#include "Coordinates.hpp"
#include "TileEnums.hpp"
#include "players/Player.hpp"
#include "MapModel.hpp"

namespace interface {


MinimapRenderer::MinimapRenderer(unsigned rows, unsigned columns)
    : tileColors_{
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
    width_(IsoPoint(columns, 0 ).toCartesian().x * horizontalPixelsPerTile_),
    height_(IsoPoint(0, rows).toCartesian().y * verticalPixelsPerTile_),
    displayedRectangle_(createDisplayedRectangle())
{
    rendering_.create(width_, height_);
}

const sf::Texture& MinimapRenderer::getTexture() const {
    return rendering_.getTexture();
}

sf::Vector2f MinimapRenderer::getTextureSize() const {
    return sf::Vector2f(width_, height_);
}

void MinimapRenderer::updateBackground(const MapModel& model, const players::Player& player) {
    background_ = createTexture(model, player);

    render();
}

sf::Texture MinimapRenderer::createTexture(const MapModel& model, const players::Player& player) {
    sf::Texture texture;
    texture.loadFromImage(createImageFromPixels(createPixels(model, player)));
    return texture;
}

sf::Image MinimapRenderer::createImageFromPixels(sf::Uint8* pixels) {
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

sf::Uint8* MinimapRenderer::createPixels(const MapModel& model, const players::Player& player) {
    sf::Uint8* pixels = new sf::Uint8[4 * width_ * height_];

    for (int r = 0; r < height_; ++r) {
        for (int c = 0; c < width_; ++c) {
            int pixelNo = (r * width_ + c) * 4;

            sf::Color color = getPixel(model, player, r / verticalPixelsPerTile_,
                c / horizontalPixelsPerTile_);

            pixels[pixelNo + 0] = color.r;
            pixels[pixelNo + 1] = color.g;
            pixels[pixelNo + 2] = color.b;
            pixels[pixelNo + 3] = color.a;
        }
    }

    return pixels;
}

sf::Color MinimapRenderer::getPixel(const MapModel& model, const players::Player& player,
    int row, int column) const
{
    IntIsoPoint pixelIsoCoords(CartPoint(column, row).toIsometric());
    auto tile = model.getTile(pixelIsoCoords);

    if (player.doesKnowTile(tile.coords)) {
        return tileColors_.at(model.getTile(pixelIsoCoords).type);
    } else {
        return sf::Color(0, 0, 0);
    }
}

void MinimapRenderer::updateDisplayedRectangle(const sf::FloatRect& bounds) {
    displayedRectangle_.setPosition(sf::Vector2f(bounds.left * width_, bounds.top * height_));
    displayedRectangle_.setSize(sf::Vector2f(bounds.width * width_, bounds.height * height_));

    render();
}

void MinimapRenderer::render() {
    rendering_.clear();
    rendering_.draw(sf::Sprite(background_));
    rendering_.draw(displayedRectangle_);
    displayedRectangle_.move(-width_, 0); // needed to draw the rectangle wrapped around the borders
    rendering_.draw(displayedRectangle_);
    displayedRectangle_.move(width_, 0);
    rendering_.display();
}

sf::RectangleShape MinimapRenderer::createDisplayedRectangle() {
    sf::RectangleShape displayedRectangle;
    displayedRectangle.setFillColor(sf::Color(255, 255, 255, 100));
    displayedRectangle.setOutlineColor(sf::Color(255, 255, 255, 255));
    displayedRectangle.setOutlineThickness(-1);
    return displayedRectangle;
}


}  // interface
