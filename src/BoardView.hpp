/* Copyright 2014 <Piotr Derkowski> */

#ifndef BOARDVIEW_H_
#define BOARDVIEW_H_

#include <SFML/Graphics.hpp>

class BoardView : public sf::Drawable {
public:
    BoardView(int rows, int columns, const sf::Sprite& cellSprite);

    void setOffset(const sf::Vector2f& offset);

    virtual ~BoardView() { }

    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

    float width() const;
    float height() const;

private:
    int rows_, columns_;
    sf::Sprite cellSprite_;
    sf::Vector2f offset_;
};

#endif  // BOARDVIEW_H_
