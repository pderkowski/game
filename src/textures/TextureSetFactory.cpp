/* Copyright 2014 <Piotr Derkowski> */

#include <vector>
#include <memory>
#include "SFML/Graphics.hpp"
#include "TextureSet.hpp"
#include "Tile.hpp"
#include "Attributes.hpp"
#include "TextureSetFactory.hpp"
#include "global/Resources.hpp"
#include "Matcher.hpp"
#include "textures/blends.hpp"
#include "textures/terrains.hpp"
#include "textures/landmarks.hpp"
#include "textures/units.hpp"
#include "textures/miscellaneous.hpp"
#include "TileEnums.hpp"
#include "units/Unit.hpp"
#include "MiscellaneousEnums.hpp"

using namespace tileenums;

#define ANY NeighborTypesMatcher::NeighborType::Any
#define SAME NeighborTypesMatcher::NeighborType::Same
#define DIFF NeighborTypesMatcher::NeighborType::Different

#define TOP Direction::Top
#define RIGHT Direction::Right
#define BOTTOM Direction::Bottom
#define LEFT Direction::Left


namespace textures {


TextureSet<Tile> TextureSetFactory::getBaseTextureSet() {
    TextureSet<Tile> ts(global::Resources::loadTexture("textures/terrains.png"));

    ts.add(std::shared_ptr<const NeighborTypesMatcher>(new NeighborTypesMatcher(Type::Water,
            { SAME, SAME, SAME, ANY, ANY, ANY, ANY, ANY })),
        textures::landmarks::water_t000);
    ts.add(std::shared_ptr<const NeighborTypesMatcher>(new NeighborTypesMatcher(Type::Water,
            { ANY, ANY, ANY, ANY, SAME, SAME, SAME, ANY })),
        textures::landmarks::water_b000);
    ts.add(std::shared_ptr<const NeighborTypesMatcher>(new NeighborTypesMatcher(Type::Water,
            { SAME, ANY, ANY, ANY, ANY, ANY, SAME, SAME })),
        textures::landmarks::water_l000);
    ts.add(std::shared_ptr<const NeighborTypesMatcher>(new NeighborTypesMatcher(Type::Water,
            { ANY, ANY, SAME, SAME, SAME, ANY, ANY, ANY })),
        textures::landmarks::water_r000);

    ts.add(std::shared_ptr<const NeighborTypesMatcher>(new NeighborTypesMatcher(Type::Water,
            { DIFF, SAME, SAME, ANY, ANY, ANY, ANY, ANY })),
        textures::landmarks::water_t100);
    ts.add(std::shared_ptr<const NeighborTypesMatcher>(new NeighborTypesMatcher(Type::Water,
            { ANY, ANY, ANY, ANY, DIFF, SAME, SAME, ANY })),
        textures::landmarks::water_b100);
    ts.add(std::shared_ptr<const NeighborTypesMatcher>(new NeighborTypesMatcher(Type::Water,
            { SAME, ANY, ANY, ANY, ANY, ANY, DIFF, SAME })),
        textures::landmarks::water_l100);
    ts.add(std::shared_ptr<const NeighborTypesMatcher>(new NeighborTypesMatcher(Type::Water,
            { ANY, ANY, DIFF, SAME, SAME, ANY, ANY, ANY })),
        textures::landmarks::water_r100);

    ts.add(std::shared_ptr<const NeighborTypesMatcher>(new NeighborTypesMatcher(Type::Water,
            { SAME, DIFF, SAME, ANY, ANY, ANY, ANY, ANY })),
        textures::landmarks::water_t010);
    ts.add(std::shared_ptr<const NeighborTypesMatcher>(new NeighborTypesMatcher(Type::Water,
            { ANY, ANY, ANY, ANY, SAME, DIFF, SAME, ANY })),
        textures::landmarks::water_b010);
    ts.add(std::shared_ptr<const NeighborTypesMatcher>(new NeighborTypesMatcher(Type::Water,
            { SAME, ANY, ANY, ANY, ANY, ANY, SAME, DIFF })),
        textures::landmarks::water_l010);
    ts.add(std::shared_ptr<const NeighborTypesMatcher>(new NeighborTypesMatcher(Type::Water,
            { ANY, ANY, SAME, DIFF, SAME, ANY, ANY, ANY })),
        textures::landmarks::water_r010);

    ts.add(std::shared_ptr<const NeighborTypesMatcher>(new NeighborTypesMatcher(Type::Water,
            { DIFF, DIFF, SAME, ANY, ANY, ANY, ANY, ANY })),
        textures::landmarks::water_t110);
    ts.add(std::shared_ptr<const NeighborTypesMatcher>(new NeighborTypesMatcher(Type::Water,
            { ANY, ANY, ANY, ANY, DIFF, DIFF, SAME, ANY })),
        textures::landmarks::water_b110);
    ts.add(std::shared_ptr<const NeighborTypesMatcher>(new NeighborTypesMatcher(Type::Water,
            { SAME, ANY, ANY, ANY, ANY, ANY, DIFF, DIFF })),
        textures::landmarks::water_l110);
    ts.add(std::shared_ptr<const NeighborTypesMatcher>(new NeighborTypesMatcher(Type::Water,
            { ANY, ANY, DIFF, DIFF, SAME, ANY, ANY, ANY })),
        textures::landmarks::water_r110);

    ts.add(std::shared_ptr<const NeighborTypesMatcher>(new NeighborTypesMatcher(Type::Water,
            { SAME, SAME, DIFF, ANY, ANY, ANY, ANY, ANY })),
        textures::landmarks::water_t001);
    ts.add(std::shared_ptr<const NeighborTypesMatcher>(new NeighborTypesMatcher(Type::Water,
            { ANY, ANY, ANY, ANY, SAME, SAME, DIFF, ANY })),
        textures::landmarks::water_b001);
    ts.add(std::shared_ptr<const NeighborTypesMatcher>(new NeighborTypesMatcher(Type::Water,
            { DIFF, ANY, ANY, ANY, ANY, ANY, SAME, SAME })),
        textures::landmarks::water_l001);
    ts.add(std::shared_ptr<const NeighborTypesMatcher>(new NeighborTypesMatcher(Type::Water,
            { ANY, ANY, SAME, SAME, DIFF, ANY, ANY, ANY })),
        textures::landmarks::water_r001);

    ts.add(std::shared_ptr<const NeighborTypesMatcher>(new NeighborTypesMatcher(Type::Water,
            { DIFF, SAME, DIFF, ANY, ANY, ANY, ANY, ANY })),
        textures::landmarks::water_t101);
    ts.add(std::shared_ptr<const NeighborTypesMatcher>(new NeighborTypesMatcher(Type::Water,
            { ANY, ANY, ANY, ANY, DIFF, SAME, DIFF, ANY })),
        textures::landmarks::water_b101);
    ts.add(std::shared_ptr<const NeighborTypesMatcher>(new NeighborTypesMatcher(Type::Water,
            { DIFF, ANY, ANY, ANY, ANY, ANY, DIFF, SAME })),
        textures::landmarks::water_l101);
    ts.add(std::shared_ptr<const NeighborTypesMatcher>(new NeighborTypesMatcher(Type::Water,
            { ANY, ANY, DIFF, SAME, DIFF, ANY, ANY, ANY })),
        textures::landmarks::water_r101);

    ts.add(std::shared_ptr<const NeighborTypesMatcher>(new NeighborTypesMatcher(Type::Water,
            { SAME, DIFF, DIFF, ANY, ANY, ANY, ANY, ANY })),
        textures::landmarks::water_t011);
    ts.add(std::shared_ptr<const NeighborTypesMatcher>(new NeighborTypesMatcher(Type::Water,
            { ANY, ANY, ANY, ANY, SAME, DIFF, DIFF, ANY })),
        textures::landmarks::water_b011);
    ts.add(std::shared_ptr<const NeighborTypesMatcher>(new NeighborTypesMatcher(Type::Water,
            { DIFF, ANY, ANY, ANY, ANY, ANY, SAME, DIFF })),
        textures::landmarks::water_l011);
    ts.add(std::shared_ptr<const NeighborTypesMatcher>(new NeighborTypesMatcher(Type::Water,
            { ANY, ANY, SAME, DIFF, DIFF, ANY, ANY, ANY })),
        textures::landmarks::water_r011);

    ts.add(std::shared_ptr<const NeighborTypesMatcher>(new NeighborTypesMatcher(Type::Water,
            { DIFF, DIFF, DIFF, ANY, ANY, ANY, ANY, ANY })),
        textures::landmarks::water_t111);
    ts.add(std::shared_ptr<const NeighborTypesMatcher>(new NeighborTypesMatcher(Type::Water,
            { ANY, ANY, ANY, ANY, DIFF, DIFF, DIFF, ANY })),
        textures::landmarks::water_b111);
    ts.add(std::shared_ptr<const NeighborTypesMatcher>(new NeighborTypesMatcher(Type::Water,
            { DIFF, ANY, ANY, ANY, ANY, ANY, DIFF, DIFF })),
        textures::landmarks::water_l111);
    ts.add(std::shared_ptr<const NeighborTypesMatcher>(new NeighborTypesMatcher(Type::Water,
            { ANY, ANY, DIFF, DIFF, DIFF, ANY, ANY, ANY })),
        textures::landmarks::water_r111);

    ts.add(std::make_shared<const TileTypeMatcher>(Type::Hills), textures::terrains::hills);
    ts.add(std::make_shared<const TileTypeMatcher>(Type::Mountains), textures::terrains::mountains);
    ts.add(std::make_shared<const TileTypeMatcher>(Type::Grassland), textures::terrains::grassland);
    ts.add(std::make_shared<const TileTypeMatcher>(Type::Plains), textures::terrains::plains);
    ts.add(std::make_shared<const TileTypeMatcher>(Type::Forest), textures::terrains::forest);
    ts.add(std::make_shared<const TileTypeMatcher>(Type::Desert), textures::terrains::desert);

    return ts;
}

TextureSet<Tile> TextureSetFactory::getBlendTextureSet() {
    TextureSet<Tile> ts(global::Resources::loadTexture("textures/blends.png"));

    ts.add(std::shared_ptr<const NeighborTypesMatcher>(new NeighborTypesMatcher(Type::Water,
            { DIFF, ANY, ANY, ANY, ANY, ANY, ANY, ANY })),
        textures::blends::water_T);
    ts.add(std::shared_ptr<const NeighborTypesMatcher>(new NeighborTypesMatcher(Type::Water,
            { ANY, ANY, DIFF, ANY, ANY, ANY, ANY, ANY })),
        textures::blends::water_R);
    ts.add(std::shared_ptr<const NeighborTypesMatcher>(new NeighborTypesMatcher(Type::Water,
            { ANY, ANY, ANY, ANY, DIFF, ANY, ANY, ANY })),
        textures::blends::water_B);
    ts.add(std::shared_ptr<const NeighborTypesMatcher>(new NeighborTypesMatcher(Type::Water,
            { ANY, ANY, ANY, ANY, ANY, ANY, DIFF, ANY })),
        textures::blends::water_L);

    ts.add(std::shared_ptr<const NeighborTypesMatcher>(new NeighborTypesMatcher(Type::Grassland,
            { DIFF, ANY, ANY, ANY, ANY, ANY, ANY, ANY })),
        textures::blends::grassland_T);
    ts.add(std::shared_ptr<const NeighborTypesMatcher>(new NeighborTypesMatcher(Type::Grassland,
            { ANY, ANY, DIFF, ANY, ANY, ANY, ANY, ANY })),
        textures::blends::grassland_R);
    ts.add(std::shared_ptr<const NeighborTypesMatcher>(new NeighborTypesMatcher(Type::Grassland,
            { ANY, ANY, ANY, ANY, DIFF, ANY, ANY, ANY })),
        textures::blends::grassland_B);
    ts.add(std::shared_ptr<const NeighborTypesMatcher>(new NeighborTypesMatcher(Type::Grassland,
            { ANY, ANY, ANY, ANY, ANY, ANY, DIFF, ANY })),
        textures::blends::grassland_L);

    ts.add(std::shared_ptr<const NeighborTypesMatcher>(new NeighborTypesMatcher(Type::Plains,
            { DIFF, ANY, ANY, ANY, ANY, ANY, ANY, ANY })),
        textures::blends::plains_T);
    ts.add(std::shared_ptr<const NeighborTypesMatcher>(new NeighborTypesMatcher(Type::Plains,
            { ANY, ANY, DIFF, ANY, ANY, ANY, ANY, ANY })),
        textures::blends::plains_R);
    ts.add(std::shared_ptr<const NeighborTypesMatcher>(new NeighborTypesMatcher(Type::Plains,
            { ANY, ANY, ANY, ANY, DIFF, ANY, ANY, ANY })),
        textures::blends::plains_B);
    ts.add(std::shared_ptr<const NeighborTypesMatcher>(new NeighborTypesMatcher(Type::Plains,
            { ANY, ANY, ANY, ANY, ANY, ANY, DIFF, ANY })),
        textures::blends::plains_L);

    ts.add(std::shared_ptr<const NeighborTypesMatcher>(new NeighborTypesMatcher(Type::Forest,
            { DIFF, ANY, ANY, ANY, ANY, ANY, ANY, ANY })),
        textures::blends::forest_T);
    ts.add(std::shared_ptr<const NeighborTypesMatcher>(new NeighborTypesMatcher(Type::Forest,
            { ANY, ANY, DIFF, ANY, ANY, ANY, ANY, ANY })),
        textures::blends::forest_R);
    ts.add(std::shared_ptr<const NeighborTypesMatcher>(new NeighborTypesMatcher(Type::Forest,
            { ANY, ANY, ANY, ANY, DIFF, ANY, ANY, ANY })),
        textures::blends::forest_B);
    ts.add(std::shared_ptr<const NeighborTypesMatcher>(new NeighborTypesMatcher(Type::Forest,
            { ANY, ANY, ANY, ANY, ANY, ANY, DIFF, ANY })),
        textures::blends::forest_L);

    ts.add(std::shared_ptr<const NeighborTypesMatcher>(new NeighborTypesMatcher(Type::Desert,
            { DIFF, ANY, ANY, ANY, ANY, ANY, ANY, ANY })),
        textures::blends::desert_T);
    ts.add(std::shared_ptr<const NeighborTypesMatcher>(new NeighborTypesMatcher(Type::Desert,
            { ANY, ANY, DIFF, ANY, ANY, ANY, ANY, ANY })),
        textures::blends::desert_R);
    ts.add(std::shared_ptr<const NeighborTypesMatcher>(new NeighborTypesMatcher(Type::Desert,
            { ANY, ANY, ANY, ANY, DIFF, ANY, ANY, ANY })),
        textures::blends::desert_B);
    ts.add(std::shared_ptr<const NeighborTypesMatcher>(new NeighborTypesMatcher(Type::Desert,
            { ANY, ANY, ANY, ANY, ANY, ANY, DIFF, ANY })),
        textures::blends::desert_L);

    ts.add(std::shared_ptr<const NeighborTypesMatcher>(new NeighborTypesMatcher(Type::Hills,
            { DIFF, ANY, ANY, ANY, ANY, ANY, ANY, ANY })),
        textures::blends::hills_T);
    ts.add(std::shared_ptr<const NeighborTypesMatcher>(new NeighborTypesMatcher(Type::Hills,
            { ANY, ANY, DIFF, ANY, ANY, ANY, ANY, ANY })),
        textures::blends::hills_R);
    ts.add(std::shared_ptr<const NeighborTypesMatcher>(new NeighborTypesMatcher(Type::Hills,
            { ANY, ANY, ANY, ANY, DIFF, ANY, ANY, ANY })),
        textures::blends::hills_B);
    ts.add(std::shared_ptr<const NeighborTypesMatcher>(new NeighborTypesMatcher(Type::Hills,
            { ANY, ANY, ANY, ANY, ANY, ANY, DIFF, ANY })),
        textures::blends::hills_L);

    ts.add(std::shared_ptr<const NeighborTypesMatcher>(new NeighborTypesMatcher(Type::Mountains,
            { DIFF, ANY, ANY, ANY, ANY, ANY, ANY, ANY })),
        textures::blends::mountains_T);
    ts.add(std::shared_ptr<const NeighborTypesMatcher>(new NeighborTypesMatcher(Type::Mountains,
            { ANY, ANY, DIFF, ANY, ANY, ANY, ANY, ANY })),
        textures::blends::mountains_R);
    ts.add(std::shared_ptr<const NeighborTypesMatcher>(new NeighborTypesMatcher(Type::Mountains,
            { ANY, ANY, ANY, ANY, DIFF, ANY, ANY, ANY })),
        textures::blends::mountains_B);
    ts.add(std::shared_ptr<const NeighborTypesMatcher>(new NeighborTypesMatcher(Type::Mountains,
            { ANY, ANY, ANY, ANY, ANY, ANY, DIFF, ANY })),
        textures::blends::mountains_L);

    return ts;
}

TextureSet<Tile> TextureSetFactory::getGridTextureSet() {
    TextureSet<Tile> ts(global::Resources::loadTexture("textures/terrains.png"));

    ts.add(std::shared_ptr<const AlwaysMatcher>(new AlwaysMatcher()),
        textures::terrains::visibleKnown);

    return ts;
}

TextureSet<Tile> TextureSetFactory::getOverlayTextureSet() {
    TextureSet<Tile> ts(global::Resources::loadTexture("textures/landmarks.png"));

    ts.add(std::shared_ptr<const NeighborTypesMatcher>(new NeighborTypesMatcher(Type::Forest,
            { DIFF, ANY, DIFF, ANY, DIFF, ANY, DIFF, ANY })),
        textures::landmarks::forest_t0r0b0l0);
    ts.add(std::shared_ptr<const NeighborTypesMatcher>(new NeighborTypesMatcher(Type::Forest,
            { SAME, ANY, DIFF, ANY, DIFF, ANY, DIFF, ANY })),
        textures::landmarks::forest_t1r0b0l0);
    ts.add(std::shared_ptr<const NeighborTypesMatcher>(new NeighborTypesMatcher(Type::Forest,
            { DIFF, ANY, DIFF, ANY, DIFF, ANY, SAME, ANY })),
        textures::landmarks::forest_t0r0b0l1);
    ts.add(std::shared_ptr<const NeighborTypesMatcher>(new NeighborTypesMatcher(Type::Forest,
            { SAME, ANY, DIFF, ANY, DIFF, ANY, SAME, ANY })),
        textures::landmarks::forest_t1r0b0l1);
    ts.add(std::shared_ptr<const NeighborTypesMatcher>(new NeighborTypesMatcher(Type::Forest,
            { DIFF, ANY, DIFF, ANY, SAME, ANY, DIFF, ANY })),
        textures::landmarks::forest_t0r0b1l0);
    ts.add(std::shared_ptr<const NeighborTypesMatcher>(new NeighborTypesMatcher(Type::Forest,
            { SAME, ANY, DIFF, ANY, SAME, ANY, DIFF, ANY })),
        textures::landmarks::forest_t1r0b1l0);
    ts.add(std::shared_ptr<const NeighborTypesMatcher>(new NeighborTypesMatcher(Type::Forest,
            { DIFF, ANY, DIFF, ANY, SAME, ANY, SAME, ANY })),
        textures::landmarks::forest_t0r0b1l1);
    ts.add(std::shared_ptr<const NeighborTypesMatcher>(new NeighborTypesMatcher(Type::Forest,
            { SAME, ANY, DIFF, ANY, SAME, ANY, SAME, ANY })),
        textures::landmarks::forest_t1r0b1l1);
    ts.add(std::shared_ptr<const NeighborTypesMatcher>(new NeighborTypesMatcher(Type::Forest,
            { DIFF, ANY, SAME, ANY, DIFF, ANY, DIFF, ANY })),
        textures::landmarks::forest_t0r1b0l0);
    ts.add(std::shared_ptr<const NeighborTypesMatcher>(new NeighborTypesMatcher(Type::Forest,
            { SAME, ANY, SAME, ANY, DIFF, ANY, DIFF, ANY })),
        textures::landmarks::forest_t1r1b0l0);
    ts.add(std::shared_ptr<const NeighborTypesMatcher>(new NeighborTypesMatcher(Type::Forest,
            { DIFF, ANY, SAME, ANY, DIFF, ANY, SAME, ANY })),
        textures::landmarks::forest_t0r1b0l1);
    ts.add(std::shared_ptr<const NeighborTypesMatcher>(new NeighborTypesMatcher(Type::Forest,
            { SAME, ANY, SAME, ANY, DIFF, ANY, SAME, ANY })),
        textures::landmarks::forest_t1r1b0l1);
    ts.add(std::shared_ptr<const NeighborTypesMatcher>(new NeighborTypesMatcher(Type::Forest,
            { DIFF, ANY, SAME, ANY, SAME, ANY, DIFF, ANY })),
        textures::landmarks::forest_t0r1b1l0);
    ts.add(std::shared_ptr<const NeighborTypesMatcher>(new NeighborTypesMatcher(Type::Forest,
            { SAME, ANY, SAME, ANY, SAME, ANY, DIFF, ANY })),
        textures::landmarks::forest_t1r1b1l0);
    ts.add(std::shared_ptr<const NeighborTypesMatcher>(new NeighborTypesMatcher(Type::Forest,
            { DIFF, ANY, SAME, ANY, SAME, ANY, SAME, ANY })),
        textures::landmarks::forest_t0r1b1l1);
    ts.add(std::shared_ptr<const NeighborTypesMatcher>(new NeighborTypesMatcher(Type::Forest,
            { SAME, ANY, SAME, ANY, SAME, ANY, SAME, ANY })),
        textures::landmarks::forest_t1r1b1l1);

    ts.add(std::shared_ptr<const NeighborTypesMatcher>(new NeighborTypesMatcher(Type::Hills,
            { DIFF, ANY, DIFF, ANY, DIFF, ANY, DIFF, ANY })),
        textures::landmarks::hills_t0r0b0l0);
    ts.add(std::shared_ptr<const NeighborTypesMatcher>(new NeighborTypesMatcher(Type::Hills,
            { SAME, ANY, DIFF, ANY, DIFF, ANY, DIFF, ANY })),
        textures::landmarks::hills_t1r0b0l0);
    ts.add(std::shared_ptr<const NeighborTypesMatcher>(new NeighborTypesMatcher(Type::Hills,
            { DIFF, ANY, DIFF, ANY, DIFF, ANY, SAME, ANY })),
        textures::landmarks::hills_t0r0b0l1);
    ts.add(std::shared_ptr<const NeighborTypesMatcher>(new NeighborTypesMatcher(Type::Hills,
            { SAME, ANY, DIFF, ANY, DIFF, ANY, SAME, ANY })),
        textures::landmarks::hills_t1r0b0l1);
    ts.add(std::shared_ptr<const NeighborTypesMatcher>(new NeighborTypesMatcher(Type::Hills,
            { DIFF, ANY, DIFF, ANY, SAME, ANY, DIFF, ANY })),
        textures::landmarks::hills_t0r0b1l0);
    ts.add(std::shared_ptr<const NeighborTypesMatcher>(new NeighborTypesMatcher(Type::Hills,
            { SAME, ANY, DIFF, ANY, SAME, ANY, DIFF, ANY })),
        textures::landmarks::hills_t1r0b1l0);
    ts.add(std::shared_ptr<const NeighborTypesMatcher>(new NeighborTypesMatcher(Type::Hills,
            { DIFF, ANY, DIFF, ANY, SAME, ANY, SAME, ANY })),
        textures::landmarks::hills_t0r0b1l1);
    ts.add(std::shared_ptr<const NeighborTypesMatcher>(new NeighborTypesMatcher(Type::Hills,
            { SAME, ANY, DIFF, ANY, SAME, ANY, SAME, ANY })),
        textures::landmarks::hills_t1r0b1l1);
    ts.add(std::shared_ptr<const NeighborTypesMatcher>(new NeighborTypesMatcher(Type::Hills,
            { DIFF, ANY, SAME, ANY, DIFF, ANY, DIFF, ANY })),
        textures::landmarks::hills_t0r1b0l0);
    ts.add(std::shared_ptr<const NeighborTypesMatcher>(new NeighborTypesMatcher(Type::Hills,
            { SAME, ANY, SAME, ANY, DIFF, ANY, DIFF, ANY })),
        textures::landmarks::hills_t1r1b0l0);
    ts.add(std::shared_ptr<const NeighborTypesMatcher>(new NeighborTypesMatcher(Type::Hills,
            { DIFF, ANY, SAME, ANY, DIFF, ANY, SAME, ANY })),
        textures::landmarks::hills_t0r1b0l1);
    ts.add(std::shared_ptr<const NeighborTypesMatcher>(new NeighborTypesMatcher(Type::Hills,
            { SAME, ANY, SAME, ANY, DIFF, ANY, SAME, ANY })),
        textures::landmarks::hills_t1r1b0l1);
    ts.add(std::shared_ptr<const NeighborTypesMatcher>(new NeighborTypesMatcher(Type::Hills,
            { DIFF, ANY, SAME, ANY, SAME, ANY, DIFF, ANY })),
        textures::landmarks::hills_t0r1b1l0);
    ts.add(std::shared_ptr<const NeighborTypesMatcher>(new NeighborTypesMatcher(Type::Hills,
            { SAME, ANY, SAME, ANY, SAME, ANY, DIFF, ANY })),
        textures::landmarks::hills_t1r1b1l0);
    ts.add(std::shared_ptr<const NeighborTypesMatcher>(new NeighborTypesMatcher(Type::Hills,
            { DIFF, ANY, SAME, ANY, SAME, ANY, SAME, ANY })),
        textures::landmarks::hills_t0r1b1l1);
    ts.add(std::shared_ptr<const NeighborTypesMatcher>(new NeighborTypesMatcher(Type::Hills,
            { SAME, ANY, SAME, ANY, SAME, ANY, SAME, ANY })),
        textures::landmarks::hills_t1r1b1l1);

    ts.add(std::shared_ptr<const NeighborTypesMatcher>(new NeighborTypesMatcher(Type::Mountains,
            { DIFF, ANY, DIFF, ANY, DIFF, ANY, DIFF, ANY })),
        textures::landmarks::mountains_t0r0b0l0);
    ts.add(std::shared_ptr<const NeighborTypesMatcher>(new NeighborTypesMatcher(Type::Mountains,
            { SAME, ANY, DIFF, ANY, DIFF, ANY, DIFF, ANY })),
        textures::landmarks::mountains_t1r0b0l0);
    ts.add(std::shared_ptr<const NeighborTypesMatcher>(new NeighborTypesMatcher(Type::Mountains,
            { DIFF, ANY, DIFF, ANY, DIFF, ANY, SAME, ANY })),
        textures::landmarks::mountains_t0r0b0l1);
    ts.add(std::shared_ptr<const NeighborTypesMatcher>(new NeighborTypesMatcher(Type::Mountains,
            { SAME, ANY, DIFF, ANY, DIFF, ANY, SAME, ANY })),
        textures::landmarks::mountains_t1r0b0l1);
    ts.add(std::shared_ptr<const NeighborTypesMatcher>(new NeighborTypesMatcher(Type::Mountains,
            { DIFF, ANY, DIFF, ANY, SAME, ANY, DIFF, ANY })),
        textures::landmarks::mountains_t0r0b1l0);
    ts.add(std::shared_ptr<const NeighborTypesMatcher>(new NeighborTypesMatcher(Type::Mountains,
            { SAME, ANY, DIFF, ANY, SAME, ANY, DIFF, ANY })),
        textures::landmarks::mountains_t1r0b1l0);
    ts.add(std::shared_ptr<const NeighborTypesMatcher>(new NeighborTypesMatcher(Type::Mountains,
            { DIFF, ANY, DIFF, ANY, SAME, ANY, SAME, ANY })),
        textures::landmarks::mountains_t0r0b1l1);
    ts.add(std::shared_ptr<const NeighborTypesMatcher>(new NeighborTypesMatcher(Type::Mountains,
            { SAME, ANY, DIFF, ANY, SAME, ANY, SAME, ANY })),
        textures::landmarks::mountains_t1r0b1l1);
    ts.add(std::shared_ptr<const NeighborTypesMatcher>(new NeighborTypesMatcher(Type::Mountains,
            { DIFF, ANY, SAME, ANY, DIFF, ANY, DIFF, ANY })),
        textures::landmarks::mountains_t0r1b0l0);
    ts.add(std::shared_ptr<const NeighborTypesMatcher>(new NeighborTypesMatcher(Type::Mountains,
            { SAME, ANY, SAME, ANY, DIFF, ANY, DIFF, ANY })),
        textures::landmarks::mountains_t1r1b0l0);
    ts.add(std::shared_ptr<const NeighborTypesMatcher>(new NeighborTypesMatcher(Type::Mountains,
            { DIFF, ANY, SAME, ANY, DIFF, ANY, SAME, ANY })),
        textures::landmarks::mountains_t0r1b0l1);
    ts.add(std::shared_ptr<const NeighborTypesMatcher>(new NeighborTypesMatcher(Type::Mountains,
            { SAME, ANY, SAME, ANY, DIFF, ANY, SAME, ANY })),
        textures::landmarks::mountains_t1r1b0l1);
    ts.add(std::shared_ptr<const NeighborTypesMatcher>(new NeighborTypesMatcher(Type::Mountains,
            { DIFF, ANY, SAME, ANY, SAME, ANY, DIFF, ANY })),
        textures::landmarks::mountains_t0r1b1l0);
    ts.add(std::shared_ptr<const NeighborTypesMatcher>(new NeighborTypesMatcher(Type::Mountains,
            { SAME, ANY, SAME, ANY, SAME, ANY, DIFF, ANY })),
        textures::landmarks::mountains_t1r1b1l0);
    ts.add(std::shared_ptr<const NeighborTypesMatcher>(new NeighborTypesMatcher(Type::Mountains,
            { DIFF, ANY, SAME, ANY, SAME, ANY, SAME, ANY })),
        textures::landmarks::mountains_t0r1b1l1);
    ts.add(std::shared_ptr<const NeighborTypesMatcher>(new NeighborTypesMatcher(Type::Mountains,
            { SAME, ANY, SAME, ANY, SAME, ANY, SAME, ANY })),
        textures::landmarks::mountains_t1r1b1l1);

    return ts;
}

TextureSet<Tile> TextureSetFactory::getAttributeTextureSet() {
    TextureSet<Tile> ts(global::Resources::loadTexture("textures/landmarks.png"));

    ts.add(std::shared_ptr<const Matcher<Tile>>(new Matcher<Tile>([] (const Tile& tile) {
        const auto river = tile.attributes.river;
        return tile.type != Type::Water && river && !river->hasDirection(TOP) && !river->hasDirection(RIGHT)
            && !river->hasDirection(BOTTOM) && !river->hasDirection(LEFT);
    })), textures::landmarks::river_t0r0b0l0);

    ts.add(std::shared_ptr<const Matcher<Tile>>(new Matcher<Tile>([] (const Tile& tile) {
        const auto river = tile.attributes.river;
        return tile.type != Type::Water && river && river->hasDirection(TOP) && !river->hasDirection(RIGHT)
            && !river->hasDirection(BOTTOM) && !river->hasDirection(LEFT);
    })), textures::landmarks::river_t1r0b0l0);

    ts.add(std::shared_ptr<const Matcher<Tile>>(new Matcher<Tile>([] (const Tile& tile) {
        const auto river = tile.attributes.river;
        return tile.type != Type::Water && river && !river->hasDirection(TOP) && !river->hasDirection(RIGHT)
            && !river->hasDirection(BOTTOM) && river->hasDirection(LEFT);
    })), textures::landmarks::river_t0r0b0l1);

    ts.add(std::shared_ptr<const Matcher<Tile>>(new Matcher<Tile>([] (const Tile& tile) {
        const auto river = tile.attributes.river;
        return tile.type != Type::Water && river && river->hasDirection(TOP) && !river->hasDirection(RIGHT)
            && !river->hasDirection(BOTTOM) && river->hasDirection(LEFT);
    })), textures::landmarks::river_t1r0b0l1);

    ts.add(std::shared_ptr<const Matcher<Tile>>(new Matcher<Tile>([] (const Tile& tile) {
        const auto river = tile.attributes.river;
        return tile.type != Type::Water && river && !river->hasDirection(TOP) && !river->hasDirection(RIGHT)
            && river->hasDirection(BOTTOM) && !river->hasDirection(LEFT);
    })), textures::landmarks::river_t0r0b1l0);

    ts.add(std::shared_ptr<const Matcher<Tile>>(new Matcher<Tile>([] (const Tile& tile) {
        const auto river = tile.attributes.river;
        return tile.type != Type::Water && river && river->hasDirection(TOP) && !river->hasDirection(RIGHT)
            && river->hasDirection(BOTTOM) && !river->hasDirection(LEFT);
    })), textures::landmarks::river_t1r0b1l0);

    ts.add(std::shared_ptr<const Matcher<Tile>>(new Matcher<Tile>([] (const Tile& tile) {
        const auto river = tile.attributes.river;
        return tile.type != Type::Water && river && !river->hasDirection(TOP) && !river->hasDirection(RIGHT)
            && river->hasDirection(BOTTOM) && river->hasDirection(LEFT);
    })), textures::landmarks::river_t0r0b1l1);

    ts.add(std::shared_ptr<const Matcher<Tile>>(new Matcher<Tile>([] (const Tile& tile) {
        const auto river = tile.attributes.river;
        return tile.type != Type::Water && river && river->hasDirection(TOP) && !river->hasDirection(RIGHT)
            && river->hasDirection(BOTTOM) && river->hasDirection(LEFT);
    })), textures::landmarks::river_t1r0b1l1);

    ts.add(std::shared_ptr<const Matcher<Tile>>(new Matcher<Tile>([] (const Tile& tile) {
        const auto river = tile.attributes.river;
        return tile.type != Type::Water && river && !river->hasDirection(TOP) && river->hasDirection(RIGHT)
            && !river->hasDirection(BOTTOM) && !river->hasDirection(LEFT);
    })), textures::landmarks::river_t0r1b0l0);

    ts.add(std::shared_ptr<const Matcher<Tile>>(new Matcher<Tile>([] (const Tile& tile) {
        const auto river = tile.attributes.river;
        return tile.type != Type::Water && river && river->hasDirection(TOP) && river->hasDirection(RIGHT)
            && !river->hasDirection(BOTTOM) && !river->hasDirection(LEFT);
    })), textures::landmarks::river_t1r1b0l0);

    ts.add(std::shared_ptr<const Matcher<Tile>>(new Matcher<Tile>([] (const Tile& tile) {
        const auto river = tile.attributes.river;
        return tile.type != Type::Water && river && !river->hasDirection(TOP) && river->hasDirection(RIGHT)
            && !river->hasDirection(BOTTOM) && river->hasDirection(LEFT);
    })), textures::landmarks::river_t0r1b0l1);

    ts.add(std::shared_ptr<const Matcher<Tile>>(new Matcher<Tile>([] (const Tile& tile) {
        const auto river = tile.attributes.river;
        return tile.type != Type::Water && river && river->hasDirection(TOP) && river->hasDirection(RIGHT)
            && !river->hasDirection(BOTTOM) && river->hasDirection(LEFT);
    })), textures::landmarks::river_t1r1b0l1);

    ts.add(std::shared_ptr<const Matcher<Tile>>(new Matcher<Tile>([] (const Tile& tile) {
        const auto river = tile.attributes.river;
        return tile.type != Type::Water && river && !river->hasDirection(TOP) && river->hasDirection(RIGHT)
            && river->hasDirection(BOTTOM) && !river->hasDirection(LEFT);
    })), textures::landmarks::river_t0r1b1l0);

    ts.add(std::shared_ptr<const Matcher<Tile>>(new Matcher<Tile>([] (const Tile& tile) {
        const auto river = tile.attributes.river;
        return tile.type != Type::Water && river && river->hasDirection(TOP) && river->hasDirection(RIGHT)
            && river->hasDirection(BOTTOM) && !river->hasDirection(LEFT);
    })), textures::landmarks::river_t1r1b1l0);

    ts.add(std::shared_ptr<const Matcher<Tile>>(new Matcher<Tile>([] (const Tile& tile) {
        const auto river = tile.attributes.river;
        return tile.type != Type::Water && river && !river->hasDirection(TOP) && river->hasDirection(RIGHT)
            && river->hasDirection(BOTTOM) && river->hasDirection(LEFT);
    })), textures::landmarks::river_t0r1b1l1);

    ts.add(std::shared_ptr<const Matcher<Tile>>(new Matcher<Tile>([] (const Tile& tile) {
        const auto river = tile.attributes.river;
        return tile.type != Type::Water && river && river->hasDirection(TOP) && river->hasDirection(RIGHT)
            && river->hasDirection(BOTTOM) && river->hasDirection(LEFT);
    })), textures::landmarks::river_t1r1b1l1);


    ts.add(std::shared_ptr<const Matcher<Tile>>(new Matcher<Tile>([] (const Tile& tile) {
        const auto river = tile.attributes.river;
        return tile.type == Type::Water && river && river->hasDirection(TOP);
    })), textures::landmarks::river_estuary_t);

    ts.add(std::shared_ptr<const Matcher<Tile>>(new Matcher<Tile>([] (const Tile& tile) {
        const auto river = tile.attributes.river;
        return tile.type == Type::Water && river && river->hasDirection(RIGHT);
    })), textures::landmarks::river_estuary_r);

    ts.add(std::shared_ptr<const Matcher<Tile>>(new Matcher<Tile>([] (const Tile& tile) {
        const auto river = tile.attributes.river;
        return tile.type == Type::Water && river && river->hasDirection(BOTTOM);
    })), textures::landmarks::river_estuary_b);

    ts.add(std::shared_ptr<const Matcher<Tile>>(new Matcher<Tile>([] (const Tile& tile) {
        const auto river = tile.attributes.river;
        return tile.type == Type::Water && river && river->hasDirection(LEFT);
    })), textures::landmarks::river_estuary_l);

    return ts;
}

TextureSet<::units::Unit> TextureSetFactory::getUnitTextureSet() {
    using namespace ::units;

    TextureSet<Unit> ts(global::Resources::loadTexture("textures/units.png"));

    ts.add(std::shared_ptr<const Matcher<Unit>>(new Matcher<Unit>([] (const Unit& unit) {
        return unit.getType() == ::units::Type::Phalanx;
    })), textures::units::phalanx);

    ts.add(std::shared_ptr<const Matcher<Unit>>(new Matcher<Unit>([] (const Unit& unit) {
        return unit.getType() == ::units::Type::Trireme;
    })), textures::units::trireme);

    return ts;
}

TextureSet<::miscellaneous::Type> TextureSetFactory::getSelectionTextureSet() {
    TextureSet<::miscellaneous::Type> ts(global::Resources::loadTexture("textures/miscellaneous.png"));

    ts.add(std::shared_ptr<const Matcher<::miscellaneous::Type>>(
        new Matcher<::miscellaneous::Type>([] (const ::miscellaneous::Type& type)
    {
        return type == ::miscellaneous::Type::Source;
    })), textures::miscellaneous::source);

    ts.add(std::shared_ptr<const Matcher<::miscellaneous::Type>>(
        new Matcher<::miscellaneous::Type>([] (const ::miscellaneous::Type& type)
    {
        return type == ::miscellaneous::Type::Destination;
    })), textures::miscellaneous::destination);

    return ts;
}


TextureSet<tileenums::Direction> TextureSetFactory::getPathTextureSet() {
    TextureSet<tileenums::Direction> ts(global::Resources::loadTexture("textures/miscellaneous.png"));

    ts.add(std::shared_ptr<const Matcher<tileenums::Direction>>(
        new Matcher<tileenums::Direction>([] (const tileenums::Direction& direction)
    {
        return direction == tileenums::Direction::Top;
    })), textures::miscellaneous::top);

    ts.add(std::shared_ptr<const Matcher<tileenums::Direction>>(
        new Matcher<tileenums::Direction>([] (const tileenums::Direction& direction)
    {
        return direction == tileenums::Direction::TopRight;
    })), textures::miscellaneous::topRight);

    ts.add(std::shared_ptr<const Matcher<tileenums::Direction>>(
        new Matcher<tileenums::Direction>([] (const tileenums::Direction& direction)
    {
        return direction == tileenums::Direction::Right;
    })), textures::miscellaneous::right);

    ts.add(std::shared_ptr<const Matcher<tileenums::Direction>>(
        new Matcher<tileenums::Direction>([] (const tileenums::Direction& direction)
    {
        return direction == tileenums::Direction::BottomRight;
    })), textures::miscellaneous::bottomRight);

    ts.add(std::shared_ptr<const Matcher<tileenums::Direction>>(
        new Matcher<tileenums::Direction>([] (const tileenums::Direction& direction)
    {
        return direction == tileenums::Direction::Bottom;
    })), textures::miscellaneous::bottom);

    ts.add(std::shared_ptr<const Matcher<tileenums::Direction>>(
        new Matcher<tileenums::Direction>([] (const tileenums::Direction& direction)
    {
        return direction == tileenums::Direction::BottomLeft;
    })), textures::miscellaneous::bottomLeft);

    ts.add(std::shared_ptr<const Matcher<tileenums::Direction>>(
        new Matcher<tileenums::Direction>([] (const tileenums::Direction& direction)
    {
        return direction == tileenums::Direction::Left;
    })), textures::miscellaneous::left);

    ts.add(std::shared_ptr<const Matcher<tileenums::Direction>>(
        new Matcher<tileenums::Direction>([] (const tileenums::Direction& direction)
    {
        return direction == tileenums::Direction::TopLeft;
    })), textures::miscellaneous::topLeft);

    return ts;
}

TextureSet<players::TileVisibility> TextureSetFactory::getFogTextureSet() {
    TextureSet<players::TileVisibility> ts(global::Resources::loadTexture("textures/terrains.png"));

    ts.add(std::shared_ptr<const Matcher<players::TileVisibility>>(
        new Matcher<players::TileVisibility>([] (const players::TileVisibility& visibility)
    {
        return visibility == players::TileVisibility::UnvisibleKnown;
    })), textures::terrains::unvisibleKnown);

    ts.add(std::shared_ptr<const Matcher<players::TileVisibility>>(
        new Matcher<players::TileVisibility>([] (const players::TileVisibility& visibility)
    {
        return visibility == players::TileVisibility::Unknown;
    })), textures::terrains::unknown);

    return ts;
}

TextureSet<::miscellaneous::Flag> TextureSetFactory::getFlagTextureSet() {
    TextureSet<::miscellaneous::Flag> ts(global::Resources::loadTexture("textures/miscellaneous.png"));

    ts.add(std::shared_ptr<const Matcher<::miscellaneous::Flag>>(
        new Matcher<::miscellaneous::Flag>([] (const ::miscellaneous::Flag& flag)
    {
        return flag == ::miscellaneous::Flag::Blue;
    })), textures::miscellaneous::blueFlag);

    ts.add(std::shared_ptr<const Matcher<::miscellaneous::Flag>>(
        new Matcher<::miscellaneous::Flag>([] (const ::miscellaneous::Flag& flag)
    {
        return flag == ::miscellaneous::Flag::Red;
    })), textures::miscellaneous::redFlag);

    return ts;
}


}  // namespace textures
