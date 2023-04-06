#ifndef ALPHA_BLENDING_HPP
#define ALPHA_BLENDING_HPP

#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Image.hpp>
#include <immintrin.h>

const char * const backPath = "Pictures/Table.bmp";
const char * const frontPath  = "Pictures/AskhatCat.bmp";
const char * const resultPath = "Pictures/Result.bmp";

sf::Uint8* alphaBlendImages(const sf::Image back, const sf::Image front);

sf::Uint8* alphaBlendArrays(const sf::Uint8 *back, unsigned int back_width,  unsigned int back_height,
                            const sf::Uint8 *front,  unsigned int front_width, unsigned int front_height);

#endif