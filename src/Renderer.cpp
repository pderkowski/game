/* Copyright 2014 <Piotr Derkowski> */

#include <vector>
#include <memory>
#include <cmath>
#include <algorithm>
#include <utility>
#include "Utils.hpp"
#include "Coordinates.hpp"
#include "SFML/Graphics.hpp"
#include "Renderer.hpp"
#include "Settings.hpp"


Renderer::Renderer(const Settings& settings, std::shared_ptr<sf::RenderTarget> target)
    : rows_(settings.rows),
    columns_(settings.columns),
    tileWidth_(settings.tileWidth),
    tileHeight_(settings.tileHeight),
    target_(target),
    mapView_(sf::FloatRect(0, 0, target->getSize().x, target->getSize().y))
{ }

sf::Vector2f Renderer::getPosition(const IntIsoPoint& coords) const {
    CartPoint cartCoords = coords.toCartesian();
    return sf::Vector2f(utils::positiveModulo(cartCoords.x * tileWidth_ / 2, 2 * getMapWidth()),
        cartCoords.y * tileHeight_ / 2);
}

sf::Vector2f Renderer::getDualPosition(const IntIsoPoint& coords) const {
    sf::Vector2f primaryPosition = getPosition(coords);
    return sf::Vector2f(utils::positiveModulo(primaryPosition.x + getMapWidth(), 2 * getMapWidth()),
        primaryPosition.y);
}

unsigned Renderer::getMapWidth() const {
    return columns_ * tileWidth_;
}

unsigned Renderer::getMapHeight() const {
    return (rows_ - 1) * tileHeight_ / 2;
}

sf::Vector2u Renderer::getSize() const {
    return target_->getSize();
}

Renderer::TargetProxy Renderer::getFixedTarget() const {
    sf::View savedView = target_->getView();
    target_->setView(target_->getDefaultView());
    return TargetProxy(this, savedView);
}

Renderer::TargetProxy Renderer::getDynamicTarget() const {
    sf::View savedView = target_->getView();
    target_->setView(mapView_);
    return TargetProxy(this, savedView);
}

IntIsoPoint Renderer::getMapCoords(const sf::Vector2i& position) const {
    const int halfWidth = tileWidth_ / 2;
    const int halfHeight = tileHeight_ / 2;

    const sf::Vector2f coords = target_->mapPixelToCoords(position);
    const sf::Vector2i intCoords(lround(coords.x), lround(coords.y));
    const sf::Vector2i corner(intCoords.x - intCoords.x % halfWidth,
        intCoords.y - intCoords.y % halfHeight);
    const sf::Vector2i scaledCorner(corner.x / halfWidth, corner.y / halfHeight);

    sf::Vector2i firstCenter, otherCenter;
    if ((scaledCorner.x + scaledCorner.y) % 2 == 0) {
        firstCenter = corner;
        otherCenter = sf::Vector2i(corner.x + halfWidth, corner.y + halfHeight);
    } else {
        firstCenter = sf::Vector2i(corner.x + halfWidth, corner.y);
        otherCenter = sf::Vector2i(corner.x, corner.y + halfHeight);
    }

    const double distanceToFirst = sqrt(pow(coords.x - firstCenter.x, 2)
        + pow(coords.y - firstCenter.y, 2));
    const double distanceToOther = sqrt(pow(otherCenter.x - coords.x, 2)
        + pow(otherCenter.y - coords.y, 2));

    const sf::Vector2i closest = (distanceToFirst < distanceToOther)? firstCenter : otherCenter;
    const IntCartPoint scaledClosest = IntCartPoint(closest.x / halfWidth, closest.y / halfHeight);
    const IntIsoPoint isometric(scaledClosest.toIsometric());

    return isometric;
}

void Renderer::scrollView(int x, int y) {
    sf::Vector2f actualShift = boundShift(x, y);

    mapView_.move(actualShift);
    target_->setView(mapView_);

    if (actualShift != sf::Vector2f(0.0f, 0.0f)) {
        notify(RendererNotification{ getDisplayedRectangle() });
    }
}

void Renderer::scrollView(const sf::Vector2i& mousePosition) {
    int xShift = calculateHorizontalShift(mousePosition.x);
    int yShift = calculateVerticalShift(mousePosition.y);

    scrollView(xShift, yShift);
}

sf::Vector2f Renderer::boundShift(int x, int y) const {
    sf::Vector2f safeShift;

    sf::IntRect bounds(0, 0, getMapWidth(), getMapHeight());
    sf::IntRect displayed(mapView_.getCenter().x - mapView_.getSize().x / 2,
        mapView_.getCenter().y - mapView_.getSize().y / 2,
        mapView_.getSize().x, mapView_.getSize().y);

    int maxTopShiftPossible = bounds.top - displayed.top;
    int maxBottomShiftPossible = bounds.top + bounds.height - displayed.top - displayed.height;

    safeShift.x
        = static_cast<int>((displayed.left + x + getMapWidth()) % getMapWidth())
            - displayed.left;
    safeShift.y = (y < 0)? std::min(std::max(y, maxTopShiftPossible), maxBottomShiftPossible)
        : std::max(std::min(y, maxBottomShiftPossible), maxTopShiftPossible);

    return safeShift;
}

void Renderer::zoomView(int delta, const sf::Vector2i& mousePosition) {
    target_->setView(mapView_);
    const float zoomFactor = (delta > 0)? 4.0 / 5 : 5.0 / 4;

    if (canZoom(zoomFactor)) {
        target_->setView(mapView_);
        sf::Vector2f oldCoords = target_->mapPixelToCoords(mousePosition);
        mapView_.zoom(zoomFactor);
        target_->setView(mapView_);

        sf::Vector2f newCoords = target_->mapPixelToCoords(mousePosition);
        scrollView(oldCoords.x - newCoords.x, oldCoords.y - newCoords.y);

        notify(RendererNotification{ getDisplayedRectangle() });
    }
}

bool Renderer::canZoom(float zoomFactor) const {
    return mapView_.getSize().x * zoomFactor < getMapWidth()
        && mapView_.getSize().y * zoomFactor < getMapHeight();
}

sf::FloatRect Renderer::getDisplayedRectangle() const {
    target_->setView(mapView_);
    sf::Vector2i leftTop(0, 0);
    sf::Vector2i rightBottom(target_->getSize().x - 1, target_->getSize().y - 1);

    sf::Vector2f leftTopCoords = target_->mapPixelToCoords(leftTop);
    sf::Vector2f rightBottomCoords = target_->mapPixelToCoords(rightBottom);

    return sf::FloatRect(
        leftTopCoords.x / getMapWidth(),
        leftTopCoords.y / getMapHeight(),
        (rightBottomCoords.x - leftTopCoords.x) / getMapWidth(),
        (rightBottomCoords.y - leftTopCoords.y) / getMapHeight());
}

int Renderer::calculateHorizontalShift(int mouseXPosition) const {
    const int scrollMarginSize = 50;

    if (mouseXPosition < scrollMarginSize) {
        return 2 * (mouseXPosition - scrollMarginSize);
    } else if (mouseXPosition > static_cast<int>(getSize().x) - scrollMarginSize) {
        return 2 * (scrollMarginSize - (static_cast<int>(getSize().x) - mouseXPosition));
    } else {
        return 0;
    }
}

int Renderer::calculateVerticalShift(int mouseYPosition) const {
    const int scrollMarginSize = 50;

    if (mouseYPosition < scrollMarginSize) {
        return 2 * (mouseYPosition - scrollMarginSize);
    } else if (mouseYPosition > static_cast<int>(getSize().y) - scrollMarginSize) {
        return 2 * (scrollMarginSize - (static_cast<int>(getSize().y) - mouseYPosition));
    } else {
        return 0;
    }
}

Renderer::TargetProxy::~TargetProxy() {
    renderer_->target_->setView(savedView_);
}

std::shared_ptr<sf::RenderTarget> Renderer::TargetProxy::get() const {
    return renderer_->target_;
}

Renderer::TargetProxy::TargetProxy(const Renderer* renderer, const sf::View& savedView)
    : renderer_(renderer), savedView_(savedView)
{ }
