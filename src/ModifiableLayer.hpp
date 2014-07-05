/* Copyright 2014 <Piotr Derkowski> */

#include <vector>
#include <map>
#include <memory>
#include "SFML/Graphics.hpp"
#include "Layer.hpp"
#include "TextureSet.hpp"
#include "Tile.hpp"

#ifndef MODIFIABLELAYER_HPP_
#define MODIFIABLELAYER_HPP_

class ModifiableLayer : public Layer {
public:
    using Layer::Layer;
    virtual ~ModifiableLayer() { }

    virtual void add(std::shared_ptr<const Tile> tile, const sf::Vector2f& tileCenter) override;

    virtual void remove(std::shared_ptr<const Tile> tile);

    virtual void update(std::shared_ptr<const Tile> tile, const sf::Vector2f& tileCenter);

private:
    struct VertexPosition {
        size_t start;
        size_t size;
    };

private:
    void removeVertices(const VertexPosition& position);
    void updatePositions(const VertexPosition& position);

    std::map<std::shared_ptr<const Tile>, VertexPosition> positions_;
};

#endif  // MODIFIABLELAYER_HPP_
