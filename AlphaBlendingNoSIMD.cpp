#include "AlphaBlending.hpp"

void alphaBlendArrays(const sf::Uint8 *back,   sf::Vector2u back_size,
                            const sf::Uint8 *front,  sf::Vector2u front_size,
                                  sf::Uint8 *result, sf::Vector2u shift) {
    unsigned int back_width  = back_size.x;
    unsigned int back_height = back_size.y;

    unsigned int front_width  = front_size.x;
    unsigned int front_height = front_size.y;

    unsigned int x_shift = shift.x;
    unsigned int y_shift = shift.y;

    for(unsigned int y = 0; y < front_height; y++)
    for(unsigned int x = 0; x < front_width; x++) 
        {
        unsigned int back_index  = 4 * ((y + y_shift) * back_width + (x + x_shift));
        unsigned int front_index = 4 * (y * front_width + x);

        for(int i = 0; i < 3; i++) 
        {
            result[back_index + i] =  (back [back_index + i]  * (255 - front[front_index + 3]) 
                                     + front[front_index + i] *        front[front_index + 3]) >> 8;
        }

        result[back_index + 3] = back[back_index + 3];
    }
}