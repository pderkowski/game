/* Copyright 2014 <Piotr Derkowski> */

#ifndef MAPVIEW_HPP_
#define MAPVIEW_HPP_

#include <memory>
#include <map>
#include "SFML/Graphics.hpp"
#include "Map.hpp"

class MapView : public sf::Drawable {
public:
    MapView(std::shared_ptr<Map> map, const std::map<Tile::Type, sf::Texture>& tileTextures);

    void setOffset(const sf::Vector2f& offset);

    virtual ~MapView() { }

    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

    float width() const;
    float height() const;

    int convertXCoordsToColumnNo(int x) const;
    int convertYCoordsToRowNo(int y) const;

private:
    std::shared_ptr<Map> map_;

    std::map<Tile::Type, sf::Texture> tileTextures_;
    sf::Vector2f offset_;

    int tileWidth_;
    int tileHeight_;
};

#endif  // MAPVIEW_HPP_
