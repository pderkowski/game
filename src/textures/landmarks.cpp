/* Copyright 2014 <Piotr Derkowski> */

#include "landmarks.hpp"
#include "TextureUtils.hpp"

const sf::VertexArray textures::landmarks::water_t000 = makeQuad(48, 24, sf::Vector2f(1, 645), sf::Vector2f(25, 0));
const sf::VertexArray textures::landmarks::water_b000 = makeQuad(48, 24, sf::Vector2f(1, 670), sf::Vector2f(25, 24));
const sf::VertexArray textures::landmarks::water_l000 = makeQuad(48, 24, sf::Vector2f(1, 695), sf::Vector2f(1, 12));
const sf::VertexArray textures::landmarks::water_r000 = makeQuad(48, 24, sf::Vector2f(50, 695), sf::Vector2f(49, 12));

const sf::VertexArray textures::landmarks::water_t100 = makeQuad(48, 24, sf::Vector2f(99, 645), sf::Vector2f(25, 0));
const sf::VertexArray textures::landmarks::water_b100 = makeQuad(48, 24, sf::Vector2f(99, 670), sf::Vector2f(25, 24));
const sf::VertexArray textures::landmarks::water_l100 = makeQuad(48, 24, sf::Vector2f(99, 695), sf::Vector2f(1, 12));
const sf::VertexArray textures::landmarks::water_r100 = makeQuad(48, 24, sf::Vector2f(148, 695), sf::Vector2f(49, 12));

const sf::VertexArray textures::landmarks::water_t010 = makeQuad(48, 24, sf::Vector2f(197, 645), sf::Vector2f(25, 0));
const sf::VertexArray textures::landmarks::water_b010 = makeQuad(48, 24, sf::Vector2f(197, 670), sf::Vector2f(25, 24));
const sf::VertexArray textures::landmarks::water_l010 = makeQuad(48, 24, sf::Vector2f(197, 695), sf::Vector2f(1, 12));
const sf::VertexArray textures::landmarks::water_r010 = makeQuad(48, 24, sf::Vector2f(246, 695), sf::Vector2f(49, 12));

const sf::VertexArray textures::landmarks::water_t110 = makeQuad(48, 24, sf::Vector2f(295, 645), sf::Vector2f(25, 0));
const sf::VertexArray textures::landmarks::water_b110 = makeQuad(48, 24, sf::Vector2f(295, 670), sf::Vector2f(25, 24));
const sf::VertexArray textures::landmarks::water_l110 = makeQuad(48, 24, sf::Vector2f(295, 695), sf::Vector2f(1, 12));
const sf::VertexArray textures::landmarks::water_r110 = makeQuad(48, 24, sf::Vector2f(344, 695), sf::Vector2f(49, 12));

const sf::VertexArray textures::landmarks::water_t001 = makeQuad(48, 24, sf::Vector2f(393, 645), sf::Vector2f(25, 0));
const sf::VertexArray textures::landmarks::water_b001 = makeQuad(48, 24, sf::Vector2f(393, 670), sf::Vector2f(25, 24));
const sf::VertexArray textures::landmarks::water_l001 = makeQuad(48, 24, sf::Vector2f(393, 695), sf::Vector2f(1, 12));
const sf::VertexArray textures::landmarks::water_r001 = makeQuad(48, 24, sf::Vector2f(442, 695), sf::Vector2f(49, 12));

const sf::VertexArray textures::landmarks::water_t101 = makeQuad(48, 24, sf::Vector2f(491, 645), sf::Vector2f(25, 0));
const sf::VertexArray textures::landmarks::water_b101 = makeQuad(48, 24, sf::Vector2f(491, 670), sf::Vector2f(25, 24));
const sf::VertexArray textures::landmarks::water_l101 = makeQuad(48, 24, sf::Vector2f(491, 695), sf::Vector2f(1, 12));
const sf::VertexArray textures::landmarks::water_r101 = makeQuad(48, 24, sf::Vector2f(540, 695), sf::Vector2f(49, 12));

const sf::VertexArray textures::landmarks::water_t011 = makeQuad(48, 24, sf::Vector2f(589, 645), sf::Vector2f(25, 0));
const sf::VertexArray textures::landmarks::water_b011 = makeQuad(48, 24, sf::Vector2f(589, 670), sf::Vector2f(25, 24));
const sf::VertexArray textures::landmarks::water_l011 = makeQuad(48, 24, sf::Vector2f(589, 695), sf::Vector2f(1, 12));
const sf::VertexArray textures::landmarks::water_r011 = makeQuad(48, 24, sf::Vector2f(638, 695), sf::Vector2f(49, 12));

const sf::VertexArray textures::landmarks::water_t111 = makeQuad(48, 24, sf::Vector2f(687, 645), sf::Vector2f(25, 0));
const sf::VertexArray textures::landmarks::water_b111 = makeQuad(48, 24, sf::Vector2f(687, 670), sf::Vector2f(25, 24));
const sf::VertexArray textures::landmarks::water_l111 = makeQuad(48, 24, sf::Vector2f(687, 695), sf::Vector2f(1, 12));
const sf::VertexArray textures::landmarks::water_r111 = makeQuad(48, 24, sf::Vector2f(736, 695), sf::Vector2f(49, 12));

const sf::VertexArray textures::landmarks::river_t0r0b0l0 = makeQuad(96, 48, sf::Vector2f(1, 99));
const sf::VertexArray textures::landmarks::river_t1r0b0l0 = makeQuad(96, 48, sf::Vector2f(98, 99));
const sf::VertexArray textures::landmarks::river_t0r0b0l1 = makeQuad(96, 48, sf::Vector2f(195, 99));
const sf::VertexArray textures::landmarks::river_t1r0b0l1 = makeQuad(96, 48, sf::Vector2f(292, 99));
const sf::VertexArray textures::landmarks::river_t0r0b1l0 = makeQuad(96, 48, sf::Vector2f(389, 99));
const sf::VertexArray textures::landmarks::river_t1r0b1l0 = makeQuad(96, 48, sf::Vector2f(486, 99));
const sf::VertexArray textures::landmarks::river_t0r0b1l1 = makeQuad(96, 48, sf::Vector2f(583, 99));
const sf::VertexArray textures::landmarks::river_t1r0b1l1 = makeQuad(96, 48, sf::Vector2f(680, 99));
const sf::VertexArray textures::landmarks::river_t0r1b0l0 = makeQuad(96, 48, sf::Vector2f(1, 148));
const sf::VertexArray textures::landmarks::river_t1r1b0l0 = makeQuad(96, 48, sf::Vector2f(98, 148));
const sf::VertexArray textures::landmarks::river_t0r1b0l1 = makeQuad(96, 48, sf::Vector2f(195, 148));
const sf::VertexArray textures::landmarks::river_t1r1b0l1 = makeQuad(96, 48, sf::Vector2f(292, 148));
const sf::VertexArray textures::landmarks::river_t0r1b1l0 = makeQuad(96, 48, sf::Vector2f(389, 148));
const sf::VertexArray textures::landmarks::river_t1r1b1l0 = makeQuad(96, 48, sf::Vector2f(486, 148));
const sf::VertexArray textures::landmarks::river_t0r1b1l1 = makeQuad(96, 48, sf::Vector2f(583, 148));
const sf::VertexArray textures::landmarks::river_t1r1b1l1 = makeQuad(96, 48, sf::Vector2f(680, 148));

const sf::VertexArray textures::landmarks::forest_t0r0b0l0 = makeQuad(96, 48, sf::Vector2f(1, 197));
const sf::VertexArray textures::landmarks::forest_t1r0b0l0 = makeQuad(96, 48, sf::Vector2f(98, 197));
const sf::VertexArray textures::landmarks::forest_t0r0b0l1 = makeQuad(96, 48, sf::Vector2f(195, 197));
const sf::VertexArray textures::landmarks::forest_t1r0b0l1 = makeQuad(96, 48, sf::Vector2f(292, 197));
const sf::VertexArray textures::landmarks::forest_t0r0b1l0 = makeQuad(96, 48, sf::Vector2f(389, 197));
const sf::VertexArray textures::landmarks::forest_t1r0b1l0 = makeQuad(96, 48, sf::Vector2f(486, 197));
const sf::VertexArray textures::landmarks::forest_t0r0b1l1 = makeQuad(96, 48, sf::Vector2f(583, 197));
const sf::VertexArray textures::landmarks::forest_t1r0b1l1 = makeQuad(96, 48, sf::Vector2f(680, 197));
const sf::VertexArray textures::landmarks::forest_t0r1b0l0 = makeQuad(96, 48, sf::Vector2f(1, 246));
const sf::VertexArray textures::landmarks::forest_t1r1b0l0 = makeQuad(96, 48, sf::Vector2f(98, 246));
const sf::VertexArray textures::landmarks::forest_t0r1b0l1 = makeQuad(96, 48, sf::Vector2f(195, 246));
const sf::VertexArray textures::landmarks::forest_t1r1b0l1 = makeQuad(96, 48, sf::Vector2f(292, 246));
const sf::VertexArray textures::landmarks::forest_t0r1b1l0 = makeQuad(96, 48, sf::Vector2f(389, 246));
const sf::VertexArray textures::landmarks::forest_t1r1b1l0 = makeQuad(96, 48, sf::Vector2f(486, 246));
const sf::VertexArray textures::landmarks::forest_t0r1b1l1 = makeQuad(96, 48, sf::Vector2f(583, 246));
const sf::VertexArray textures::landmarks::forest_t1r1b1l1 = makeQuad(96, 48, sf::Vector2f(680, 246));

const sf::VertexArray textures::landmarks::hills_t0r0b0l0 = makeQuad(96, 48, sf::Vector2f(1, 393));
const sf::VertexArray textures::landmarks::hills_t1r0b0l0 = makeQuad(96, 48, sf::Vector2f(98, 393));
const sf::VertexArray textures::landmarks::hills_t0r0b0l1 = makeQuad(96, 48, sf::Vector2f(195, 393));
const sf::VertexArray textures::landmarks::hills_t1r0b0l1 = makeQuad(96, 48, sf::Vector2f(292, 393));
const sf::VertexArray textures::landmarks::hills_t0r0b1l0 = makeQuad(96, 48, sf::Vector2f(389, 393));
const sf::VertexArray textures::landmarks::hills_t1r0b1l0 = makeQuad(96, 48, sf::Vector2f(486, 393));
const sf::VertexArray textures::landmarks::hills_t0r0b1l1 = makeQuad(96, 48, sf::Vector2f(583, 393));
const sf::VertexArray textures::landmarks::hills_t1r0b1l1 = makeQuad(96, 48, sf::Vector2f(680, 393));
const sf::VertexArray textures::landmarks::hills_t0r1b0l0 = makeQuad(96, 48, sf::Vector2f(1, 442));
const sf::VertexArray textures::landmarks::hills_t1r1b0l0 = makeQuad(96, 48, sf::Vector2f(98, 442));
const sf::VertexArray textures::landmarks::hills_t0r1b0l1 = makeQuad(96, 48, sf::Vector2f(195, 442));
const sf::VertexArray textures::landmarks::hills_t1r1b0l1 = makeQuad(96, 48, sf::Vector2f(292, 442));
const sf::VertexArray textures::landmarks::hills_t0r1b1l0 = makeQuad(96, 48, sf::Vector2f(389, 442));
const sf::VertexArray textures::landmarks::hills_t1r1b1l0 = makeQuad(96, 48, sf::Vector2f(486, 442));
const sf::VertexArray textures::landmarks::hills_t0r1b1l1 = makeQuad(96, 48, sf::Vector2f(583, 442));
const sf::VertexArray textures::landmarks::hills_t1r1b1l1 = makeQuad(96, 48, sf::Vector2f(680, 442));

const sf::VertexArray textures::landmarks::mountains_t0r0b0l0 = makeQuad(96, 48, sf::Vector2f(1, 295));
const sf::VertexArray textures::landmarks::mountains_t1r0b0l0 = makeQuad(96, 48, sf::Vector2f(98, 295));
const sf::VertexArray textures::landmarks::mountains_t0r0b0l1 = makeQuad(96, 48, sf::Vector2f(195, 295));
const sf::VertexArray textures::landmarks::mountains_t1r0b0l1 = makeQuad(96, 48, sf::Vector2f(292, 295));
const sf::VertexArray textures::landmarks::mountains_t0r0b1l0 = makeQuad(96, 48, sf::Vector2f(389, 295));
const sf::VertexArray textures::landmarks::mountains_t1r0b1l0 = makeQuad(96, 48, sf::Vector2f(486, 295));
const sf::VertexArray textures::landmarks::mountains_t0r0b1l1 = makeQuad(96, 48, sf::Vector2f(583, 295));
const sf::VertexArray textures::landmarks::mountains_t1r0b1l1 = makeQuad(96, 48, sf::Vector2f(680, 295));
const sf::VertexArray textures::landmarks::mountains_t0r1b0l0 = makeQuad(96, 48, sf::Vector2f(1, 344));
const sf::VertexArray textures::landmarks::mountains_t1r1b0l0 = makeQuad(96, 48, sf::Vector2f(98, 344));
const sf::VertexArray textures::landmarks::mountains_t0r1b0l1 = makeQuad(96, 48, sf::Vector2f(195, 344));
const sf::VertexArray textures::landmarks::mountains_t1r1b0l1 = makeQuad(96, 48, sf::Vector2f(292, 344));
const sf::VertexArray textures::landmarks::mountains_t0r1b1l0 = makeQuad(96, 48, sf::Vector2f(389, 344));
const sf::VertexArray textures::landmarks::mountains_t1r1b1l0 = makeQuad(96, 48, sf::Vector2f(486, 344));
const sf::VertexArray textures::landmarks::mountains_t0r1b1l1 = makeQuad(96, 48, sf::Vector2f(583, 344));
const sf::VertexArray textures::landmarks::mountains_t1r1b1l1 = makeQuad(96, 48, sf::Vector2f(680, 344));
