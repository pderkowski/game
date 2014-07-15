/* Copyright 2014 <Piotr Derkowski> */

#ifndef TEXTURESETFACTORY_HPP_
#define TEXTURESETFACTORY_HPP_

#include "TextureSet.hpp"
#include "Tile.hpp"
#include "units/Unit.hpp"
#include "MiscellaneousEnums.hpp"

class TextureSetFactory {
public:
    static TextureSet<Tile> getBaseTextureSet();
    static TextureSet<Tile> getBlendTextureSet();
    static TextureSet<Tile> getOverlayTextureSet();
    static TextureSet<Tile> getAttributeTextureSet();
    static TextureSet<units::Unit> getUnitTextureSet();

    static TextureSet<Tile> getGridTextureSet();

    static TextureSet<miscellaneous::Type> getSelectionTextureSet();
    static TextureSet<tileenums::Direction> getPathTextureSet();
};

#endif  // TEXTURESETFACTORY_HPP_
