/* Copyright 2014 <Piotr Derkowski> */

#include "MinimapFrame.hpp"
#include "Renderer.hpp"
#include "MapModel.hpp"
#include "players/Players.hpp"
#include "MinimapRenderer.hpp"


namespace interface {


MinimapFrame::MinimapFrame(const MapModel& model, const Renderer* renderer)
    : renderer_(renderer), minimapRenderer_(model.getRowsNo(), model.getColumnsNo())
{ }

void MinimapFrame::setPosition(const sf::Vector2f& position) {
    position_ = position;
}

sf::Vector2f MinimapFrame::getSize() const {
    return minimapRenderer_.getTextureSize();
}

void MinimapFrame::updateBackground(const MapModel& model, const players::Player& player) {
    minimapRenderer_.updateBackground(model, player);
}

void MinimapFrame::updateDisplayedRectangle() {
    sf::FloatRect bounds = renderer_->getDisplayedRectangle();
    minimapRenderer_.updateDisplayedRectangle(bounds);
}

void MinimapFrame::draw() const {
    sf::Sprite minimapSprite;
    minimapSprite.setTexture(minimapRenderer_.getTexture());
    minimapSprite.setPosition(position_);

    Renderer::TargetProxy target = renderer_->getFixedTarget();
    target.get()->draw(minimapSprite);
}


}  // namespace interface
