/* Copyright 2014 <Piotr Derkowski> */

#ifndef TEXTURECOORDSFACTORY_HPP_
#define TEXTURECOORDSFACTORY_HPP_

#include "TextureCoords.hpp"
#include "Tile.hpp"

class TextureCoordsFactory {
public:
    static TextureCoords<Tile::Type> getTerrainTextureCoords();
    static TextureCoords<Tile::Type> getLandmarkTextureCoords();
};

#endif  // TEXTURECOORDSFACTORY_HPP_
