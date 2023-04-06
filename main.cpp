#include "AlphaBlending.hpp"

sf::Uint8* alphaBlendImages(const sf::Image back, const sf::Image front) {
    const sf::Uint8 *back_array = back.getPixelsPtr();
    const sf::Uint8 *front_array = front.getPixelsPtr();

    sf::Vector2u back_size = back.getSize();
    sf::Vector2u front_size = front.getSize();

    return alphaBlendArrays(back_array,  back_size.x,  back_size.y,
                            front_array, front_size.x, front_size.y);
}

int main() {
    sf::Image back;

    if(!back.loadFromFile(backPath)) {
        printf("back picture not found!\n");
        exit(1);
    }

    sf::Image front;

    if(!front.loadFromFile(frontPath)) {
        printf("front picture not found!\n");
        exit(1);
    }

    sf::Uint8* result_array = alphaBlendImages(back, front);

    sf::Vector2u backSize = back.getSize();

    const unsigned int WIDTH  = backSize.x;
    const unsigned int HEIGHT = backSize.y;

    sf::RenderWindow window(sf::VideoMode(WIDTH, HEIGHT), "Mandelbrot");

    sf::Texture resultTexture;
    resultTexture.create(WIDTH, HEIGHT);
    resultTexture.update(resultTexture);

    sf::Sprite resultSprite(resultTexture);

    while(window.isOpen()) {
        sf::Event event;

        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed){
                window.close();
            }
        }

        result_array = alphaBlendImages(back, front);

        window.clear();
        window.draw(resultSprite);
        window.display();
    }

    sf::Image resultImage;
        resultImage.create(WIDTH, HEIGHT, result_array);

    if(!resultImage.saveToFile(resultPath)) {
        printf("Failed to save result\n");
    }

    return 0;
}