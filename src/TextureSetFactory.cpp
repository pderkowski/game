/* Copyright 2014 <Piotr Derkowski> */

#include <vector>
#include "SFML/Graphics.hpp"
#include "TextureSet.hpp"
#include "Tile.hpp"
#include "TextureSetFactory.hpp"
#include "Resources.hpp"
#include "TextureMatcher.hpp"
#include "textures/blends.hpp"
#include "textures/terrains.hpp"
#include "textures/landmarks.hpp"

#define ANY TextureMatcher::TileMatcher::Any
#define SAME TextureMatcher::TileMatcher::Same
#define DIFF TextureMatcher::TileMatcher::Different

TextureSet TextureSetFactory::getBaseTextureSet() {
    TextureSet ts(Resources::loadTexture("textures/terrains.png"));

    ts.add(Tile::Type::Water, makeWaterBaseMatcher());
    ts.add(Tile::Type::Hills, makeHillsBaseMatcher());
    ts.add(Tile::Type::Mountains, makeMountainsBaseMatcher());
    ts.add(Tile::Type::Grassland, makeGrasslandBaseMatcher());
    ts.add(Tile::Type::Plains, makePlainsBaseMatcher());
    ts.add(Tile::Type::River, makeRiverBaseMatcher());
    ts.add(Tile::Type::Forest, makeForestBaseMatcher());
    ts.add(Tile::Type::Desert, makeDesertBaseMatcher());

    return ts;
}

TextureSet TextureSetFactory::getBlendTextureSet() {
    TextureSet ts(Resources::loadTexture("textures/blends.png"));

    ts.add(Tile::Type::Water, makeWaterBlendMatcher());
    ts.add(Tile::Type::Plains, makePlainsBlendMatcher());
    ts.add(Tile::Type::River, makeRiverBlendMatcher());
    ts.add(Tile::Type::Forest, makeForestBlendMatcher());
    ts.add(Tile::Type::Grassland, makeGrasslandBlendMatcher());
    ts.add(Tile::Type::Desert, makeDesertBlendMatcher());
    ts.add(Tile::Type::Hills, makeHillsBlendMatcher());
    ts.add(Tile::Type::Mountains, makeMountainsBlendMatcher());

    return ts;
}

TextureSet TextureSetFactory::getOverlayTextureSet() {
    TextureSet ts(Resources::loadTexture("textures/landmarks.png"));

    ts.add(Tile::Type::Forest, makeForestOverlayMatcher());
    ts.add(Tile::Type::Hills, makeHillsOverlayMatcher());
    ts.add(Tile::Type::Mountains, makeMountainsOverlayMatcher());
    ts.add(Tile::Type::River, makeRiverOverlayMatcher());

    return ts;
}

TextureMatcher TextureSetFactory::makeHillsBaseMatcher() {
    TextureMatcher tm;

    tm.addMatching(TextureMatcher::Matching({ ANY, ANY, ANY, ANY, ANY, ANY, ANY, ANY }),
        textures::terrains::hills);

    return tm;
}

TextureMatcher TextureSetFactory::makeMountainsBaseMatcher() {
    TextureMatcher tm;

    tm.addMatching(TextureMatcher::Matching({ ANY, ANY, ANY, ANY, ANY, ANY, ANY, ANY }),
        textures::terrains::mountains);

    return tm;
}

TextureMatcher TextureSetFactory::makeGrasslandBaseMatcher() {
    TextureMatcher tm;

    tm.addMatching(TextureMatcher::Matching({ ANY, ANY, ANY, ANY, ANY, ANY, ANY, ANY }),
        textures::terrains::grassland);

    return tm;
}

TextureMatcher TextureSetFactory::makeRiverBaseMatcher() {
    TextureMatcher tm;

    tm.addMatching(TextureMatcher::Matching({ ANY, ANY, ANY, ANY, ANY, ANY, ANY, ANY }),
        textures::terrains::river);

    return tm;
}

TextureMatcher TextureSetFactory::makePlainsBaseMatcher() {
    TextureMatcher tm;

    tm.addMatching(TextureMatcher::Matching({ ANY, ANY, ANY, ANY, ANY, ANY, ANY, ANY }),
        textures::terrains::plains);

    return tm;
}

TextureMatcher TextureSetFactory::makeForestBaseMatcher() {
    TextureMatcher tm;

    tm.addMatching(TextureMatcher::Matching({ ANY, ANY, ANY, ANY, ANY, ANY, ANY, ANY }),
        textures::terrains::forest);

    return tm;
}

TextureMatcher TextureSetFactory::makeDesertBaseMatcher() {
    TextureMatcher tm;

    tm.addMatching(TextureMatcher::Matching({ ANY, ANY, ANY, ANY, ANY, ANY, ANY, ANY }),
        textures::terrains::desert);

    return tm;
}

TextureMatcher TextureSetFactory::makeWaterBlendMatcher() {
    TextureMatcher tm({ Tile::Type::Water, Tile::Type::Empty });

    tm.addMatching(TextureMatcher::Matching({ DIFF, ANY, ANY, ANY, ANY, ANY, ANY, ANY }),
        textures::blends::water_T);
    tm.addMatching(TextureMatcher::Matching({ ANY, ANY, DIFF, ANY, ANY, ANY, ANY, ANY }),
        textures::blends::water_R);
    tm.addMatching(TextureMatcher::Matching({ ANY, ANY, ANY, ANY, DIFF, ANY, ANY, ANY }),
        textures::blends::water_B);
    tm.addMatching(TextureMatcher::Matching({ ANY, ANY, ANY, ANY, ANY, ANY, DIFF, ANY }),
        textures::blends::water_L);

    return tm;
}

TextureMatcher TextureSetFactory::makeGrasslandBlendMatcher() {
    TextureMatcher tm({ Tile::Type::Grassland, Tile::Type::Empty });

    tm.addMatching(TextureMatcher::Matching({ DIFF, ANY, ANY, ANY, ANY, ANY, ANY, ANY }),
        textures::blends::grassland_T);
    tm.addMatching(TextureMatcher::Matching({ ANY, ANY, DIFF, ANY, ANY, ANY, ANY, ANY }),
        textures::blends::grassland_R);
    tm.addMatching(TextureMatcher::Matching({ ANY, ANY, ANY, ANY, DIFF, ANY, ANY, ANY }),
        textures::blends::grassland_B);
    tm.addMatching(TextureMatcher::Matching({ ANY, ANY, ANY, ANY, ANY, ANY, DIFF, ANY }),
        textures::blends::grassland_L);

    return tm;
}

TextureMatcher TextureSetFactory::makeRiverBlendMatcher() {
    TextureMatcher tm({ Tile::Type::River, Tile::Type::Empty });

    tm.addMatching(TextureMatcher::Matching({ DIFF, ANY, ANY, ANY, ANY, ANY, ANY, ANY }),
        textures::blends::river_T);
    tm.addMatching(TextureMatcher::Matching({ ANY, ANY, DIFF, ANY, ANY, ANY, ANY, ANY }),
        textures::blends::river_R);
    tm.addMatching(TextureMatcher::Matching({ ANY, ANY, ANY, ANY, DIFF, ANY, ANY, ANY }),
        textures::blends::river_B);
    tm.addMatching(TextureMatcher::Matching({ ANY, ANY, ANY, ANY, ANY, ANY, DIFF, ANY }),
        textures::blends::river_L);

    return tm;
}

TextureMatcher TextureSetFactory::makePlainsBlendMatcher() {
    TextureMatcher tm({ Tile::Type::Plains, Tile::Type::Empty });

    tm.addMatching(TextureMatcher::Matching({ DIFF, ANY, ANY, ANY, ANY, ANY, ANY, ANY }),
        textures::blends::plains_T);
    tm.addMatching(TextureMatcher::Matching({ ANY, ANY, DIFF, ANY, ANY, ANY, ANY, ANY }),
        textures::blends::plains_R);
    tm.addMatching(TextureMatcher::Matching({ ANY, ANY, ANY, ANY, DIFF, ANY, ANY, ANY }),
        textures::blends::plains_B);
    tm.addMatching(TextureMatcher::Matching({ ANY, ANY, ANY, ANY, ANY, ANY, DIFF, ANY }),
        textures::blends::plains_L);

    return tm;
}

TextureMatcher TextureSetFactory::makeForestBlendMatcher() {
    TextureMatcher tm({ Tile::Type::Forest, Tile::Type::Empty });

    tm.addMatching(TextureMatcher::Matching({ DIFF, ANY, ANY, ANY, ANY, ANY, ANY, ANY }),
        textures::blends::forest_T);
    tm.addMatching(TextureMatcher::Matching({ ANY, ANY, DIFF, ANY, ANY, ANY, ANY, ANY }),
        textures::blends::forest_R);
    tm.addMatching(TextureMatcher::Matching({ ANY, ANY, ANY, ANY, DIFF, ANY, ANY, ANY }),
        textures::blends::forest_B);
    tm.addMatching(TextureMatcher::Matching({ ANY, ANY, ANY, ANY, ANY, ANY, DIFF, ANY }),
        textures::blends::forest_L);

    return tm;
}

TextureMatcher TextureSetFactory::makeDesertBlendMatcher() {
    TextureMatcher tm({ Tile::Type::Desert, Tile::Type::Empty });

    tm.addMatching(TextureMatcher::Matching({ DIFF, ANY, ANY, ANY, ANY, ANY, ANY, ANY }),
        textures::blends::desert_T);
    tm.addMatching(TextureMatcher::Matching({ ANY, ANY, DIFF, ANY, ANY, ANY, ANY, ANY }),
        textures::blends::desert_R);
    tm.addMatching(TextureMatcher::Matching({ ANY, ANY, ANY, ANY, DIFF, ANY, ANY, ANY }),
        textures::blends::desert_B);
    tm.addMatching(TextureMatcher::Matching({ ANY, ANY, ANY, ANY, ANY, ANY, DIFF, ANY }),
        textures::blends::desert_L);

    return tm;
}

TextureMatcher TextureSetFactory::makeHillsBlendMatcher() {
    TextureMatcher tm({ Tile::Type::Hills, Tile::Type::Empty });

    tm.addMatching(TextureMatcher::Matching({ DIFF, ANY, ANY, ANY, ANY, ANY, ANY, ANY }),
        textures::blends::hills_T);
    tm.addMatching(TextureMatcher::Matching({ ANY, ANY, DIFF, ANY, ANY, ANY, ANY, ANY }),
        textures::blends::hills_R);
    tm.addMatching(TextureMatcher::Matching({ ANY, ANY, ANY, ANY, DIFF, ANY, ANY, ANY }),
        textures::blends::hills_B);
    tm.addMatching(TextureMatcher::Matching({ ANY, ANY, ANY, ANY, ANY, ANY, DIFF, ANY }),
        textures::blends::hills_L);

    return tm;
}

TextureMatcher TextureSetFactory::makeMountainsBlendMatcher() {
    TextureMatcher tm({ Tile::Type::Mountains, Tile::Type::Empty });

    tm.addMatching(TextureMatcher::Matching({ DIFF, ANY, ANY, ANY, ANY, ANY, ANY, ANY }),
        textures::blends::mountains_T);
    tm.addMatching(TextureMatcher::Matching({ ANY, ANY, DIFF, ANY, ANY, ANY, ANY, ANY }),
        textures::blends::mountains_R);
    tm.addMatching(TextureMatcher::Matching({ ANY, ANY, ANY, ANY, DIFF, ANY, ANY, ANY }),
        textures::blends::mountains_B);
    tm.addMatching(TextureMatcher::Matching({ ANY, ANY, ANY, ANY, ANY, ANY, DIFF, ANY }),
        textures::blends::mountains_L);

    return tm;
}

TextureMatcher TextureSetFactory::makeWaterBaseMatcher() {
    TextureMatcher tm({ Tile::Type::Water, Tile::Type::Empty });

    tm.addMatching(TextureMatcher::Matching({ SAME, SAME, SAME, ANY, ANY, ANY, ANY, ANY }),
        textures::landmarks::water_t000);
    tm.addMatching(TextureMatcher::Matching({ ANY, ANY, ANY, ANY, SAME, SAME, SAME, ANY }),
        textures::landmarks::water_b000);
    tm.addMatching(TextureMatcher::Matching({ SAME, ANY, ANY, ANY, ANY, ANY, SAME, SAME }),
        textures::landmarks::water_l000);
    tm.addMatching(TextureMatcher::Matching({ ANY, ANY, SAME, SAME, SAME, ANY, ANY, ANY }),
        textures::landmarks::water_r000);

    tm.addMatching(TextureMatcher::Matching({ DIFF, SAME, SAME, ANY, ANY, ANY, ANY, ANY }),
        textures::landmarks::water_t100);
    tm.addMatching(TextureMatcher::Matching({ ANY, ANY, ANY, ANY, DIFF, SAME, SAME, ANY }),
        textures::landmarks::water_b100);
    tm.addMatching(TextureMatcher::Matching({ SAME, ANY, ANY, ANY, ANY, ANY, DIFF, SAME }),
        textures::landmarks::water_l100);
    tm.addMatching(TextureMatcher::Matching({ ANY, ANY, DIFF, SAME, SAME, ANY, ANY, ANY }),
        textures::landmarks::water_r100);

    tm.addMatching(TextureMatcher::Matching({ SAME, DIFF, SAME, ANY, ANY, ANY, ANY, ANY }),
        textures::landmarks::water_t010);
    tm.addMatching(TextureMatcher::Matching({ ANY, ANY, ANY, ANY, SAME, DIFF, SAME, ANY }),
        textures::landmarks::water_b010);
    tm.addMatching(TextureMatcher::Matching({ SAME, ANY, ANY, ANY, ANY, ANY, SAME, DIFF }),
        textures::landmarks::water_l010);
    tm.addMatching(TextureMatcher::Matching({ ANY, ANY, SAME, DIFF, SAME, ANY, ANY, ANY }),
        textures::landmarks::water_r010);

    tm.addMatching(TextureMatcher::Matching({ DIFF, DIFF, SAME, ANY, ANY, ANY, ANY, ANY }),
        textures::landmarks::water_t110);
    tm.addMatching(TextureMatcher::Matching({ ANY, ANY, ANY, ANY, DIFF, DIFF, SAME, ANY }),
        textures::landmarks::water_b110);
    tm.addMatching(TextureMatcher::Matching({ SAME, ANY, ANY, ANY, ANY, ANY, DIFF, DIFF }),
        textures::landmarks::water_l110);
    tm.addMatching(TextureMatcher::Matching({ ANY, ANY, DIFF, DIFF, SAME, ANY, ANY, ANY }),
        textures::landmarks::water_r110);

    tm.addMatching(TextureMatcher::Matching({ SAME, SAME, DIFF, ANY, ANY, ANY, ANY, ANY }),
        textures::landmarks::water_t001);
    tm.addMatching(TextureMatcher::Matching({ ANY, ANY, ANY, ANY, SAME, SAME, DIFF, ANY }),
        textures::landmarks::water_b001);
    tm.addMatching(TextureMatcher::Matching({ DIFF, ANY, ANY, ANY, ANY, ANY, SAME, SAME }),
        textures::landmarks::water_l001);
    tm.addMatching(TextureMatcher::Matching({ ANY, ANY, SAME, SAME, DIFF, ANY, ANY, ANY }),
        textures::landmarks::water_r001);

    tm.addMatching(TextureMatcher::Matching({ DIFF, SAME, DIFF, ANY, ANY, ANY, ANY, ANY }),
        textures::landmarks::water_t101);
    tm.addMatching(TextureMatcher::Matching({ ANY, ANY, ANY, ANY, DIFF, SAME, DIFF, ANY }),
        textures::landmarks::water_b101);
    tm.addMatching(TextureMatcher::Matching({ DIFF, ANY, ANY, ANY, ANY, ANY, DIFF, SAME }),
        textures::landmarks::water_l101);
    tm.addMatching(TextureMatcher::Matching({ ANY, ANY, DIFF, SAME, DIFF, ANY, ANY, ANY }),
        textures::landmarks::water_r101);

    tm.addMatching(TextureMatcher::Matching({ SAME, DIFF, DIFF, ANY, ANY, ANY, ANY, ANY }),
        textures::landmarks::water_t011);
    tm.addMatching(TextureMatcher::Matching({ ANY, ANY, ANY, ANY, SAME, DIFF, DIFF, ANY }),
        textures::landmarks::water_b011);
    tm.addMatching(TextureMatcher::Matching({ DIFF, ANY, ANY, ANY, ANY, ANY, SAME, DIFF }),
        textures::landmarks::water_l011);
    tm.addMatching(TextureMatcher::Matching({ ANY, ANY, SAME, DIFF, DIFF, ANY, ANY, ANY }),
        textures::landmarks::water_r011);

    tm.addMatching(TextureMatcher::Matching({ DIFF, DIFF, DIFF, ANY, ANY, ANY, ANY, ANY }),
        textures::landmarks::water_t111);
    tm.addMatching(TextureMatcher::Matching({ ANY, ANY, ANY, ANY, DIFF, DIFF, DIFF, ANY }),
        textures::landmarks::water_b111);
    tm.addMatching(TextureMatcher::Matching({ DIFF, ANY, ANY, ANY, ANY, ANY, DIFF, DIFF }),
        textures::landmarks::water_l111);
    tm.addMatching(TextureMatcher::Matching({ ANY, ANY, DIFF, DIFF, DIFF, ANY, ANY, ANY }),
        textures::landmarks::water_r111);

    return tm;
}

TextureMatcher TextureSetFactory::makeRiverOverlayMatcher() {
    TextureMatcher tm({ Tile::Type::River, Tile::Type::Water, Tile::Type::Empty });

    tm.addMatching(TextureMatcher::Matching({ DIFF, ANY, DIFF, ANY, DIFF, ANY, DIFF, ANY }),
        textures::landmarks::river_t0r0b0l0);
    tm.addMatching(TextureMatcher::Matching({ SAME, ANY, DIFF, ANY, DIFF, ANY, DIFF, ANY }),
        textures::landmarks::river_t1r0b0l0);
    tm.addMatching(TextureMatcher::Matching({ DIFF, ANY, DIFF, ANY, DIFF, ANY, SAME, ANY }),
        textures::landmarks::river_t0r0b0l1);
    tm.addMatching(TextureMatcher::Matching({ SAME, ANY, DIFF, ANY, DIFF, ANY, SAME, ANY }),
        textures::landmarks::river_t1r0b0l1);
    tm.addMatching(TextureMatcher::Matching({ DIFF, ANY, DIFF, ANY, SAME, ANY, DIFF, ANY }),
        textures::landmarks::river_t0r0b1l0);
    tm.addMatching(TextureMatcher::Matching({ SAME, ANY, DIFF, ANY, SAME, ANY, DIFF, ANY }),
        textures::landmarks::river_t1r0b1l0);
    tm.addMatching(TextureMatcher::Matching({ DIFF, ANY, DIFF, ANY, SAME, ANY, SAME, ANY }),
        textures::landmarks::river_t0r0b1l1);
    tm.addMatching(TextureMatcher::Matching({ SAME, ANY, DIFF, ANY, SAME, ANY, SAME, ANY }),
        textures::landmarks::river_t1r0b1l1);
    tm.addMatching(TextureMatcher::Matching({ DIFF, ANY, SAME, ANY, DIFF, ANY, DIFF, ANY }),
        textures::landmarks::river_t0r1b0l0);
    tm.addMatching(TextureMatcher::Matching({ SAME, ANY, SAME, ANY, DIFF, ANY, DIFF, ANY }),
        textures::landmarks::river_t1r1b0l0);
    tm.addMatching(TextureMatcher::Matching({ DIFF, ANY, SAME, ANY, DIFF, ANY, SAME, ANY }),
        textures::landmarks::river_t0r1b0l1);
    tm.addMatching(TextureMatcher::Matching({ SAME, ANY, SAME, ANY, DIFF, ANY, SAME, ANY }),
        textures::landmarks::river_t1r1b0l1);
    tm.addMatching(TextureMatcher::Matching({ DIFF, ANY, SAME, ANY, SAME, ANY, DIFF, ANY }),
        textures::landmarks::river_t0r1b1l0);
    tm.addMatching(TextureMatcher::Matching({ SAME, ANY, SAME, ANY, SAME, ANY, DIFF, ANY }),
        textures::landmarks::river_t1r1b1l0);
    tm.addMatching(TextureMatcher::Matching({ DIFF, ANY, SAME, ANY, SAME, ANY, SAME, ANY }),
        textures::landmarks::river_t0r1b1l1);
    tm.addMatching(TextureMatcher::Matching({ SAME, ANY, SAME, ANY, SAME, ANY, SAME, ANY }),
        textures::landmarks::river_t1r1b1l1);

    return tm;
}

TextureMatcher TextureSetFactory::makeForestOverlayMatcher() {
    TextureMatcher tm({ Tile::Type::Forest, Tile::Type::Empty });

    tm.addMatching(TextureMatcher::Matching({ ANY, ANY, ANY, ANY, ANY, ANY, ANY, ANY }),
        textures::landmarks::forest_t0r0b0l0);
    tm.addMatching(TextureMatcher::Matching({ SAME, ANY, ANY, ANY, ANY, ANY, ANY, ANY }),
        textures::landmarks::forest_t1r0b0l0);
    tm.addMatching(TextureMatcher::Matching({ ANY, ANY, ANY, ANY, ANY, ANY, SAME, ANY }),
        textures::landmarks::forest_t0r0b0l1);
    tm.addMatching(TextureMatcher::Matching({ SAME, ANY, ANY, ANY, ANY, ANY, SAME, ANY }),
        textures::landmarks::forest_t1r0b0l1);
    tm.addMatching(TextureMatcher::Matching({ ANY, ANY, ANY, ANY, SAME, ANY, ANY, ANY }),
        textures::landmarks::forest_t0r0b1l0);
    tm.addMatching(TextureMatcher::Matching({ SAME, ANY, ANY, ANY, SAME, ANY, ANY, ANY }),
        textures::landmarks::forest_t1r0b1l0);
    tm.addMatching(TextureMatcher::Matching({ ANY, ANY, ANY, ANY, SAME, ANY, SAME, ANY }),
        textures::landmarks::forest_t0r0b1l1);
    tm.addMatching(TextureMatcher::Matching({ SAME, ANY, ANY, ANY, SAME, ANY, SAME, ANY }),
        textures::landmarks::forest_t1r0b1l1);
    tm.addMatching(TextureMatcher::Matching({ ANY, ANY, SAME, ANY, ANY, ANY, ANY, ANY }),
        textures::landmarks::forest_t0r1b0l0);
    tm.addMatching(TextureMatcher::Matching({ SAME, ANY, SAME, ANY, ANY, ANY, ANY, ANY }),
        textures::landmarks::forest_t1r1b0l0);
    tm.addMatching(TextureMatcher::Matching({ ANY, ANY, SAME, ANY, ANY, ANY, SAME, ANY }),
        textures::landmarks::forest_t0r1b0l1);
    tm.addMatching(TextureMatcher::Matching({ SAME, ANY, SAME, ANY, ANY, ANY, SAME, ANY }),
        textures::landmarks::forest_t1r1b0l1);
    tm.addMatching(TextureMatcher::Matching({ ANY, ANY, SAME, ANY, SAME, ANY, ANY, ANY }),
        textures::landmarks::forest_t0r1b1l0);
    tm.addMatching(TextureMatcher::Matching({ SAME, ANY, SAME, ANY, SAME, ANY, ANY, ANY }),
        textures::landmarks::forest_t1r1b1l0);
    tm.addMatching(TextureMatcher::Matching({ ANY, ANY, SAME, ANY, SAME, ANY, SAME, ANY }),
        textures::landmarks::forest_t0r1b1l1);
    tm.addMatching(TextureMatcher::Matching({ SAME, ANY, SAME, ANY, SAME, ANY, SAME, ANY }),
        textures::landmarks::forest_t1r1b1l1);

    return tm;
}

TextureMatcher TextureSetFactory::makeHillsOverlayMatcher() {
    TextureMatcher tm({ Tile::Type::Hills, Tile::Type::Empty });

    tm.addMatching(TextureMatcher::Matching({ ANY, ANY, ANY, ANY, ANY, ANY, ANY, ANY }),
        textures::landmarks::hills_t0r0b0l0);
    tm.addMatching(TextureMatcher::Matching({ SAME, ANY, ANY, ANY, ANY, ANY, ANY, ANY }),
        textures::landmarks::hills_t1r0b0l0);
    tm.addMatching(TextureMatcher::Matching({ ANY, ANY, ANY, ANY, ANY, ANY, SAME, ANY }),
        textures::landmarks::hills_t0r0b0l1);
    tm.addMatching(TextureMatcher::Matching({ SAME, ANY, ANY, ANY, ANY, ANY, SAME, ANY }),
        textures::landmarks::hills_t1r0b0l1);
    tm.addMatching(TextureMatcher::Matching({ ANY, ANY, ANY, ANY, SAME, ANY, ANY, ANY }),
        textures::landmarks::hills_t0r0b1l0);
    tm.addMatching(TextureMatcher::Matching({ SAME, ANY, ANY, ANY, SAME, ANY, ANY, ANY }),
        textures::landmarks::mountains_t1r0b1l0);
    tm.addMatching(TextureMatcher::Matching({ ANY, ANY, ANY, ANY, SAME, ANY, SAME, ANY }),
        textures::landmarks::hills_t0r0b1l1);
    tm.addMatching(TextureMatcher::Matching({ SAME, ANY, ANY, ANY, SAME, ANY, SAME, ANY }),
        textures::landmarks::hills_t1r0b1l1);
    tm.addMatching(TextureMatcher::Matching({ ANY, ANY, SAME, ANY, ANY, ANY, ANY, ANY }),
        textures::landmarks::hills_t0r1b0l0);
    tm.addMatching(TextureMatcher::Matching({ SAME, ANY, SAME, ANY, ANY, ANY, ANY, ANY }),
        textures::landmarks::hills_t1r1b0l0);
    tm.addMatching(TextureMatcher::Matching({ ANY, ANY, SAME, ANY, ANY, ANY, SAME, ANY }),
        textures::landmarks::hills_t0r1b0l1);
    tm.addMatching(TextureMatcher::Matching({ SAME, ANY, SAME, ANY, ANY, ANY, SAME, ANY }),
        textures::landmarks::hills_t1r1b0l1);
    tm.addMatching(TextureMatcher::Matching({ ANY, ANY, SAME, ANY, SAME, ANY, ANY, ANY }),
        textures::landmarks::hills_t0r1b1l0);
    tm.addMatching(TextureMatcher::Matching({ SAME, ANY, SAME, ANY, SAME, ANY, ANY, ANY }),
        textures::landmarks::hills_t1r1b1l0);
    tm.addMatching(TextureMatcher::Matching({ ANY, ANY, SAME, ANY, SAME, ANY, SAME, ANY }),
        textures::landmarks::hills_t0r1b1l1);
    tm.addMatching(TextureMatcher::Matching({ SAME, ANY, SAME, ANY, SAME, ANY, SAME, ANY }),
        textures::landmarks::hills_t1r1b1l1);

    return tm;
}

TextureMatcher TextureSetFactory::makeMountainsOverlayMatcher() {
    TextureMatcher tm({ Tile::Type::Mountains, Tile::Type::Empty });

    tm.addMatching(TextureMatcher::Matching({ ANY, ANY, ANY, ANY, ANY, ANY, ANY, ANY }),
        textures::landmarks::mountains_t0r0b0l0);
    tm.addMatching(TextureMatcher::Matching({ SAME, ANY, ANY, ANY, ANY, ANY, ANY, ANY }),
        textures::landmarks::mountains_t1r0b0l0);
    tm.addMatching(TextureMatcher::Matching({ ANY, ANY, ANY, ANY, ANY, ANY, SAME, ANY }),
        textures::landmarks::mountains_t0r0b0l1);
    tm.addMatching(TextureMatcher::Matching({ SAME, ANY, ANY, ANY, ANY, ANY, SAME, ANY }),
        textures::landmarks::mountains_t1r0b0l1);
    tm.addMatching(TextureMatcher::Matching({ ANY, ANY, ANY, ANY, SAME, ANY, ANY, ANY }),
        textures::landmarks::mountains_t0r0b1l0);
    tm.addMatching(TextureMatcher::Matching({ SAME, ANY, ANY, ANY, SAME, ANY, ANY, ANY }),
        textures::landmarks::mountains_t1r0b1l0);
    tm.addMatching(TextureMatcher::Matching({ ANY, ANY, ANY, ANY, SAME, ANY, SAME, ANY }),
        textures::landmarks::mountains_t0r0b1l1);
    tm.addMatching(TextureMatcher::Matching({ SAME, ANY, ANY, ANY, SAME, ANY, SAME, ANY }),
        textures::landmarks::mountains_t1r0b1l1);
    tm.addMatching(TextureMatcher::Matching({ ANY, ANY, SAME, ANY, ANY, ANY, ANY, ANY }),
        textures::landmarks::mountains_t0r1b0l0);
    tm.addMatching(TextureMatcher::Matching({ SAME, ANY, SAME, ANY, ANY, ANY, ANY, ANY }),
        textures::landmarks::mountains_t1r1b0l0);
    tm.addMatching(TextureMatcher::Matching({ ANY, ANY, SAME, ANY, ANY, ANY, SAME, ANY }),
        textures::landmarks::mountains_t0r1b0l1);
    tm.addMatching(TextureMatcher::Matching({ SAME, ANY, SAME, ANY, ANY, ANY, SAME, ANY }),
        textures::landmarks::mountains_t1r1b0l1);
    tm.addMatching(TextureMatcher::Matching({ ANY, ANY, SAME, ANY, SAME, ANY, ANY, ANY }),
        textures::landmarks::mountains_t0r1b1l0);
    tm.addMatching(TextureMatcher::Matching({ SAME, ANY, SAME, ANY, SAME, ANY, ANY, ANY }),
        textures::landmarks::mountains_t1r1b1l0);
    tm.addMatching(TextureMatcher::Matching({ ANY, ANY, SAME, ANY, SAME, ANY, SAME, ANY }),
        textures::landmarks::mountains_t0r1b1l1);
    tm.addMatching(TextureMatcher::Matching({ SAME, ANY, SAME, ANY, SAME, ANY, SAME, ANY }),
        textures::landmarks::mountains_t1r1b1l1);

    return tm;
}
