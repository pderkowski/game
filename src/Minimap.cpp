/* Copyright 2014 <Piotr Derkowski> */

#include <map>
#include <functional>
#include "SFML/Graphics.hpp"
#include "MapModel.hpp"
#include "Resources.hpp"
#include "Minimap.hpp"
#include "Tile.hpp"
#include "Coordinates.hpp"
#include "TileEnums.hpp"
#include "MapRenderer.hpp"
#include "players/Fog.hpp"

Minimap::Minimap(const MapModel* model, const players::Fog& fog, const MapRenderer* renderer)
    : model_(model),
    fog_(fog),
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
    isFogToggledOn_(true)
{
    rebuild(model, fog);
}

void Minimap::rebuild(const MapModel* model, const players::Fog& fog) {
    using namespace std::placeholders;

    model_ = model;
    fog_ = fog;

    width_ = IsoPoint(model->getColumnsNo(), 0 ).toCartesian().x * horizontalPixelsPerTile_;
    height_ = IsoPoint(0, model->getRowsNo()).toCartesian().y * verticalPixelsPerTile_;

    displayedRectangle_ = createDisplayedRectangle(),
    minimapBackground_ = createTexture(std::bind(&Minimap::getBackgroundPixel, this, _1, _2));
    fogTexture_ = createTexture(std::bind(&Minimap::getFogPixel, this, _1, _2));

    minimap_.create(width_, height_);

    updateDisplayedRectangle();
}

sf::RectangleShape Minimap::createDisplayedRectangle() {
    sf::RectangleShape view;
    view.setSize(sf::Vector2f(width_, height_));
    view.setFillColor(sf::Color(255, 255, 255, 100));
    view.setOutlineColor(sf::Color(255, 255, 255, 255));
    view.setOutlineThickness(-1);
    return view;
}

sf::Color Minimap::getBackgroundPixel(int row, int column) const {
    IntIsoPoint pixelIsoCoords(CartPoint(column, row).toIsometric());
    return tileColors_.at(model_->getTile(pixelIsoCoords).type);
}

sf::Color Minimap::getFogPixel(int row, int column) const {
    IntIsoPoint pixelIsoCoords(CartPoint(column, row).toIsometric());
    auto tile = model_->getTile(pixelIsoCoords);
    IntIsoPoint tileIsoCoords(tile.coords.toIsometric());

    if (fog_(tileIsoCoords.y, tileIsoCoords.x) == players::TileVisibility::Unknown) {
        return sf::Color(0, 0, 0);
    } else {
        return sf::Color(0, 0, 0, 0);
    }
}

sf::Texture Minimap::createTexture(std::function<sf::Color(int row, int column)> pixelGetter) {
    sf::Texture texture;
    texture.loadFromImage(createImageFromPixels(createPixels(pixelGetter)));
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

sf::Uint8* Minimap::createPixels(std::function<sf::Color(int row, int column)> pixelGetter) {
    sf::Uint8* pixels = new sf::Uint8[4 * width_ * height_];

    for (int r = 0; r < height_; ++r) {
        for (int c = 0; c < width_; ++c) {
            int pixelNo = (r * width_ + c) * 4;

            sf::Color color = pixelGetter(r / verticalPixelsPerTile_,
                c / horizontalPixelsPerTile_);
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

    MapRenderer::TargetProxy target = renderer_->getFixedTarget();
    target.get()->draw(minimapSprite);
}

void Minimap::updateDisplayedRectangle() {
    sf::FloatRect bounds = renderer_->getDisplayedRectangle();
    displayedRectangle_.setPosition(sf::Vector2f(bounds.left * width_, bounds.top * height_));
    displayedRectangle_.setSize(sf::Vector2f(bounds.width * width_, bounds.height * height_));

    render();
}

void Minimap::updateFog(const players::Fog& fog) {
    using namespace std::placeholders;

    fog_ = fog;

    fogTexture_ = createTexture(std::bind(&Minimap::getFogPixel, this, _1, _2));

    render();
}

void Minimap::toggleFog() {
    isFogToggledOn_ = !isFogToggledOn_;

    render();
}

void Minimap::render() {
    minimap_.clear();
    minimap_.draw(sf::Sprite(minimapBackground_));
    if (isFogToggledOn_) {
        minimap_.draw(sf::Sprite(fogTexture_));
    }
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
