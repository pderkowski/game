/* Copyright 2014 <Piotr Derkowski> */

#ifndef TEXTURESETFACTORY_HPP_
#define TEXTURESETFACTORY_HPP_

#include "TextureSet.hpp"
#include "Tile.hpp"
#include "units/Unit.hpp"

class TextureSetFactory {
public:
    static TextureSet<Tile> getBaseTextureSet();
    static TextureSet<Tile> getBlendTextureSet();
    static TextureSet<Tile> getOverlayTextureSet();
    static TextureSet<Tile> getAttributeTextureSet();
    static TextureSet<units::Unit> getUnitTextureSet();

    static TextureSet<Tile> getGridTextureSet();
};

#endif  // TEXTURESETFACTORY_HPP_
