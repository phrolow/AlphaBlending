#ifndef ALPHA_BLENDING_HPP
#define ALPHA_BLENDING_HPP

#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Image.hpp>
#include <immintrin.h>
#include <memory.h>

const char * const backPath = "Pictures/Table.bmp";
const char * const frontPath  = "Pictures/AskhatCat.bmp";
const char * const resultPath = "Pictures/Result.bmp";

const unsigned int X_SHIFT = 300;
const unsigned int Y_SHIFT = 200;

void alphaBlendImages(const sf::Image back, const sf::Image front, sf::Uint8 *result, sf::Vector2u shift);

void alphaBlendArrays(const sf::Uint8 *back,   sf::Vector2u back_size,
                            const sf::Uint8 *front,  sf::Vector2u front_size,
                                  sf::Uint8 *result, sf::Vector2u shift);

#endif