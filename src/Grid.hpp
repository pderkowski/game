/* Copyright 2014 <Piotr Derkowski> */

#ifndef GRID_H_
#define GRID_H_

#include <SFML/Graphics.hpp>

class Grid : public sf::Drawable {
public:
    Grid(int rows, int columns, const sf::Sprite& cellSprite);

    void setOffset(const sf::Vector2f& offset);

    virtual ~Grid() { }

    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

    float width() const;
    float height() const;

private:
    int rows_, columns_;
    sf::Sprite cellSprite_;
    sf::Vector2f offset_;
};

#endif  // GRID_H_
