/* Copyright 2014 <Piotr Derkowski> */

#include <string>
#include "SFML/Graphics.hpp"
#include "units/Unit.hpp"
#include "Renderer.hpp"
#include "UnitFrame.hpp"
#include "Resources.hpp"
#include "players/Players.hpp"


namespace interface {


UnitFrame::UnitFrame(const Renderer* renderer)
    : font_(Resources::loadFont("fonts/UbuntuMono.ttf")),
    characterSize_(30),
    horizontalSpacing_(10.0f, 0.0f),
    verticalSpacing_(0.0f, 10.0f),
    unitName_("", font_, characterSize_),
    hpLeft_("", font_, characterSize_),
    movesLeft_("", font_, characterSize_),
    renderer_(renderer)
{
    unitName_.setColor(sf::Color::Black);
    unitName_.setStyle(sf::Text::Style::Bold);
    movesLeft_.setColor(sf::Color::Black);
    hpLeft_.setColor(sf::Color::Black);
}

void UnitFrame::draw() const {
    Renderer::TargetProxy target = renderer_->getFixedTarget();

    target.get()->draw(unitName_);
    target.get()->draw(hpLeft_);
    target.get()->draw(movesLeft_);
}

void UnitFrame::setUnitDisplayed(const units::Unit& unit) {
    unitName_.setString(unit.getName());
    hpLeft_.setString("HP: " + std::to_string(unit.getHpLeft()) + "/" + std::to_string(unit.getBaseHp()));
    movesLeft_.setString("Moves: " + std::to_string(unit.getMovesLeft()) + "/" + std::to_string(unit.getBaseMoves()));
}

void UnitFrame::clear() {
    unitName_.setString("");
    hpLeft_.setString("");
    movesLeft_.setString("");
}

void UnitFrame::setPosition(const sf::Vector2f& basePosition) {
    sf::Vector2f unitNamePosition = basePosition + horizontalSpacing_ + verticalSpacing_;
    unitName_.setPosition(unitNamePosition);

    sf::Vector2f hpLeftPosition = unitNamePosition + verticalSpacing_ + getHeight(unitName_);
    hpLeft_.setPosition(hpLeftPosition);

    sf::Vector2f movesLeftPosition = hpLeftPosition + verticalSpacing_ + getHeight(hpLeft_);
    movesLeft_.setPosition(movesLeftPosition);
}

sf::Vector2f UnitFrame::getSize() const {
    return getHeight(unitName_) + getHeight(hpLeft_) + getHeight(movesLeft_)
        + 4.0f * verticalSpacing_ + sf::Vector2f(240.0f, 0.0f);
}

sf::Vector2f UnitFrame::getHeight(const sf::Text& text) const {
    return sf::Vector2f(0.0f, static_cast<float>(text.getCharacterSize()));
}


}
