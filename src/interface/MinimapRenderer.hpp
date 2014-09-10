/* Copyright 2014 <Piotr Derkowski> */

#ifndef INTERFACE_MINIMAP_HPP_
#define INTERFACE_MINIMAP_HPP_

#include <map>
#include "SFML/Graphics.hpp"
#include "TileEnums.hpp"
namespace map { class MapModel; }
namespace players { class Player; }


namespace interface {


class MinimapRenderer {
public:
    explicit MinimapRenderer(unsigned rows, unsigned columns);

    const sf::Texture& getTexture() const;

    sf::Vector2f getTextureSize() const;

    void updateBackground(const map::MapModel& model, const players::Player& player);
    void updateDisplayedRectangle(const sf::FloatRect& bounds);

private:
    sf::RectangleShape createDisplayedRectangle();
    sf::Texture createTexture(const map::MapModel& model, const players::Player& player);
    sf::Image createImageFromPixels(sf::Uint8* pixels);
    sf::Uint8* createPixels(const map::MapModel& model, const players::Player& player);

    sf::Color getPixel(const map::MapModel& model, const players::Player& player, int row,
        int column) const;

    void render();

private:
    std::map<tileenums::Type, sf::Color> tileColors_;

    int horizontalPixelsPerTile_;
    int verticalPixelsPerTile_;
    int width_;
    int height_;

    sf::Texture background_;
    sf::RectangleShape displayedRectangle_;

    sf::RenderTexture rendering_;
};


}  // namespace interface


#endif  // INTERFACE_MINIMAP_HPP_
