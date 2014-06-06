/* Copyright 2014 <Piotr Derkowski> */

#include <vector>
#include "SFML/Graphics.hpp"
#include "TextureMatcher.hpp"

TextureMatcher::TextureMatcher()
    : matchedTileType_(Tile::Type::Empty)
{ }

TextureMatcher::TextureMatcher(Tile::Type matchedTileType)
    : matchedTileType_(matchedTileType)
{ }

void TextureMatcher::addMatching(const Matching& matching, const sf::VertexArray& textureVertices)
{
    matchings_[matching] = textureVertices;
}

sf::VertexArray TextureMatcher::match(
    const std::vector<std::shared_ptr<const Tile>>& neighbors) const
{
    sf::VertexArray matchedVertices;
    for (const auto& matching_vertices : matchings_) {
        if (doMatch(neighbors, matching_vertices.first)) {
            for (unsigned i = 0; i < matching_vertices.second.getVertexCount(); ++i) {
                matchedVertices.append(matching_vertices.second[i]);
            }
        }
    }
    return matchedVertices;
}


bool TextureMatcher::doMatch(const std::vector<std::shared_ptr<const Tile>>& neighbors,
    const Matching& matching) const
{
    if (neighbors.size() != matching.size())
        return false;

    for (unsigned i = 0; i < matching.size(); ++i) {
        switch (matching[i]) {
            case TileMatcher::Any:
                break;
            case TileMatcher::Same:
                if (neighbors[i]->type == matchedTileType_ || neighbors[i]->type == Tile::Type::Empty)
                    break;
                else
                    return false;
            case TileMatcher::Different:
                if (neighbors[i]->type != matchedTileType_ && neighbors[i]->type != Tile::Type::Empty)
                    break;
                else
                    return false;
        }
    }

    return true;
}
