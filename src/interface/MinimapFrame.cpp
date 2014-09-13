/* Copyright 2014 <Piotr Derkowski> */

#include "MinimapFrame.hpp"
#include "Renderer.hpp"
#include "map/MapModel.hpp"
#include "players/Players.hpp"
#include "MinimapRenderer.hpp"
#include "Settings.hpp"


namespace interface {


MinimapFrame::MinimapFrame(const Settings& settings, const Renderer* renderer)
    : renderer_(renderer), minimapRenderer_(settings.rows, settings.columns)
{ }

void MinimapFrame::setPosition(const sf::Vector2f& position) {
    position_ = position;
}

sf::Vector2f MinimapFrame::getSize() const {
    return minimapRenderer_.getTextureSize();
}

void MinimapFrame::updateBackground(const map::MapModel& model, const players::Player& player) {
    minimapRenderer_.updateBackground(model, player);
}

void MinimapFrame::updateDisplayedRectangle(const sf::FloatRect& displayedRectangle) {
    minimapRenderer_.updateDisplayedRectangle(displayedRectangle);
}

void MinimapFrame::draw() const {
    sf::Sprite minimapSprite;
    minimapSprite.setTexture(minimapRenderer_.getTexture());
    minimapSprite.setPosition(position_);

    Renderer::TargetProxy target = renderer_->getFixedTarget();
    target.get()->draw(minimapSprite);
}


}  // namespace interface
