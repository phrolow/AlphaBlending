#include "AlphaBlending.hpp"

int main() {
    sf::Image back;

    if(!back.loadFromFile(back_path)) {
        printf("back picture not found!\n");
        exit(1);
    }

    sf::Image front;

    if(!front.loadFromFile(front_path)) {
        printf("front picture not found!\n");
        exit(1);
    }

    sf::Vector2u backSize = back.getSize();

    const unsigned int WIDTH  = backSize.x;
    const unsigned int HEIGHT = backSize.y;

    sf::Vector2u shift(X_SHIFT, Y_SHIFT);

    sf::Uint8* result_array = (sf::Uint8 *) calloc(4 * WIDTH * HEIGHT, sizeof(sf::Uint8));

    memcpy(result_array, back.getPixelsPtr(), 4 * WIDTH * HEIGHT);  

    const sf::Uint8 *back_array = back.getPixelsPtr();
    const sf::Uint8 *front_array = front.getPixelsPtr();

    sf::Vector2u back_size = back.getSize();
    sf::Vector2u front_size = front.getSize();

    sf::Int64 blending_time = 0;
    sf::Clock clock = sf::Clock();
    sf::Time previousTime;
    previousTime = clock.getElapsedTime();
    sf::Time currentTime;

    size_t counter = 0;
    long long unsigned ms_counter = 0;

    while(counter < FIRST_FRAMES + NUM_FRAMES) {
        alphaBlendArrays(back_array,    back_size,
                        front_array,    front_size,
                        result_array,   shift);

        currentTime = clock.getElapsedTime();
        blending_time = currentTime.asMicroseconds() - previousTime.asMicroseconds(); 
        previousTime = currentTime;

        if(counter >= FIRST_FRAMES)
            ms_counter += blending_time;
        
        counter++;
    }

    sf::Image resultImage;
    resultImage.create(WIDTH, HEIGHT, result_array);

    if(!resultImage.saveToFile(result_path)) {
        printf("Failed to save result\n");
    }

    printf("Average time: %llu ms\n", ms_counter / counter);

    free(result_array);

    return 0;
}