#include "AlphaBlending.hpp"

void alphaBlendArrays(const sf::Uint8 *back,   sf::Vector2u back_size,
                      const sf::Uint8 *front,  sf::Vector2u front_size,
                            sf::Uint8 *result, sf::Vector2u shift) {
    // unsigned int back_width  = back_size.x;
    // unsigned int back_height = back_size.y;

    // unsigned int front_width  = front_size.x;
    // unsigned int front_height = front_size.y;

    // unsigned int x_shift = shift.x;
    // unsigned int y_shift = shift.y;

    // for(unsigned int y = 0; y < front_height; y++)
    // for(unsigned int x = 0; x < front_width; x++) 
    //     {
    //     unsigned int back_index  = 4 * ((y + y_shift) * back_width + (x + x_shift));
    //     unsigned int front_index = 4 * (y * front_width + x);

    //     for(int i = 0; i < 3; i++) 
    //     {
    //         result[back_index + i] =  (back [back_index + i]  * (255 - front[front_index + 3]) 
    //                                  + front[front_index + i] *        front[front_index + 3]) >> 8;
    //     }

    //     result[back_index + 3] = back[back_index + 3];
    // }

    unsigned int back_width  = back_size.x;
    unsigned int back_height = back_size.y;

    unsigned int front_width  = front_size.x;
    unsigned int front_height = front_size.y;

    unsigned int x_shift = shift.x;
    unsigned int y_shift = shift.y;

    const sf::Uint8 Z = 0x80;

    const __m128i   _0 =                   _mm_set1_epi8(0);
    const __m128i _255 = _mm_cvtepu8_epi16(_mm_set1_epi8(255u));

    for(unsigned int y = 0; y < front_height; y++)
    for(unsigned int x = 0; x < front_width; x += 4) 
    {
        unsigned int back_index  = 4 * ((y + y_shift) * back_width + (x + x_shift));
        unsigned int front_index = 4 * (y * (front_width / 16 * 16 + 16) + x);

        __m128i fr = _mm_load_si128((__m128i*) (front + front_index)); //here
        __m128i bk = _mm_load_si128((__m128i*) (back + back_index));

        __m128i FR = (__m128i) _mm_movehl_ps((__m128) _0, (__m128) fr);
        __m128i BK = (__m128i) _mm_movehl_ps((__m128) _0, (__m128) bk);

        fr = _mm_cvtepu8_epi32(fr);
        bk = _mm_cvtepu8_epi32(bk);

        FR = _mm_cvtepu8_epi32(FR);
        BK = _mm_cvtepu8_epi32(BK);

        static const __m128i moveA = _mm_set_epi8 (Z, 14, Z, 14, Z, 14, Z, 14,
                                                   Z,  6, Z,  6, Z,  6, Z,  6);

        __m128i a = _mm_shuffle_epi8 (fr, moveA);                               
        __m128i A = _mm_shuffle_epi8 (FR, moveA);

        fr = _mm_mullo_epi16 (fr, a);                                        
        FR = _mm_mullo_epi16 (FR, A);

        bk = _mm_mullo_epi16 (bk, _mm_sub_epi16 (_255, a));                      
        BK = _mm_mullo_epi16 (BK, _mm_sub_epi16 (_255, A));

        __m128i sum = _mm_add_epi16 (fr, bk);                                 
        __m128i SUM = _mm_add_epi16 (FR, BK);

        static const __m128i moveSum = _mm_set_epi8 ( Z,  Z,  Z, Z, Z, Z, Z, Z,
                                                     15, 13, 11, 9, 7, 5, 3, 1);

        sum = _mm_shuffle_epi8 (sum, moveSum);                                  
        SUM = _mm_shuffle_epi8 (SUM, moveSum);
        
        union {
            __m128i color;
            unsigned char rgba[16];
        };

        color = (__m128i) _mm_movelh_ps ((__m128) sum, (__m128) SUM);   

        printf("(%u, %u, %u, %u)", rgba[0], rgba[1], rgba[2], rgba[3]);

        _mm_store_si128 ((__m128i *) (result + back_index), color);
    }
}