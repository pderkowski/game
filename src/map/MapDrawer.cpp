/* Copyright 2014 <Piotr Derkowski> */

#include "SFML/Graphics.hpp"
#include "MapModel.hpp"
#include "MapDrawer.hpp"
#include "Tile.hpp"
#include "Coordinates.hpp"
#include "textures/TextureSetFactory.hpp"
#include "Layer.hpp"
#include "Renderer.hpp"


namespace map {


MapDrawer::MapDrawer(const MapModel& model, const Renderer* renderer)
    : renderer_(renderer)
{
    setModel(model);
}

void MapDrawer::setModel(const MapModel& model) {
    layers_.clear();
    layers_.push_back(Layer<Tile>(textures::TextureSetFactory::getBaseTextureSet()));
    layers_.push_back(Layer<Tile>(textures::TextureSetFactory::getBlendTextureSet()));
    layers_.push_back(Layer<Tile>(textures::TextureSetFactory::getGridTextureSet()));
    layers_.push_back(Layer<Tile>(textures::TextureSetFactory::getOverlayTextureSet()));
    layers_.push_back(Layer<Tile>(textures::TextureSetFactory::getAttributeTextureSet()));

    for (int r = 0; r < model.getRowsNo(); ++r) {
        for (int c = 0; c < model.getColumnsNo(); ++c) {
            auto tile = model.getTile(IntIsoPoint(c, r));
            addTileToLayers(tile);
        }
    }
}

void MapDrawer::addTileToLayers(const Tile& tile) {
    for (auto& layer : layers_) {
        auto tilePosition = renderer_->getPosition(IntIsoPoint(tile.coords.toIsometric()));
        auto dualTilePosition = renderer_->getDualPosition(IntIsoPoint(tile.coords.toIsometric()));

        layer.add(tile, tilePosition);
        layer.add(tile, dualTilePosition);
    }
}

void MapDrawer::draw() const {
    Renderer::TargetProxy target = renderer_->getDynamicTarget();

    for (const auto& layer : layers_) {
        target.get()->draw(layer);
    }
}


}  // namespace map
