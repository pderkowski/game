/* Copyright 2014 <Piotr Derkowski> */

#ifndef INTERFACE_INTERFACE_HPP_
#define INTERFACE_INTERFACE_HPP_

#include "Layout.hpp"
#include "UnitFrame.hpp"
#include "MinimapFrame.hpp"
#include "Observer.hpp"
#include "RendererNotification.hpp"
class GameNotification;
class Renderer;
class Settings;
namespace map { class MapModel; }
namespace players { class Player; }


namespace interface {


class Interface : public Observer<RendererNotification>, public Observer<GameNotification> {
public:
    explicit Interface(const Settings& settings, const Renderer* renderer);
    virtual ~Interface() { }

    void draw() const;

private:
    void updateMinimapBackground(const map::MapModel* map, const players::Player* player);
    void updateSelectedUnitFrame(const players::Player* player);

    virtual void onNotify(const RendererNotification& notification);
    virtual void onNotify(const GameNotification& notification);

private:
    Layout layout_;
    MinimapFrame minimapFrame_;
    UnitFrame unitFrame_;
};


}  // namespace interface

#endif  // INTERFACE_INTERFACE_HPP_
