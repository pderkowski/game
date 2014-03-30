/* Copyright 2014 <Piotr Derkowski> */

#include <SFML/Graphics/Rect.hpp>
#include <SFML/Graphics/Drawable.hpp>

class Grid : public sf::Drawable {
public:
    Grid(int rows, int columns, const sf::Sprite& cellSprite);

    virtual ~Grid() { }

    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

private:
    int rows, columns;
    sf::Sprite cellSprite;
};
