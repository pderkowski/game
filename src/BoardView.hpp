/* Copyright 2014 <Piotr Derkowski> */

#ifndef BOARDVIEW_H_
#define BOARDVIEW_H_

#include <memory>
#include "SFML/Graphics.hpp"
#include "Board.hpp"

class BoardView : public sf::Drawable {
public:
    BoardView(std::shared_ptr<Board> board, const sf::Sprite& cellSprite);

    void setOffset(const sf::Vector2f& offset);

    virtual ~BoardView() { }

    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

    float width() const;
    float height() const;

private:
    std::shared_ptr<Board> board_;

    sf::Sprite cellSprite_;
    sf::Vector2f offset_;
};

#endif  // BOARDVIEW_H_
