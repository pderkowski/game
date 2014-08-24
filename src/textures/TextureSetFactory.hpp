/* Copyright 2014 <Piotr Derkowski> */

#ifndef TEXTURES_TEXTURESETFACTORY_HPP_
#define TEXTURES_TEXTURESETFACTORY_HPP_

#include "TextureSet.hpp"
#include "Tile.hpp"
#include "units/Unit.hpp"
#include "MiscellaneousEnums.hpp"
#include "players/Fog.hpp"


namespace textures {

class TextureSetFactory {
public:
    static TextureSet<Tile> getBaseTextureSet();
    static TextureSet<Tile> getBlendTextureSet();
    static TextureSet<Tile> getGridTextureSet();
    static TextureSet<Tile> getOverlayTextureSet();
    static TextureSet<Tile> getAttributeTextureSet();
    static TextureSet<units::Unit> getUnitTextureSet();

    static TextureSet<miscellaneous::Type> getSelectionTextureSet();
    static TextureSet<miscellaneous::Flag> getFlagTextureSet();
    static TextureSet<tileenums::Direction> getPathTextureSet();

    static TextureSet<players::TileVisibility> getFogTextureSet();
};


}  // namespace textures


#endif  // TEXTURES_TEXTURESETFACTORY_HPP_
