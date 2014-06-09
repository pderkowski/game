/* Copyright 2014 <Piotr Derkowski> */

#ifndef TEXTURESETFACTORY_HPP_
#define TEXTURESETFACTORY_HPP_

#include "TextureSet.hpp"
#include "Tile.hpp"

class TextureSetFactory {
public:
    static TextureSet getBaseTextureSet();
    static TextureSet getBlendTextureSet();
    static TextureSet getOverlayTextureSet();

private:
    static TextureMatcher makeHillsBaseMatcher();
    static TextureMatcher makeMountainsBaseMatcher();
    static TextureMatcher makeGrasslandBaseMatcher();
    static TextureMatcher makePlainsBaseMatcher();
    static TextureMatcher makeDesertBaseMatcher();
    static TextureMatcher makeWaterBaseMatcher();

    static TextureMatcher makeWaterBlendMatcher();
    static TextureMatcher makeGrasslandBlendMatcher();
    static TextureMatcher makePlainsBlendMatcher();
    static TextureMatcher makeDesertBlendMatcher();
    static TextureMatcher makeHillsBlendMatcher();
    static TextureMatcher makeMountainsBlendMatcher();

    static TextureMatcher makeHillsOverlayMatcher();
    static TextureMatcher makeMountainsOverlayMatcher();
};

#endif  // TEXTURESETFACTORY_HPP_
