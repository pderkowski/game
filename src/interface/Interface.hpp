/* Copyright 2014 <Piotr Derkowski> */

#ifndef INTERFACE_INTERFACE_HPP_
#define INTERFACE_INTERFACE_HPP_

#include "Layout.hpp"
#include "UnitFrame.hpp"
#include "MinimapFrame.hpp"
class Renderer;
class MapModel;
namespace players { class Players; }


namespace interface {


class Interface {
public:
    explicit Interface(const MapModel* model, const players::Players* players,
        const Renderer* renderer);

    void setModel(const MapModel* model);

    void draw() const;

    void updateEverything();

    void updateMinimapBackground();
    void updateMinimapDisplayedRectangle();

    void updateSelectedUnitFrame();

private:
    const MapModel* model_;

    const players::Players* players_;

    Layout layout_;
    MinimapFrame minimapFrame_;
    UnitFrame unitFrame_;
};


}  // namespace interface

#endif  // INTERFACE_INTERFACE_HPP_
