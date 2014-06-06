/* Copyright 2014 <Piotr Derkowski> */

#ifndef TEXTURESETFACTORY_HPP_
#define TEXTURESETFACTORY_HPP_

#include "TextureSet.hpp"
#include "Tile.hpp"

class TextureSetFactory {
public:
    static TextureSet getTerrainTextureSet();
    static TextureSet getLandmarkTextureSet();

private:
    static TextureMatcher makeHillsTerrainMatcher();
    static TextureMatcher makeMountainsTerrainMatcher();
    static TextureMatcher makePlainsTerrainMatcher();
    static TextureMatcher makeWaterMatcher();
    static TextureMatcher makeHillsLandmarkMatcher();
    static TextureMatcher makeMountainsLandmarkMatcher();
};

#endif  // TEXTURESETFACTORY_HPP_
