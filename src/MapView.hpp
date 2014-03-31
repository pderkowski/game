/* Copyright 2014 <Piotr Derkowski> */

#ifndef MAPVIEW_H_
#define MAPVIEW_H_

#include <memory>
#include "SFML/Graphics.hpp"
#include "Map.hpp"

class MapView : public sf::Drawable {
public:
    MapView(std::shared_ptr<Map> map, const sf::Sprite& cellSprite);

    void setOffset(const sf::Vector2f& offset);

    virtual ~MapView() { }

    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

    float width() const;
    float height() const;

    int convertXCoordsToColumnNo(int x) const;
    int convertYCoordsToRowNo(int y) const;

private:
    std::shared_ptr<Map> map_;

    sf::Sprite cellSprite_;
    sf::Vector2f offset_;
};

#endif  // MAPVIEW_H_
