/* Copyright 2014 <Piotr Derkowski> */

#ifndef TEXTUREMATCHER_HPP_
#define TEXTUREMATCHER_HPP_

#include <vector>
#include <memory>
#include <map>
#include "SFML/Graphics.hpp"
#include "Tile.hpp"

class TextureMatcher {
public:
    enum TileMatcher {
        Any,
        Same,
        Different
    };

    typedef std::vector<TileMatcher> Matching;

    TextureMatcher();
    TextureMatcher(Tile::Type matchedTileType);

    void addMatching(const Matching& matching, const sf::VertexArray& textureVertices);
    sf::VertexArray match(const std::vector<std::shared_ptr<const Tile>>& neighbors) const;

private:
    bool doMatch(const std::vector<std::shared_ptr<const Tile>>& neighbors,
        const Matching& matching) const;

    std::map<Matching, sf::VertexArray> matchings_;
    Tile::Type matchedTileType_;
};

#endif  // TEXTUREMATCHER_HPP_
