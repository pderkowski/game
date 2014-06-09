/* Copyright 2014 <Piotr Derkowski> */

#include <vector>
#include "SFML/Graphics.hpp"
#include "TextureSet.hpp"
#include "Tile.hpp"
#include "TextureSetFactory.hpp"
#include "Resources.hpp"
#include "TextureMatcher.hpp"

#define ANY TextureMatcher::TileMatcher::Any
#define SAME TextureMatcher::TileMatcher::Same
#define DIFF TextureMatcher::TileMatcher::Different

namespace {

sf::VertexArray makeQuad(float width, float height, const sf::Vector2f& texCoords,
    const sf::Vector2f& position = sf::Vector2f(0, 0))
{
    sf::VertexArray rectangle(sf::Quads, 4);
    rectangle[0].position = position + sf::Vector2f(0, 0);
    rectangle[1].position = position + sf::Vector2f(width, 0);
    rectangle[2].position = position + sf::Vector2f(width, height);
    rectangle[3].position = position + sf::Vector2f(0, height);

    rectangle[0].texCoords = texCoords + sf::Vector2f(0, 0);
    rectangle[1].texCoords = texCoords + sf::Vector2f(width, 0);
    rectangle[2].texCoords = texCoords + sf::Vector2f(width, height);
    rectangle[3].texCoords = texCoords + sf::Vector2f(0, height);

    return rectangle;
}

}


TextureSet TextureSetFactory::getBaseTextureSet() {
    TextureSet ts(Resources::loadTexture("textures/terrains.png"));

    ts.add(Tile::Type::Water, makeWaterBaseMatcher());
    ts.add(Tile::Type::Hills, makeHillsBaseMatcher());
    ts.add(Tile::Type::Mountains, makeMountainsBaseMatcher());
    ts.add(Tile::Type::Grassland, makeGrasslandBaseMatcher());
    ts.add(Tile::Type::Plains, makePlainsBaseMatcher());
    ts.add(Tile::Type::Forest, makeForestBaseMatcher());
    ts.add(Tile::Type::Desert, makeDesertBaseMatcher());

    return ts;
}

TextureSet TextureSetFactory::getBlendTextureSet() {
    TextureSet ts(Resources::loadTexture("textures/blends.png"));

    ts.add(Tile::Type::Water, makeWaterBlendMatcher());
    ts.add(Tile::Type::Plains, makePlainsBlendMatcher());
    ts.add(Tile::Type::Forest, makeForestBlendMatcher());
    ts.add(Tile::Type::Grassland, makeGrasslandBlendMatcher());
    ts.add(Tile::Type::Desert, makeDesertBlendMatcher());
    ts.add(Tile::Type::Hills, makeHillsBlendMatcher());
    ts.add(Tile::Type::Mountains, makeMountainsBlendMatcher());

    return ts;
}

TextureSet TextureSetFactory::getOverlayTextureSet() {
    TextureSet ts(Resources::loadTexture("textures/landmarks.png"));

    ts.add(Tile::Type::Forest, makeForestOverlayMatcher());
    ts.add(Tile::Type::Hills, makeHillsOverlayMatcher());
    ts.add(Tile::Type::Mountains, makeMountainsOverlayMatcher());

    return ts;
}

TextureMatcher TextureSetFactory::makeHillsBaseMatcher() {
    TextureMatcher tm(Tile::Type::Hills);

    tm.addMatching(TextureMatcher::Matching({ ANY, ANY, ANY, ANY, ANY, ANY, ANY, ANY }),
        ::makeQuad(96, 48, sf::Vector2f(1, 197)));

    return tm;
}

TextureMatcher TextureSetFactory::makeMountainsBaseMatcher() {
    TextureMatcher tm(Tile::Type::Mountains);

    tm.addMatching(TextureMatcher::Matching({ ANY, ANY, ANY, ANY, ANY, ANY, ANY, ANY }),
        ::makeQuad(96, 48, sf::Vector2f(1, 197)));

    return tm;
}

TextureMatcher TextureSetFactory::makeGrasslandBaseMatcher() {
    TextureMatcher tm(Tile::Type::Grassland);

    tm.addMatching(TextureMatcher::Matching({ ANY, ANY, ANY, ANY, ANY, ANY, ANY, ANY }),
        ::makeQuad(96, 48, sf::Vector2f(1, 99)));

    return tm;
}

TextureMatcher TextureSetFactory::makePlainsBaseMatcher() {
    TextureMatcher tm(Tile::Type::Plains);

    tm.addMatching(TextureMatcher::Matching({ ANY, ANY, ANY, ANY, ANY, ANY, ANY, ANY }),
        ::makeQuad(96, 48, sf::Vector2f(1, 50)));

    return tm;
}

TextureMatcher TextureSetFactory::makeForestBaseMatcher() {
    TextureMatcher tm(Tile::Type::Forest);

    tm.addMatching(TextureMatcher::Matching({ ANY, ANY, ANY, ANY, ANY, ANY, ANY, ANY }),
        ::makeQuad(96, 48, sf::Vector2f(1, 50)));

    return tm;
}

TextureMatcher TextureSetFactory::makeDesertBaseMatcher() {
    TextureMatcher tm(Tile::Type::Desert);

    tm.addMatching(TextureMatcher::Matching({ ANY, ANY, ANY, ANY, ANY, ANY, ANY, ANY }),
        ::makeQuad(96, 48, sf::Vector2f(1, 1)));

    return tm;
}

TextureMatcher TextureSetFactory::makeWaterBlendMatcher() {
    TextureMatcher tm(Tile::Type::Water);

    tm.addMatching(TextureMatcher::Matching({ DIFF, ANY, ANY, ANY, ANY, ANY, ANY, ANY }),
        ::makeQuad(48, 24, sf::Vector2f(1, 1)));
    tm.addMatching(TextureMatcher::Matching({ ANY, ANY, DIFF, ANY, ANY, ANY, ANY, ANY }),
        ::makeQuad(48, 24, sf::Vector2f(50, 1), sf::Vector2f(48, 0)));
    tm.addMatching(TextureMatcher::Matching({ ANY, ANY, ANY, ANY, DIFF, ANY, ANY, ANY }),
        ::makeQuad(48, 24, sf::Vector2f(50, 26), sf::Vector2f(48, 24)));
    tm.addMatching(TextureMatcher::Matching({ ANY, ANY, ANY, ANY, ANY, ANY, DIFF, ANY }),
        ::makeQuad(48, 24, sf::Vector2f(1, 26), sf::Vector2f(0, 24)));

    return tm;
}

TextureMatcher TextureSetFactory::makeGrasslandBlendMatcher() {
    TextureMatcher tm(Tile::Type::Grassland);

    tm.addMatching(TextureMatcher::Matching({ DIFF, ANY, ANY, ANY, ANY, ANY, ANY, ANY }),
        ::makeQuad(48, 24, sf::Vector2f(1, 51)));
    tm.addMatching(TextureMatcher::Matching({ ANY, ANY, DIFF, ANY, ANY, ANY, ANY, ANY }),
        ::makeQuad(48, 24, sf::Vector2f(50, 51), sf::Vector2f(48, 0)));
    tm.addMatching(TextureMatcher::Matching({ ANY, ANY, ANY, ANY, DIFF, ANY, ANY, ANY }),
        ::makeQuad(48, 24, sf::Vector2f(50, 76), sf::Vector2f(48, 24)));
    tm.addMatching(TextureMatcher::Matching({ ANY, ANY, ANY, ANY, ANY, ANY, DIFF, ANY }),
        ::makeQuad(48, 24, sf::Vector2f(1, 76), sf::Vector2f(0, 24)));

    return tm;
}

TextureMatcher TextureSetFactory::makePlainsBlendMatcher() {
    TextureMatcher tm(Tile::Type::Plains);

    tm.addMatching(TextureMatcher::Matching({ DIFF, ANY, ANY, ANY, ANY, ANY, ANY, ANY }),
        ::makeQuad(48, 24, sf::Vector2f(1, 151)));
    tm.addMatching(TextureMatcher::Matching({ ANY, ANY, DIFF, ANY, ANY, ANY, ANY, ANY }),
        ::makeQuad(48, 24, sf::Vector2f(50, 151), sf::Vector2f(48, 0)));
    tm.addMatching(TextureMatcher::Matching({ ANY, ANY, ANY, ANY, DIFF, ANY, ANY, ANY }),
        ::makeQuad(48, 24, sf::Vector2f(50, 176), sf::Vector2f(48, 24)));
    tm.addMatching(TextureMatcher::Matching({ ANY, ANY, ANY, ANY, ANY, ANY, DIFF, ANY }),
        ::makeQuad(48, 24, sf::Vector2f(1, 176), sf::Vector2f(0, 24)));

    return tm;
}

TextureMatcher TextureSetFactory::makeForestBlendMatcher() {
    TextureMatcher tm(Tile::Type::Forest);

    tm.addMatching(TextureMatcher::Matching({ DIFF, ANY, ANY, ANY, ANY, ANY, ANY, ANY }),
        ::makeQuad(48, 24, sf::Vector2f(1, 151)));
    tm.addMatching(TextureMatcher::Matching({ ANY, ANY, DIFF, ANY, ANY, ANY, ANY, ANY }),
        ::makeQuad(48, 24, sf::Vector2f(50, 151), sf::Vector2f(48, 0)));
    tm.addMatching(TextureMatcher::Matching({ ANY, ANY, ANY, ANY, DIFF, ANY, ANY, ANY }),
        ::makeQuad(48, 24, sf::Vector2f(50, 176), sf::Vector2f(48, 24)));
    tm.addMatching(TextureMatcher::Matching({ ANY, ANY, ANY, ANY, ANY, ANY, DIFF, ANY }),
        ::makeQuad(48, 24, sf::Vector2f(1, 176), sf::Vector2f(0, 24)));

    return tm;
}

TextureMatcher TextureSetFactory::makeDesertBlendMatcher() {
    TextureMatcher tm(Tile::Type::Desert);

    tm.addMatching(TextureMatcher::Matching({ DIFF, ANY, ANY, ANY, ANY, ANY, ANY, ANY }),
        ::makeQuad(48, 24, sf::Vector2f(99, 1)));
    tm.addMatching(TextureMatcher::Matching({ ANY, ANY, DIFF, ANY, ANY, ANY, ANY, ANY }),
        ::makeQuad(48, 24, sf::Vector2f(148, 1), sf::Vector2f(48, 0)));
    tm.addMatching(TextureMatcher::Matching({ ANY, ANY, ANY, ANY, DIFF, ANY, ANY, ANY }),
        ::makeQuad(48, 24, sf::Vector2f(148, 26), sf::Vector2f(48, 24)));
    tm.addMatching(TextureMatcher::Matching({ ANY, ANY, ANY, ANY, ANY, ANY, DIFF, ANY }),
        ::makeQuad(48, 24, sf::Vector2f(99, 26), sf::Vector2f(0, 24)));

    return tm;
}

TextureMatcher TextureSetFactory::makeHillsBlendMatcher() {
    TextureMatcher tm(Tile::Type::Hills);

    tm.addMatching(TextureMatcher::Matching({ DIFF, ANY, ANY, ANY, ANY, ANY, ANY, ANY }),
        ::makeQuad(48, 24, sf::Vector2f(1, 101)));
    tm.addMatching(TextureMatcher::Matching({ ANY, ANY, DIFF, ANY, ANY, ANY, ANY, ANY }),
        ::makeQuad(48, 24, sf::Vector2f(50, 101), sf::Vector2f(48, 0)));
    tm.addMatching(TextureMatcher::Matching({ ANY, ANY, ANY, ANY, DIFF, ANY, ANY, ANY }),
        ::makeQuad(48, 24, sf::Vector2f(50, 126), sf::Vector2f(48, 24)));
    tm.addMatching(TextureMatcher::Matching({ ANY, ANY, ANY, ANY, ANY, ANY, DIFF, ANY }),
        ::makeQuad(48, 24, sf::Vector2f(1, 126), sf::Vector2f(0, 24)));

    return tm;
}

TextureMatcher TextureSetFactory::makeMountainsBlendMatcher() {
    TextureMatcher tm(Tile::Type::Mountains);

    tm.addMatching(TextureMatcher::Matching({ DIFF, ANY, ANY, ANY, ANY, ANY, ANY, ANY }),
        ::makeQuad(48, 24, sf::Vector2f(1, 101)));
    tm.addMatching(TextureMatcher::Matching({ ANY, ANY, DIFF, ANY, ANY, ANY, ANY, ANY }),
        ::makeQuad(48, 24, sf::Vector2f(50, 101), sf::Vector2f(48, 0)));
    tm.addMatching(TextureMatcher::Matching({ ANY, ANY, ANY, ANY, DIFF, ANY, ANY, ANY }),
        ::makeQuad(48, 24, sf::Vector2f(50, 126), sf::Vector2f(48, 24)));
    tm.addMatching(TextureMatcher::Matching({ ANY, ANY, ANY, ANY, ANY, ANY, DIFF, ANY }),
        ::makeQuad(48, 24, sf::Vector2f(1, 126), sf::Vector2f(0, 24)));

    return tm;
}

TextureMatcher TextureSetFactory::makeWaterBaseMatcher() {
    TextureMatcher tm(Tile::Type::Water);

    tm.addMatching(TextureMatcher::Matching({ SAME, SAME, SAME, ANY, ANY, ANY, ANY, ANY }),
        ::makeQuad(48, 24, sf::Vector2f(1, 645), sf::Vector2f(25, 0)));
    tm.addMatching(TextureMatcher::Matching({ ANY, ANY, ANY, ANY, SAME, SAME, SAME, ANY }),
        ::makeQuad(48, 24, sf::Vector2f(1, 670), sf::Vector2f(25, 24)));
    tm.addMatching(TextureMatcher::Matching({ SAME, ANY, ANY, ANY, ANY, ANY, SAME, SAME }),
        ::makeQuad(48, 24, sf::Vector2f(1, 695), sf::Vector2f(1, 12)));
    tm.addMatching(TextureMatcher::Matching({ ANY, ANY, SAME, SAME, SAME, ANY, ANY, ANY }),
        ::makeQuad(48, 24, sf::Vector2f(50, 695), sf::Vector2f(49, 12)));

    tm.addMatching(TextureMatcher::Matching({ DIFF, SAME, SAME, ANY, ANY, ANY, ANY, ANY }),
        ::makeQuad(48, 24, sf::Vector2f(99, 645), sf::Vector2f(25, 0)));
    tm.addMatching(TextureMatcher::Matching({ ANY, ANY, ANY, ANY, DIFF, SAME, SAME, ANY }),
        ::makeQuad(48, 24, sf::Vector2f(99, 670), sf::Vector2f(25, 24)));
    tm.addMatching(TextureMatcher::Matching({ SAME, ANY, ANY, ANY, ANY, ANY, DIFF, SAME }),
        ::makeQuad(48, 24, sf::Vector2f(99, 695), sf::Vector2f(1, 12)));
    tm.addMatching(TextureMatcher::Matching({ ANY, ANY, DIFF, SAME, SAME, ANY, ANY, ANY }),
        ::makeQuad(48, 24, sf::Vector2f(148, 695), sf::Vector2f(49, 12)));

    tm.addMatching(TextureMatcher::Matching({ SAME, DIFF, SAME, ANY, ANY, ANY, ANY, ANY }),
        ::makeQuad(48, 24, sf::Vector2f(197, 645), sf::Vector2f(25, 0)));
    tm.addMatching(TextureMatcher::Matching({ ANY, ANY, ANY, ANY, SAME, DIFF, SAME, ANY }),
        ::makeQuad(48, 24, sf::Vector2f(197, 670), sf::Vector2f(25, 24)));
    tm.addMatching(TextureMatcher::Matching({ SAME, ANY, ANY, ANY, ANY, ANY, SAME, DIFF }),
        ::makeQuad(48, 24, sf::Vector2f(197, 695), sf::Vector2f(1, 12)));
    tm.addMatching(TextureMatcher::Matching({ ANY, ANY, SAME, DIFF, SAME, ANY, ANY, ANY }),
        ::makeQuad(48, 24, sf::Vector2f(246, 695), sf::Vector2f(49, 12)));

    tm.addMatching(TextureMatcher::Matching({ DIFF, DIFF, SAME, ANY, ANY, ANY, ANY, ANY }),
        ::makeQuad(48, 24, sf::Vector2f(295, 645), sf::Vector2f(25, 0)));
    tm.addMatching(TextureMatcher::Matching({ ANY, ANY, ANY, ANY, DIFF, DIFF, SAME, ANY }),
        ::makeQuad(48, 24, sf::Vector2f(295, 670), sf::Vector2f(25, 24)));
    tm.addMatching(TextureMatcher::Matching({ SAME, ANY, ANY, ANY, ANY, ANY, DIFF, DIFF }),
        ::makeQuad(48, 24, sf::Vector2f(295, 695), sf::Vector2f(1, 12)));
    tm.addMatching(TextureMatcher::Matching({ ANY, ANY, DIFF, DIFF, SAME, ANY, ANY, ANY }),
        ::makeQuad(48, 24, sf::Vector2f(344, 695), sf::Vector2f(49, 12)));

    tm.addMatching(TextureMatcher::Matching({ SAME, SAME, DIFF, ANY, ANY, ANY, ANY, ANY }),
        ::makeQuad(48, 24, sf::Vector2f(393, 645), sf::Vector2f(25, 0)));
    tm.addMatching(TextureMatcher::Matching({ ANY, ANY, ANY, ANY, SAME, SAME, DIFF, ANY }),
        ::makeQuad(48, 24, sf::Vector2f(393, 670), sf::Vector2f(25, 24)));
    tm.addMatching(TextureMatcher::Matching({ DIFF, ANY, ANY, ANY, ANY, ANY, SAME, SAME }),
        ::makeQuad(48, 24, sf::Vector2f(393, 695), sf::Vector2f(1, 12)));
    tm.addMatching(TextureMatcher::Matching({ ANY, ANY, SAME, SAME, DIFF, ANY, ANY, ANY }),
        ::makeQuad(48, 24, sf::Vector2f(442, 695), sf::Vector2f(49, 12)));

    tm.addMatching(TextureMatcher::Matching({ DIFF, SAME, DIFF, ANY, ANY, ANY, ANY, ANY }),
        ::makeQuad(48, 24, sf::Vector2f(491, 645), sf::Vector2f(25, 0)));
    tm.addMatching(TextureMatcher::Matching({ ANY, ANY, ANY, ANY, DIFF, SAME, DIFF, ANY }),
        ::makeQuad(48, 24, sf::Vector2f(491, 670), sf::Vector2f(25, 24)));
    tm.addMatching(TextureMatcher::Matching({ DIFF, ANY, ANY, ANY, ANY, ANY, DIFF, SAME }),
        ::makeQuad(48, 24, sf::Vector2f(491, 695), sf::Vector2f(1, 12)));
    tm.addMatching(TextureMatcher::Matching({ ANY, ANY, DIFF, SAME, DIFF, ANY, ANY, ANY }),
        ::makeQuad(48, 24, sf::Vector2f(540, 695), sf::Vector2f(49, 12)));

    tm.addMatching(TextureMatcher::Matching({ SAME, DIFF, DIFF, ANY, ANY, ANY, ANY, ANY }),
        ::makeQuad(48, 24, sf::Vector2f(589, 645), sf::Vector2f(25, 0)));
    tm.addMatching(TextureMatcher::Matching({ ANY, ANY, ANY, ANY, SAME, DIFF, DIFF, ANY }),
        ::makeQuad(48, 24, sf::Vector2f(589, 670), sf::Vector2f(25, 24)));
    tm.addMatching(TextureMatcher::Matching({ DIFF, ANY, ANY, ANY, ANY, ANY, SAME, DIFF }),
        ::makeQuad(48, 24, sf::Vector2f(589, 695), sf::Vector2f(1, 12)));
    tm.addMatching(TextureMatcher::Matching({ ANY, ANY, SAME, DIFF, DIFF, ANY, ANY, ANY }),
        ::makeQuad(48, 24, sf::Vector2f(638, 695), sf::Vector2f(49, 12)));

    tm.addMatching(TextureMatcher::Matching({ DIFF, DIFF, DIFF, ANY, ANY, ANY, ANY, ANY }),
        ::makeQuad(48, 24, sf::Vector2f(687, 645), sf::Vector2f(25, 0)));
    tm.addMatching(TextureMatcher::Matching({ ANY, ANY, ANY, ANY, DIFF, DIFF, DIFF, ANY }),
        ::makeQuad(48, 24, sf::Vector2f(687, 670), sf::Vector2f(25, 24)));
    tm.addMatching(TextureMatcher::Matching({ DIFF, ANY, ANY, ANY, ANY, ANY, DIFF, DIFF }),
        ::makeQuad(48, 24, sf::Vector2f(687, 695), sf::Vector2f(1, 12)));
    tm.addMatching(TextureMatcher::Matching({ ANY, ANY, DIFF, DIFF, DIFF, ANY, ANY, ANY }),
        ::makeQuad(48, 24, sf::Vector2f(736, 695), sf::Vector2f(49, 12)));

    return tm;
}

TextureMatcher TextureSetFactory::makeForestOverlayMatcher() {
    TextureMatcher tm(Tile::Type::Forest);

    tm.addMatching(TextureMatcher::Matching({ ANY, ANY, ANY, ANY, ANY, ANY, ANY, ANY }),
        ::makeQuad(96, 48, sf::Vector2f(1, 197)));
    tm.addMatching(TextureMatcher::Matching({ ANY, ANY, ANY, ANY, ANY, ANY, SAME, ANY }),
        ::makeQuad(96, 48, sf::Vector2f(98, 197)));
    tm.addMatching(TextureMatcher::Matching({ ANY, ANY, ANY, ANY, SAME, ANY, ANY, ANY }),
        ::makeQuad(96, 48, sf::Vector2f(195, 197)));
    tm.addMatching(TextureMatcher::Matching({ ANY, ANY, ANY, ANY, SAME, ANY, SAME, ANY }),
        ::makeQuad(96, 48, sf::Vector2f(292, 197)));
    tm.addMatching(TextureMatcher::Matching({ ANY, ANY, SAME, ANY, ANY, ANY, ANY, ANY }),
        ::makeQuad(96, 48, sf::Vector2f(389, 197)));
    tm.addMatching(TextureMatcher::Matching({ ANY, ANY, SAME, ANY, ANY, ANY, SAME, ANY }),
        ::makeQuad(96, 48, sf::Vector2f(486, 197)));
    tm.addMatching(TextureMatcher::Matching({ ANY, ANY, SAME, ANY, SAME, ANY, ANY, ANY }),
        ::makeQuad(96, 48, sf::Vector2f(583, 197)));
    tm.addMatching(TextureMatcher::Matching({ ANY, ANY, SAME, ANY, SAME, ANY, SAME, ANY }),
        ::makeQuad(96, 48, sf::Vector2f(680, 197)));
    tm.addMatching(TextureMatcher::Matching({ SAME, ANY, ANY, ANY, ANY, ANY, ANY, ANY }),
        ::makeQuad(96, 48, sf::Vector2f(1, 246)));
    tm.addMatching(TextureMatcher::Matching({ SAME, ANY, ANY, ANY, ANY, ANY, SAME, ANY }),
        ::makeQuad(96, 48, sf::Vector2f(98, 246)));
    tm.addMatching(TextureMatcher::Matching({ SAME, ANY, ANY, ANY, SAME, ANY, ANY, ANY }),
        ::makeQuad(96, 48, sf::Vector2f(195, 246)));
    tm.addMatching(TextureMatcher::Matching({ SAME, ANY, ANY, ANY, SAME, ANY, SAME, ANY }),
        ::makeQuad(96, 48, sf::Vector2f(292, 246)));
    tm.addMatching(TextureMatcher::Matching({ SAME, ANY, SAME, ANY, ANY, ANY, ANY, ANY }),
        ::makeQuad(96, 48, sf::Vector2f(389, 246)));
    tm.addMatching(TextureMatcher::Matching({ SAME, ANY, SAME, ANY, ANY, ANY, SAME, ANY }),
        ::makeQuad(96, 48, sf::Vector2f(486, 246)));
    tm.addMatching(TextureMatcher::Matching({ SAME, ANY, SAME, ANY, SAME, ANY, ANY, ANY }),
        ::makeQuad(96, 48, sf::Vector2f(583, 246)));
    tm.addMatching(TextureMatcher::Matching({ SAME, ANY, SAME, ANY, SAME, ANY, SAME, ANY }),
        ::makeQuad(96, 48, sf::Vector2f(680, 246)));

    return tm;
}

TextureMatcher TextureSetFactory::makeHillsOverlayMatcher() {
    TextureMatcher tm(Tile::Type::Hills);

    tm.addMatching(TextureMatcher::Matching({ ANY, ANY, ANY, ANY, ANY, ANY, ANY, ANY }),
        ::makeQuad(96, 48, sf::Vector2f(1, 393)));
    tm.addMatching(TextureMatcher::Matching({ ANY, ANY, ANY, ANY, ANY, ANY, SAME, ANY }),
        ::makeQuad(96, 48, sf::Vector2f(98, 393)));
    tm.addMatching(TextureMatcher::Matching({ ANY, ANY, ANY, ANY, SAME, ANY, ANY, ANY }),
        ::makeQuad(96, 48, sf::Vector2f(195, 393)));
    tm.addMatching(TextureMatcher::Matching({ ANY, ANY, ANY, ANY, SAME, ANY, SAME, ANY }),
        ::makeQuad(96, 48, sf::Vector2f(292, 393)));
    tm.addMatching(TextureMatcher::Matching({ ANY, ANY, SAME, ANY, ANY, ANY, ANY, ANY }),
        ::makeQuad(96, 48, sf::Vector2f(389, 393)));
    tm.addMatching(TextureMatcher::Matching({ ANY, ANY, SAME, ANY, ANY, ANY, SAME, ANY }),
        ::makeQuad(96, 48, sf::Vector2f(486, 393)));
    tm.addMatching(TextureMatcher::Matching({ ANY, ANY, SAME, ANY, SAME, ANY, ANY, ANY }),
        ::makeQuad(96, 48, sf::Vector2f(583, 393)));
    tm.addMatching(TextureMatcher::Matching({ ANY, ANY, SAME, ANY, SAME, ANY, SAME, ANY }),
        ::makeQuad(96, 48, sf::Vector2f(680, 393)));
    tm.addMatching(TextureMatcher::Matching({ SAME, ANY, ANY, ANY, ANY, ANY, ANY, ANY }),
        ::makeQuad(96, 48, sf::Vector2f(1, 442)));
    tm.addMatching(TextureMatcher::Matching({ SAME, ANY, ANY, ANY, ANY, ANY, SAME, ANY }),
        ::makeQuad(96, 48, sf::Vector2f(98, 442)));
    tm.addMatching(TextureMatcher::Matching({ SAME, ANY, ANY, ANY, SAME, ANY, ANY, ANY }),
        ::makeQuad(96, 48, sf::Vector2f(195, 442)));
    tm.addMatching(TextureMatcher::Matching({ SAME, ANY, ANY, ANY, SAME, ANY, SAME, ANY }),
        ::makeQuad(96, 48, sf::Vector2f(292, 442)));
    tm.addMatching(TextureMatcher::Matching({ SAME, ANY, SAME, ANY, ANY, ANY, ANY, ANY }),
        ::makeQuad(96, 48, sf::Vector2f(389, 442)));
    tm.addMatching(TextureMatcher::Matching({ SAME, ANY, SAME, ANY, ANY, ANY, SAME, ANY }),
        ::makeQuad(96, 48, sf::Vector2f(486, 442)));
    tm.addMatching(TextureMatcher::Matching({ SAME, ANY, SAME, ANY, SAME, ANY, ANY, ANY }),
        ::makeQuad(96, 48, sf::Vector2f(583, 442)));
    tm.addMatching(TextureMatcher::Matching({ SAME, ANY, SAME, ANY, SAME, ANY, SAME, ANY }),
        ::makeQuad(96, 48, sf::Vector2f(680, 442)));

    return tm;
}

TextureMatcher TextureSetFactory::makeMountainsOverlayMatcher() {
    TextureMatcher tm(Tile::Type::Mountains);

    tm.addMatching(TextureMatcher::Matching({ ANY, ANY, ANY, ANY, ANY, ANY, ANY, ANY }),
        ::makeQuad(96, 48, sf::Vector2f(1, 295)));
    tm.addMatching(TextureMatcher::Matching({ ANY, ANY, ANY, ANY, ANY, ANY, SAME, ANY }),
        ::makeQuad(96, 48, sf::Vector2f(98, 295)));
    tm.addMatching(TextureMatcher::Matching({ ANY, ANY, ANY, ANY, SAME, ANY, ANY, ANY }),
        ::makeQuad(96, 48, sf::Vector2f(195, 295)));
    tm.addMatching(TextureMatcher::Matching({ ANY, ANY, ANY, ANY, SAME, ANY, SAME, ANY }),
        ::makeQuad(96, 48, sf::Vector2f(292, 295)));
    tm.addMatching(TextureMatcher::Matching({ ANY, ANY, SAME, ANY, ANY, ANY, ANY, ANY }),
        ::makeQuad(96, 48, sf::Vector2f(389, 295)));
    tm.addMatching(TextureMatcher::Matching({ ANY, ANY, SAME, ANY, ANY, ANY, SAME, ANY }),
        ::makeQuad(96, 48, sf::Vector2f(486, 295)));
    tm.addMatching(TextureMatcher::Matching({ ANY, ANY, SAME, ANY, SAME, ANY, ANY, ANY }),
        ::makeQuad(96, 48, sf::Vector2f(583, 295)));
    tm.addMatching(TextureMatcher::Matching({ ANY, ANY, SAME, ANY, SAME, ANY, SAME, ANY }),
        ::makeQuad(96, 48, sf::Vector2f(680, 295)));
    tm.addMatching(TextureMatcher::Matching({ SAME, ANY, ANY, ANY, ANY, ANY, ANY, ANY }),
        ::makeQuad(96, 48, sf::Vector2f(1, 344)));
    tm.addMatching(TextureMatcher::Matching({ SAME, ANY, ANY, ANY, ANY, ANY, SAME, ANY }),
        ::makeQuad(96, 48, sf::Vector2f(98, 344)));
    tm.addMatching(TextureMatcher::Matching({ SAME, ANY, ANY, ANY, SAME, ANY, ANY, ANY }),
        ::makeQuad(96, 48, sf::Vector2f(195, 344)));
    tm.addMatching(TextureMatcher::Matching({ SAME, ANY, ANY, ANY, SAME, ANY, SAME, ANY }),
        ::makeQuad(96, 48, sf::Vector2f(292, 344)));
    tm.addMatching(TextureMatcher::Matching({ SAME, ANY, SAME, ANY, ANY, ANY, ANY, ANY }),
        ::makeQuad(96, 48, sf::Vector2f(389, 344)));
    tm.addMatching(TextureMatcher::Matching({ SAME, ANY, SAME, ANY, ANY, ANY, SAME, ANY }),
        ::makeQuad(96, 48, sf::Vector2f(486, 344)));
    tm.addMatching(TextureMatcher::Matching({ SAME, ANY, SAME, ANY, SAME, ANY, ANY, ANY }),
        ::makeQuad(96, 48, sf::Vector2f(583, 344)));
    tm.addMatching(TextureMatcher::Matching({ SAME, ANY, SAME, ANY, SAME, ANY, SAME, ANY }),
        ::makeQuad(96, 48, sf::Vector2f(680, 344)));

    return tm;
}
