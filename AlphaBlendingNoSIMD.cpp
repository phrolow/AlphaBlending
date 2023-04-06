#include "AlphaBlending.hpp"

sf::Uint8* alphaBlendArrays(const sf::Uint8 *back, unsigned int back_width,  unsigned int back_height,
                            const sf::Uint8 *front,  unsigned int front_width, unsigned int front_height) {
    sf::Uint8 *result = new sf::Uint8[back_width * back_height * 4];

    for(unsigned int y = 0; y < front_height; y++)
    for(unsigned int x = 0; x < front_width; x++) {
        unsigned int back_index  = 4 * (y * back_width + x);
        unsigned int front_index = 4 * (y * front_width + x);

        for(int i = 0; i < 3; i++) {
            result[back_index + i] =  back [back_index + i]  * (255 - front[front_index + 3]) 
                                + front[front_index + i] *        front[front_index + 3];
        }

        result[back_index + 3] = back[back_index + 3];
    }

    return result;
}