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
    static TextureMatcher makePlainsBaseMatcher();
    static TextureMatcher makeWaterBlendMatcher();
    static TextureMatcher makePlainsBlendMatcher();
    static TextureMatcher makeWaterBaseMatcher();
    static TextureMatcher makeHillsOverlayMatcher();
    static TextureMatcher makeMountainsOverlayMatcher();
};

#endif  // TEXTURESETFACTORY_HPP_
