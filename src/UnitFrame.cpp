/* Copyright 2014 <Piotr Derkowski> */

#include "SFML/Graphics.hpp"
#include "units/Unit.hpp"
#include "Renderer.hpp"
#include "UnitFrame.hpp"
#include "Resources.hpp"
#include "players/Players.hpp"


UnitFrame::UnitFrame(const Renderer* renderer)
    : font_(Resources::loadFont("fonts/UbuntuMono.ttf")),
    characterSize_(20),
    horizontalSpacing_(10.0f, 0.0f),
    verticalSpacing_(0.0f, 10.0f),
    unitOwner_("", font_, characterSize_),
    unitName_("", font_, characterSize_),
    hpLeft_("", font_, characterSize_),
    movesLeft_("", font_, characterSize_),
    renderer_(renderer)
{ }

void UnitFrame::draw() const {
    Renderer::TargetProxy target = renderer_->getFixedTarget();

    target.get()->draw(unitOwner_);
    target.get()->draw(unitName_);
    target.get()->draw(hpLeft_);
    target.get()->draw(movesLeft_);
}

void UnitFrame::update(const players::Players& players) {
    if (players.isUnitSelected()) {
        setUnitDisplayed(players.getSelectedUnit());
    } else {
        clear();
    }
}

void UnitFrame::setUnitDisplayed(__attribute__((unused)) const units::Unit& unit) {
    unitOwner_.setString("Selected!");
    unitName_.setString("Selected!");
    hpLeft_.setString("Selected!");
    movesLeft_.setString("Selected!");
}

void UnitFrame::clear() {
    unitOwner_.setString("");
    unitName_.setString("");
    hpLeft_.setString("");
    movesLeft_.setString("");
}

void UnitFrame::setPosition(const sf::Vector2f& basePosition) {
    sf::Vector2f unitOwnerPosition = basePosition + horizontalSpacing_ + verticalSpacing_;
    unitOwner_.setPosition(unitOwnerPosition);

    sf::Vector2f unitNamePosition = unitOwnerPosition + verticalSpacing_ + getHeight(unitOwner_);
    unitName_.setPosition(unitNamePosition);

    sf::Vector2f hpLeftPosition = unitNamePosition + verticalSpacing_ + getHeight(unitName_);
    hpLeft_.setPosition(hpLeftPosition);

    sf::Vector2f movesLeftPosition = hpLeftPosition + verticalSpacing_ + getHeight(hpLeft_);
    movesLeft_.setPosition(movesLeftPosition);
}

sf::Vector2f UnitFrame::getSize() const {
    return getHeight(unitOwner_) + getHeight(unitName_) + getHeight(hpLeft_) + getHeight(movesLeft_)
        + 5.0f * verticalSpacing_ + sf::Vector2f(200.0f, 0.0f);
}

sf::Vector2f UnitFrame::getHeight(const sf::Text& text) const {
    return sf::Vector2f(0.0f, static_cast<float>(text.getCharacterSize()));
}
