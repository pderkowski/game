/* Copyright 2014 <Piotr Derkowski> */

#include <vector>
#include <memory>
#include "SFML/Graphics.hpp"
#include "TextureSet.hpp"
#include "Tile.hpp"
#include "TextureSetFactory.hpp"
#include "Resources.hpp"
#include "Matcher.hpp"
#include "textures/blends.hpp"
#include "textures/terrains.hpp"
#include "textures/landmarks.hpp"

#define ANY NeighborTypesMatcher::NeighborType::Any
#define SAME NeighborTypesMatcher::NeighborType::Same
#define DIFF NeighborTypesMatcher::NeighborType::Different

TextureSet TextureSetFactory::getBaseTextureSet() {
    TextureSet ts(Resources::loadTexture("textures/terrains.png"));

    ts.add(std::shared_ptr<const NeighborTypesMatcher>(new NeighborTypesMatcher(Tile::Type::Water,
			{ SAME, SAME, SAME, ANY, ANY, ANY, ANY, ANY })),
        textures::landmarks::water_t000);
    ts.add(std::shared_ptr<const NeighborTypesMatcher>(new NeighborTypesMatcher(Tile::Type::Water,
			{ ANY, ANY, ANY, ANY, SAME, SAME, SAME, ANY })),
        textures::landmarks::water_b000);
    ts.add(std::shared_ptr<const NeighborTypesMatcher>(new NeighborTypesMatcher(Tile::Type::Water,
			{ SAME, ANY, ANY, ANY, ANY, ANY, SAME, SAME })),
        textures::landmarks::water_l000);
    ts.add(std::shared_ptr<const NeighborTypesMatcher>(new NeighborTypesMatcher(Tile::Type::Water,
			{ ANY, ANY, SAME, SAME, SAME, ANY, ANY, ANY })),
        textures::landmarks::water_r000);

    ts.add(std::shared_ptr<const NeighborTypesMatcher>(new NeighborTypesMatcher(Tile::Type::Water,
			{ DIFF, SAME, SAME, ANY, ANY, ANY, ANY, ANY })),
        textures::landmarks::water_t100);
    ts.add(std::shared_ptr<const NeighborTypesMatcher>(new NeighborTypesMatcher(Tile::Type::Water,
			{ ANY, ANY, ANY, ANY, DIFF, SAME, SAME, ANY })),
        textures::landmarks::water_b100);
    ts.add(std::shared_ptr<const NeighborTypesMatcher>(new NeighborTypesMatcher(Tile::Type::Water,
			{ SAME, ANY, ANY, ANY, ANY, ANY, DIFF, SAME })),
        textures::landmarks::water_l100);
    ts.add(std::shared_ptr<const NeighborTypesMatcher>(new NeighborTypesMatcher(Tile::Type::Water,
			{ ANY, ANY, DIFF, SAME, SAME, ANY, ANY, ANY })),
        textures::landmarks::water_r100);

    ts.add(std::shared_ptr<const NeighborTypesMatcher>(new NeighborTypesMatcher(Tile::Type::Water,
			{ SAME, DIFF, SAME, ANY, ANY, ANY, ANY, ANY })),
        textures::landmarks::water_t010);
    ts.add(std::shared_ptr<const NeighborTypesMatcher>(new NeighborTypesMatcher(Tile::Type::Water,
			{ ANY, ANY, ANY, ANY, SAME, DIFF, SAME, ANY })),
        textures::landmarks::water_b010);
    ts.add(std::shared_ptr<const NeighborTypesMatcher>(new NeighborTypesMatcher(Tile::Type::Water,
			{ SAME, ANY, ANY, ANY, ANY, ANY, SAME, DIFF })),
        textures::landmarks::water_l010);
    ts.add(std::shared_ptr<const NeighborTypesMatcher>(new NeighborTypesMatcher(Tile::Type::Water,
			{ ANY, ANY, SAME, DIFF, SAME, ANY, ANY, ANY })),
        textures::landmarks::water_r010);

    ts.add(std::shared_ptr<const NeighborTypesMatcher>(new NeighborTypesMatcher(Tile::Type::Water,
			{ DIFF, DIFF, SAME, ANY, ANY, ANY, ANY, ANY })),
        textures::landmarks::water_t110);
    ts.add(std::shared_ptr<const NeighborTypesMatcher>(new NeighborTypesMatcher(Tile::Type::Water,
			{ ANY, ANY, ANY, ANY, DIFF, DIFF, SAME, ANY })),
        textures::landmarks::water_b110);
    ts.add(std::shared_ptr<const NeighborTypesMatcher>(new NeighborTypesMatcher(Tile::Type::Water,
			{ SAME, ANY, ANY, ANY, ANY, ANY, DIFF, DIFF })),
        textures::landmarks::water_l110);
    ts.add(std::shared_ptr<const NeighborTypesMatcher>(new NeighborTypesMatcher(Tile::Type::Water,
			{ ANY, ANY, DIFF, DIFF, SAME, ANY, ANY, ANY })),
        textures::landmarks::water_r110);

    ts.add(std::shared_ptr<const NeighborTypesMatcher>(new NeighborTypesMatcher(Tile::Type::Water,
			{ SAME, SAME, DIFF, ANY, ANY, ANY, ANY, ANY })),
        textures::landmarks::water_t001);
    ts.add(std::shared_ptr<const NeighborTypesMatcher>(new NeighborTypesMatcher(Tile::Type::Water,
			{ ANY, ANY, ANY, ANY, SAME, SAME, DIFF, ANY })),
        textures::landmarks::water_b001);
    ts.add(std::shared_ptr<const NeighborTypesMatcher>(new NeighborTypesMatcher(Tile::Type::Water,
			{ DIFF, ANY, ANY, ANY, ANY, ANY, SAME, SAME })),
        textures::landmarks::water_l001);
    ts.add(std::shared_ptr<const NeighborTypesMatcher>(new NeighborTypesMatcher(Tile::Type::Water,
			{ ANY, ANY, SAME, SAME, DIFF, ANY, ANY, ANY })),
        textures::landmarks::water_r001);

    ts.add(std::shared_ptr<const NeighborTypesMatcher>(new NeighborTypesMatcher(Tile::Type::Water,
			{ DIFF, SAME, DIFF, ANY, ANY, ANY, ANY, ANY })),
        textures::landmarks::water_t101);
    ts.add(std::shared_ptr<const NeighborTypesMatcher>(new NeighborTypesMatcher(Tile::Type::Water,
			{ ANY, ANY, ANY, ANY, DIFF, SAME, DIFF, ANY })),
        textures::landmarks::water_b101);
    ts.add(std::shared_ptr<const NeighborTypesMatcher>(new NeighborTypesMatcher(Tile::Type::Water,
			{ DIFF, ANY, ANY, ANY, ANY, ANY, DIFF, SAME })),
        textures::landmarks::water_l101);
    ts.add(std::shared_ptr<const NeighborTypesMatcher>(new NeighborTypesMatcher(Tile::Type::Water,
			{ ANY, ANY, DIFF, SAME, DIFF, ANY, ANY, ANY })),
        textures::landmarks::water_r101);

    ts.add(std::shared_ptr<const NeighborTypesMatcher>(new NeighborTypesMatcher(Tile::Type::Water,
			{ SAME, DIFF, DIFF, ANY, ANY, ANY, ANY, ANY })),
        textures::landmarks::water_t011);
    ts.add(std::shared_ptr<const NeighborTypesMatcher>(new NeighborTypesMatcher(Tile::Type::Water,
			{ ANY, ANY, ANY, ANY, SAME, DIFF, DIFF, ANY })),
        textures::landmarks::water_b011);
    ts.add(std::shared_ptr<const NeighborTypesMatcher>(new NeighborTypesMatcher(Tile::Type::Water,
			{ DIFF, ANY, ANY, ANY, ANY, ANY, SAME, DIFF })),
        textures::landmarks::water_l011);
    ts.add(std::shared_ptr<const NeighborTypesMatcher>(new NeighborTypesMatcher(Tile::Type::Water,
			{ ANY, ANY, SAME, DIFF, DIFF, ANY, ANY, ANY })),
        textures::landmarks::water_r011);

    ts.add(std::shared_ptr<const NeighborTypesMatcher>(new NeighborTypesMatcher(Tile::Type::Water,
			{ DIFF, DIFF, DIFF, ANY, ANY, ANY, ANY, ANY })),
        textures::landmarks::water_t111);
    ts.add(std::shared_ptr<const NeighborTypesMatcher>(new NeighborTypesMatcher(Tile::Type::Water,
			{ ANY, ANY, ANY, ANY, DIFF, DIFF, DIFF, ANY })),
        textures::landmarks::water_b111);
    ts.add(std::shared_ptr<const NeighborTypesMatcher>(new NeighborTypesMatcher(Tile::Type::Water,
			{ DIFF, ANY, ANY, ANY, ANY, ANY, DIFF, DIFF })),
        textures::landmarks::water_l111);
    ts.add(std::shared_ptr<const NeighborTypesMatcher>(new NeighborTypesMatcher(Tile::Type::Water,
			{ ANY, ANY, DIFF, DIFF, DIFF, ANY, ANY, ANY })),
        textures::landmarks::water_r111);

    ts.add(std::make_shared<const TileTypeMatcher>(Tile::Type::Hills), textures::terrains::hills);
    ts.add(std::make_shared<const TileTypeMatcher>(Tile::Type::Mountains), textures::terrains::mountains);
    ts.add(std::make_shared<const TileTypeMatcher>(Tile::Type::Grassland), textures::terrains::grassland);
    ts.add(std::make_shared<const TileTypeMatcher>(Tile::Type::Plains), textures::terrains::plains);
    ts.add(std::make_shared<const TileTypeMatcher>(Tile::Type::River), textures::terrains::river);
    ts.add(std::make_shared<const TileTypeMatcher>(Tile::Type::Forest), textures::terrains::forest);
    ts.add(std::make_shared<const TileTypeMatcher>(Tile::Type::Desert), textures::terrains::desert);

    return ts;
}

TextureSet TextureSetFactory::getBlendTextureSet() {
    TextureSet ts(Resources::loadTexture("textures/blends.png"));

    ts.add(std::shared_ptr<const NeighborTypesMatcher>(new NeighborTypesMatcher(Tile::Type::Water,
			{ DIFF, ANY, ANY, ANY, ANY, ANY, ANY, ANY })),
        textures::blends::water_T);
    ts.add(std::shared_ptr<const NeighborTypesMatcher>(new NeighborTypesMatcher(Tile::Type::Water,
			{ ANY, ANY, DIFF, ANY, ANY, ANY, ANY, ANY })),
        textures::blends::water_R);
    ts.add(std::shared_ptr<const NeighborTypesMatcher>(new NeighborTypesMatcher(Tile::Type::Water,
			{ ANY, ANY, ANY, ANY, DIFF, ANY, ANY, ANY })),
        textures::blends::water_B);
    ts.add(std::shared_ptr<const NeighborTypesMatcher>(new NeighborTypesMatcher(Tile::Type::Water,
			{ ANY, ANY, ANY, ANY, ANY, ANY, DIFF, ANY })),
        textures::blends::water_L);

    ts.add(std::shared_ptr<const NeighborTypesMatcher>(new NeighborTypesMatcher(Tile::Type::Grassland,
			{ DIFF, ANY, ANY, ANY, ANY, ANY, ANY, ANY })),
        textures::blends::grassland_T);
    ts.add(std::shared_ptr<const NeighborTypesMatcher>(new NeighborTypesMatcher(Tile::Type::Grassland,
			{ ANY, ANY, DIFF, ANY, ANY, ANY, ANY, ANY })),
        textures::blends::grassland_R);
    ts.add(std::shared_ptr<const NeighborTypesMatcher>(new NeighborTypesMatcher(Tile::Type::Grassland,
			{ ANY, ANY, ANY, ANY, DIFF, ANY, ANY, ANY })),
        textures::blends::grassland_B);
    ts.add(std::shared_ptr<const NeighborTypesMatcher>(new NeighborTypesMatcher(Tile::Type::Grassland,
			{ ANY, ANY, ANY, ANY, ANY, ANY, DIFF, ANY })),
        textures::blends::grassland_L);

    ts.add(std::shared_ptr<const NeighborTypesMatcher>(new NeighborTypesMatcher(Tile::Type::River,
			{ DIFF, ANY, ANY, ANY, ANY, ANY, ANY, ANY })),
        textures::blends::river_T);
    ts.add(std::shared_ptr<const NeighborTypesMatcher>(new NeighborTypesMatcher(Tile::Type::River,
			{ ANY, ANY, DIFF, ANY, ANY, ANY, ANY, ANY })),
        textures::blends::river_R);
    ts.add(std::shared_ptr<const NeighborTypesMatcher>(new NeighborTypesMatcher(Tile::Type::River,
			{ ANY, ANY, ANY, ANY, DIFF, ANY, ANY, ANY })),
        textures::blends::river_B);
    ts.add(std::shared_ptr<const NeighborTypesMatcher>(new NeighborTypesMatcher(Tile::Type::River,
			{ ANY, ANY, ANY, ANY, ANY, ANY, DIFF, ANY })),
        textures::blends::river_L);

    ts.add(std::shared_ptr<const NeighborTypesMatcher>(new NeighborTypesMatcher(Tile::Type::Plains,
			{ DIFF, ANY, ANY, ANY, ANY, ANY, ANY, ANY })),
        textures::blends::plains_T);
    ts.add(std::shared_ptr<const NeighborTypesMatcher>(new NeighborTypesMatcher(Tile::Type::Plains,
			{ ANY, ANY, DIFF, ANY, ANY, ANY, ANY, ANY })),
        textures::blends::plains_R);
    ts.add(std::shared_ptr<const NeighborTypesMatcher>(new NeighborTypesMatcher(Tile::Type::Plains,
			{ ANY, ANY, ANY, ANY, DIFF, ANY, ANY, ANY })),
        textures::blends::plains_B);
    ts.add(std::shared_ptr<const NeighborTypesMatcher>(new NeighborTypesMatcher(Tile::Type::Plains,
			{ ANY, ANY, ANY, ANY, ANY, ANY, DIFF, ANY })),
        textures::blends::plains_L);

    ts.add(std::shared_ptr<const NeighborTypesMatcher>(new NeighborTypesMatcher(Tile::Type::Forest,
			{ DIFF, ANY, ANY, ANY, ANY, ANY, ANY, ANY })),
        textures::blends::forest_T);
    ts.add(std::shared_ptr<const NeighborTypesMatcher>(new NeighborTypesMatcher(Tile::Type::Forest,
			{ ANY, ANY, DIFF, ANY, ANY, ANY, ANY, ANY })),
        textures::blends::forest_R);
    ts.add(std::shared_ptr<const NeighborTypesMatcher>(new NeighborTypesMatcher(Tile::Type::Forest,
			{ ANY, ANY, ANY, ANY, DIFF, ANY, ANY, ANY })),
        textures::blends::forest_B);
    ts.add(std::shared_ptr<const NeighborTypesMatcher>(new NeighborTypesMatcher(Tile::Type::Forest,
			{ ANY, ANY, ANY, ANY, ANY, ANY, DIFF, ANY })),
        textures::blends::forest_L);

    ts.add(std::shared_ptr<const NeighborTypesMatcher>(new NeighborTypesMatcher(Tile::Type::Desert,
			{ DIFF, ANY, ANY, ANY, ANY, ANY, ANY, ANY })),
        textures::blends::desert_T);
    ts.add(std::shared_ptr<const NeighborTypesMatcher>(new NeighborTypesMatcher(Tile::Type::Desert,
			{ ANY, ANY, DIFF, ANY, ANY, ANY, ANY, ANY })),
        textures::blends::desert_R);
    ts.add(std::shared_ptr<const NeighborTypesMatcher>(new NeighborTypesMatcher(Tile::Type::Desert,
			{ ANY, ANY, ANY, ANY, DIFF, ANY, ANY, ANY })),
        textures::blends::desert_B);
    ts.add(std::shared_ptr<const NeighborTypesMatcher>(new NeighborTypesMatcher(Tile::Type::Desert,
			{ ANY, ANY, ANY, ANY, ANY, ANY, DIFF, ANY })),
        textures::blends::desert_L);

    ts.add(std::shared_ptr<const NeighborTypesMatcher>(new NeighborTypesMatcher(Tile::Type::Hills,
			{ DIFF, ANY, ANY, ANY, ANY, ANY, ANY, ANY })),
        textures::blends::hills_T);
    ts.add(std::shared_ptr<const NeighborTypesMatcher>(new NeighborTypesMatcher(Tile::Type::Hills,
			{ ANY, ANY, DIFF, ANY, ANY, ANY, ANY, ANY })),
        textures::blends::hills_R);
    ts.add(std::shared_ptr<const NeighborTypesMatcher>(new NeighborTypesMatcher(Tile::Type::Hills,
			{ ANY, ANY, ANY, ANY, DIFF, ANY, ANY, ANY })),
        textures::blends::hills_B);
    ts.add(std::shared_ptr<const NeighborTypesMatcher>(new NeighborTypesMatcher(Tile::Type::Hills,
			{ ANY, ANY, ANY, ANY, ANY, ANY, DIFF, ANY })),
        textures::blends::hills_L);

    ts.add(std::shared_ptr<const NeighborTypesMatcher>(new NeighborTypesMatcher(Tile::Type::Mountains,
			{ DIFF, ANY, ANY, ANY, ANY, ANY, ANY, ANY })),
        textures::blends::mountains_T);
    ts.add(std::shared_ptr<const NeighborTypesMatcher>(new NeighborTypesMatcher(Tile::Type::Mountains,
			{ ANY, ANY, DIFF, ANY, ANY, ANY, ANY, ANY })),
        textures::blends::mountains_R);
    ts.add(std::shared_ptr<const NeighborTypesMatcher>(new NeighborTypesMatcher(Tile::Type::Mountains,
			{ ANY, ANY, ANY, ANY, DIFF, ANY, ANY, ANY })),
        textures::blends::mountains_B);
    ts.add(std::shared_ptr<const NeighborTypesMatcher>(new NeighborTypesMatcher(Tile::Type::Mountains,
			{ ANY, ANY, ANY, ANY, ANY, ANY, DIFF, ANY })),
        textures::blends::mountains_L);

    return ts;
}

TextureSet TextureSetFactory::getOverlayTextureSet() {
    TextureSet ts(Resources::loadTexture("textures/landmarks.png"));

    ts.add(std::shared_ptr<const NeighborTypesMatcher>(new NeighborTypesMatcher(Tile::Type::River,
			{ DIFF, ANY, DIFF, ANY, DIFF, ANY, DIFF, ANY })),
        textures::landmarks::river_t0r0b0l0);
    ts.add(std::shared_ptr<const NeighborTypesMatcher>(new NeighborTypesMatcher(Tile::Type::River,
			{ SAME, ANY, DIFF, ANY, DIFF, ANY, DIFF, ANY })),
        textures::landmarks::river_t1r0b0l0);
    ts.add(std::shared_ptr<const NeighborTypesMatcher>(new NeighborTypesMatcher(Tile::Type::River,
			{ DIFF, ANY, DIFF, ANY, DIFF, ANY, SAME, ANY })),
        textures::landmarks::river_t0r0b0l1);
    ts.add(std::shared_ptr<const NeighborTypesMatcher>(new NeighborTypesMatcher(Tile::Type::River,
			{ SAME, ANY, DIFF, ANY, DIFF, ANY, SAME, ANY })),
        textures::landmarks::river_t1r0b0l1);
    ts.add(std::shared_ptr<const NeighborTypesMatcher>(new NeighborTypesMatcher(Tile::Type::River,
			{ DIFF, ANY, DIFF, ANY, SAME, ANY, DIFF, ANY })),
        textures::landmarks::river_t0r0b1l0);
    ts.add(std::shared_ptr<const NeighborTypesMatcher>(new NeighborTypesMatcher(Tile::Type::River,
			{ SAME, ANY, DIFF, ANY, SAME, ANY, DIFF, ANY })),
        textures::landmarks::river_t1r0b1l0);
    ts.add(std::shared_ptr<const NeighborTypesMatcher>(new NeighborTypesMatcher(Tile::Type::River,
			{ DIFF, ANY, DIFF, ANY, SAME, ANY, SAME, ANY })),
        textures::landmarks::river_t0r0b1l1);
    ts.add(std::shared_ptr<const NeighborTypesMatcher>(new NeighborTypesMatcher(Tile::Type::River,
			{ SAME, ANY, DIFF, ANY, SAME, ANY, SAME, ANY })),
        textures::landmarks::river_t1r0b1l1);
    ts.add(std::shared_ptr<const NeighborTypesMatcher>(new NeighborTypesMatcher(Tile::Type::River,
			{ DIFF, ANY, SAME, ANY, DIFF, ANY, DIFF, ANY })),
        textures::landmarks::river_t0r1b0l0);
    ts.add(std::shared_ptr<const NeighborTypesMatcher>(new NeighborTypesMatcher(Tile::Type::River,
			{ SAME, ANY, SAME, ANY, DIFF, ANY, DIFF, ANY })),
        textures::landmarks::river_t1r1b0l0);
    ts.add(std::shared_ptr<const NeighborTypesMatcher>(new NeighborTypesMatcher(Tile::Type::River,
			{ DIFF, ANY, SAME, ANY, DIFF, ANY, SAME, ANY })),
        textures::landmarks::river_t0r1b0l1);
    ts.add(std::shared_ptr<const NeighborTypesMatcher>(new NeighborTypesMatcher(Tile::Type::River,
			{ SAME, ANY, SAME, ANY, DIFF, ANY, SAME, ANY })),
        textures::landmarks::river_t1r1b0l1);
    ts.add(std::shared_ptr<const NeighborTypesMatcher>(new NeighborTypesMatcher(Tile::Type::River,
			{ DIFF, ANY, SAME, ANY, SAME, ANY, DIFF, ANY })),
        textures::landmarks::river_t0r1b1l0);
    ts.add(std::shared_ptr<const NeighborTypesMatcher>(new NeighborTypesMatcher(Tile::Type::River,
			{ SAME, ANY, SAME, ANY, SAME, ANY, DIFF, ANY })),
        textures::landmarks::river_t1r1b1l0);
    ts.add(std::shared_ptr<const NeighborTypesMatcher>(new NeighborTypesMatcher(Tile::Type::River,
			{ DIFF, ANY, SAME, ANY, SAME, ANY, SAME, ANY })),
        textures::landmarks::river_t0r1b1l1);
    ts.add(std::shared_ptr<const NeighborTypesMatcher>(new NeighborTypesMatcher(Tile::Type::River,
			{ SAME, ANY, SAME, ANY, SAME, ANY, SAME, ANY })),
        textures::landmarks::river_t1r1b1l1);

    ts.add(std::shared_ptr<const NeighborTypesMatcher>(new NeighborTypesMatcher(Tile::Type::Forest,
			{ ANY, ANY, ANY, ANY, ANY, ANY, ANY, ANY })),
        textures::landmarks::forest_t0r0b0l0);
    ts.add(std::shared_ptr<const NeighborTypesMatcher>(new NeighborTypesMatcher(Tile::Type::Forest,
			{ SAME, ANY, ANY, ANY, ANY, ANY, ANY, ANY })),
        textures::landmarks::forest_t1r0b0l0);
    ts.add(std::shared_ptr<const NeighborTypesMatcher>(new NeighborTypesMatcher(Tile::Type::Forest,
			{ ANY, ANY, ANY, ANY, ANY, ANY, SAME, ANY })),
        textures::landmarks::forest_t0r0b0l1);
    ts.add(std::shared_ptr<const NeighborTypesMatcher>(new NeighborTypesMatcher(Tile::Type::Forest,
			{ SAME, ANY, ANY, ANY, ANY, ANY, SAME, ANY })),
        textures::landmarks::forest_t1r0b0l1);
    ts.add(std::shared_ptr<const NeighborTypesMatcher>(new NeighborTypesMatcher(Tile::Type::Forest,
			{ ANY, ANY, ANY, ANY, SAME, ANY, ANY, ANY })),
        textures::landmarks::forest_t0r0b1l0);
    ts.add(std::shared_ptr<const NeighborTypesMatcher>(new NeighborTypesMatcher(Tile::Type::Forest,
			{ SAME, ANY, ANY, ANY, SAME, ANY, ANY, ANY })),
        textures::landmarks::forest_t1r0b1l0);
    ts.add(std::shared_ptr<const NeighborTypesMatcher>(new NeighborTypesMatcher(Tile::Type::Forest,
			{ ANY, ANY, ANY, ANY, SAME, ANY, SAME, ANY })),
        textures::landmarks::forest_t0r0b1l1);
    ts.add(std::shared_ptr<const NeighborTypesMatcher>(new NeighborTypesMatcher(Tile::Type::Forest,
			{ SAME, ANY, ANY, ANY, SAME, ANY, SAME, ANY })),
        textures::landmarks::forest_t1r0b1l1);
    ts.add(std::shared_ptr<const NeighborTypesMatcher>(new NeighborTypesMatcher(Tile::Type::Forest,
			{ ANY, ANY, SAME, ANY, ANY, ANY, ANY, ANY })),
        textures::landmarks::forest_t0r1b0l0);
    ts.add(std::shared_ptr<const NeighborTypesMatcher>(new NeighborTypesMatcher(Tile::Type::Forest,
			{ SAME, ANY, SAME, ANY, ANY, ANY, ANY, ANY })),
        textures::landmarks::forest_t1r1b0l0);
    ts.add(std::shared_ptr<const NeighborTypesMatcher>(new NeighborTypesMatcher(Tile::Type::Forest,
			{ ANY, ANY, SAME, ANY, ANY, ANY, SAME, ANY })),
        textures::landmarks::forest_t0r1b0l1);
    ts.add(std::shared_ptr<const NeighborTypesMatcher>(new NeighborTypesMatcher(Tile::Type::Forest,
			{ SAME, ANY, SAME, ANY, ANY, ANY, SAME, ANY })),
        textures::landmarks::forest_t1r1b0l1);
    ts.add(std::shared_ptr<const NeighborTypesMatcher>(new NeighborTypesMatcher(Tile::Type::Forest,
			{ ANY, ANY, SAME, ANY, SAME, ANY, ANY, ANY })),
        textures::landmarks::forest_t0r1b1l0);
    ts.add(std::shared_ptr<const NeighborTypesMatcher>(new NeighborTypesMatcher(Tile::Type::Forest,
			{ SAME, ANY, SAME, ANY, SAME, ANY, ANY, ANY })),
        textures::landmarks::forest_t1r1b1l0);
    ts.add(std::shared_ptr<const NeighborTypesMatcher>(new NeighborTypesMatcher(Tile::Type::Forest,
			{ ANY, ANY, SAME, ANY, SAME, ANY, SAME, ANY })),
        textures::landmarks::forest_t0r1b1l1);
    ts.add(std::shared_ptr<const NeighborTypesMatcher>(new NeighborTypesMatcher(Tile::Type::Forest,
			{ SAME, ANY, SAME, ANY, SAME, ANY, SAME, ANY })),
        textures::landmarks::forest_t1r1b1l1);

    ts.add(std::shared_ptr<const NeighborTypesMatcher>(new NeighborTypesMatcher(Tile::Type::Hills,
			{ ANY, ANY, ANY, ANY, ANY, ANY, ANY, ANY })),
        textures::landmarks::hills_t0r0b0l0);
    ts.add(std::shared_ptr<const NeighborTypesMatcher>(new NeighborTypesMatcher(Tile::Type::Hills,
			{ SAME, ANY, ANY, ANY, ANY, ANY, ANY, ANY })),
        textures::landmarks::hills_t1r0b0l0);
    ts.add(std::shared_ptr<const NeighborTypesMatcher>(new NeighborTypesMatcher(Tile::Type::Hills,
			{ ANY, ANY, ANY, ANY, ANY, ANY, SAME, ANY })),
        textures::landmarks::hills_t0r0b0l1);
    ts.add(std::shared_ptr<const NeighborTypesMatcher>(new NeighborTypesMatcher(Tile::Type::Hills,
			{ SAME, ANY, ANY, ANY, ANY, ANY, SAME, ANY })),
        textures::landmarks::hills_t1r0b0l1);
    ts.add(std::shared_ptr<const NeighborTypesMatcher>(new NeighborTypesMatcher(Tile::Type::Hills,
			{ ANY, ANY, ANY, ANY, SAME, ANY, ANY, ANY })),
        textures::landmarks::hills_t0r0b1l0);
    ts.add(std::shared_ptr<const NeighborTypesMatcher>(new NeighborTypesMatcher(Tile::Type::Hills,
			{ SAME, ANY, ANY, ANY, SAME, ANY, ANY, ANY })),
        textures::landmarks::mountains_t1r0b1l0);
    ts.add(std::shared_ptr<const NeighborTypesMatcher>(new NeighborTypesMatcher(Tile::Type::Hills,
			{ ANY, ANY, ANY, ANY, SAME, ANY, SAME, ANY })),
        textures::landmarks::hills_t0r0b1l1);
    ts.add(std::shared_ptr<const NeighborTypesMatcher>(new NeighborTypesMatcher(Tile::Type::Hills,
			{ SAME, ANY, ANY, ANY, SAME, ANY, SAME, ANY })),
        textures::landmarks::hills_t1r0b1l1);
    ts.add(std::shared_ptr<const NeighborTypesMatcher>(new NeighborTypesMatcher(Tile::Type::Hills,
			{ ANY, ANY, SAME, ANY, ANY, ANY, ANY, ANY })),
        textures::landmarks::hills_t0r1b0l0);
    ts.add(std::shared_ptr<const NeighborTypesMatcher>(new NeighborTypesMatcher(Tile::Type::Hills,
			{ SAME, ANY, SAME, ANY, ANY, ANY, ANY, ANY })),
        textures::landmarks::hills_t1r1b0l0);
    ts.add(std::shared_ptr<const NeighborTypesMatcher>(new NeighborTypesMatcher(Tile::Type::Hills,
			{ ANY, ANY, SAME, ANY, ANY, ANY, SAME, ANY })),
        textures::landmarks::hills_t0r1b0l1);
    ts.add(std::shared_ptr<const NeighborTypesMatcher>(new NeighborTypesMatcher(Tile::Type::Hills,
			{ SAME, ANY, SAME, ANY, ANY, ANY, SAME, ANY })),
        textures::landmarks::hills_t1r1b0l1);
    ts.add(std::shared_ptr<const NeighborTypesMatcher>(new NeighborTypesMatcher(Tile::Type::Hills,
			{ ANY, ANY, SAME, ANY, SAME, ANY, ANY, ANY })),
        textures::landmarks::hills_t0r1b1l0);
    ts.add(std::shared_ptr<const NeighborTypesMatcher>(new NeighborTypesMatcher(Tile::Type::Hills,
			{ SAME, ANY, SAME, ANY, SAME, ANY, ANY, ANY })),
        textures::landmarks::hills_t1r1b1l0);
    ts.add(std::shared_ptr<const NeighborTypesMatcher>(new NeighborTypesMatcher(Tile::Type::Hills,
			{ ANY, ANY, SAME, ANY, SAME, ANY, SAME, ANY })),
        textures::landmarks::hills_t0r1b1l1);
    ts.add(std::shared_ptr<const NeighborTypesMatcher>(new NeighborTypesMatcher(Tile::Type::Hills,
			{ SAME, ANY, SAME, ANY, SAME, ANY, SAME, ANY })),
        textures::landmarks::hills_t1r1b1l1);

    ts.add(std::shared_ptr<const NeighborTypesMatcher>(new NeighborTypesMatcher(Tile::Type::Mountains,
			{ ANY, ANY, ANY, ANY, ANY, ANY, ANY, ANY })),
        textures::landmarks::mountains_t0r0b0l0);
    ts.add(std::shared_ptr<const NeighborTypesMatcher>(new NeighborTypesMatcher(Tile::Type::Mountains,
			{ SAME, ANY, ANY, ANY, ANY, ANY, ANY, ANY })),
        textures::landmarks::mountains_t1r0b0l0);
    ts.add(std::shared_ptr<const NeighborTypesMatcher>(new NeighborTypesMatcher(Tile::Type::Mountains,
			{ ANY, ANY, ANY, ANY, ANY, ANY, SAME, ANY })),
        textures::landmarks::mountains_t0r0b0l1);
    ts.add(std::shared_ptr<const NeighborTypesMatcher>(new NeighborTypesMatcher(Tile::Type::Mountains,
			{ SAME, ANY, ANY, ANY, ANY, ANY, SAME, ANY })),
        textures::landmarks::mountains_t1r0b0l1);
    ts.add(std::shared_ptr<const NeighborTypesMatcher>(new NeighborTypesMatcher(Tile::Type::Mountains,
			{ ANY, ANY, ANY, ANY, SAME, ANY, ANY, ANY })),
        textures::landmarks::mountains_t0r0b1l0);
    ts.add(std::shared_ptr<const NeighborTypesMatcher>(new NeighborTypesMatcher(Tile::Type::Mountains,
			{ SAME, ANY, ANY, ANY, SAME, ANY, ANY, ANY })),
        textures::landmarks::mountains_t1r0b1l0);
    ts.add(std::shared_ptr<const NeighborTypesMatcher>(new NeighborTypesMatcher(Tile::Type::Mountains,
			{ ANY, ANY, ANY, ANY, SAME, ANY, SAME, ANY })),
        textures::landmarks::mountains_t0r0b1l1);
    ts.add(std::shared_ptr<const NeighborTypesMatcher>(new NeighborTypesMatcher(Tile::Type::Mountains,
			{ SAME, ANY, ANY, ANY, SAME, ANY, SAME, ANY })),
        textures::landmarks::mountains_t1r0b1l1);
    ts.add(std::shared_ptr<const NeighborTypesMatcher>(new NeighborTypesMatcher(Tile::Type::Mountains,
			{ ANY, ANY, SAME, ANY, ANY, ANY, ANY, ANY })),
        textures::landmarks::mountains_t0r1b0l0);
    ts.add(std::shared_ptr<const NeighborTypesMatcher>(new NeighborTypesMatcher(Tile::Type::Mountains,
			{ SAME, ANY, SAME, ANY, ANY, ANY, ANY, ANY })),
        textures::landmarks::mountains_t1r1b0l0);
    ts.add(std::shared_ptr<const NeighborTypesMatcher>(new NeighborTypesMatcher(Tile::Type::Mountains,
			{ ANY, ANY, SAME, ANY, ANY, ANY, SAME, ANY })),
        textures::landmarks::mountains_t0r1b0l1);
    ts.add(std::shared_ptr<const NeighborTypesMatcher>(new NeighborTypesMatcher(Tile::Type::Mountains,
			{ SAME, ANY, SAME, ANY, ANY, ANY, SAME, ANY })),
        textures::landmarks::mountains_t1r1b0l1);
    ts.add(std::shared_ptr<const NeighborTypesMatcher>(new NeighborTypesMatcher(Tile::Type::Mountains,
			{ ANY, ANY, SAME, ANY, SAME, ANY, ANY, ANY })),
        textures::landmarks::mountains_t0r1b1l0);
    ts.add(std::shared_ptr<const NeighborTypesMatcher>(new NeighborTypesMatcher(Tile::Type::Mountains,
			{ SAME, ANY, SAME, ANY, SAME, ANY, ANY, ANY })),
        textures::landmarks::mountains_t1r1b1l0);
    ts.add(std::shared_ptr<const NeighborTypesMatcher>(new NeighborTypesMatcher(Tile::Type::Mountains,
			{ ANY, ANY, SAME, ANY, SAME, ANY, SAME, ANY })),
        textures::landmarks::mountains_t0r1b1l1);
    ts.add(std::shared_ptr<const NeighborTypesMatcher>(new NeighborTypesMatcher(Tile::Type::Mountains,
			{ SAME, ANY, SAME, ANY, SAME, ANY, SAME, ANY })),
        textures::landmarks::mountains_t1r1b1l1);

    return ts;
}
