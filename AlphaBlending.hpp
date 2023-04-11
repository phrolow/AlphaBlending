#ifndef ALPHA_BLENDING_HPP
#define ALPHA_BLENDING_HPP

#include <immintrin.h>
#include <math.h>
#include <memory.h>

#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Image.hpp>

const char * const back_path   = "Pictures/Table.bmp";
const char * const front_path  = "Pictures/AskhatCat.bmp";
const char * const result_path = "Pictures/Result.bmp";
const char * const font_path   = "impact.ttf";

const unsigned int X_SHIFT = 300;
const unsigned int Y_SHIFT = 201;

const size_t FIRST_FRAMES = 100;
const size_t NUM_FRAMES = 10000;

//void alphaBlendImages(const sf::Image back, const sf::Image front, sf::Uint8 *result, sf::Vector2u shift);

void alphaBlendArrays(const sf::Uint8 *back,   sf::Vector2u back_size,
                      const sf::Uint8 *front,  sf::Vector2u front_size,
                            sf::Uint8 *result, sf::Vector2u shift);

#endif