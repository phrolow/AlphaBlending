#include "AlphaBlending.hpp"

void alphaBlendImages(const sf::Image back, const sf::Image front, sf::Uint8 *result, sf::Vector2u shift) {
    const sf::Uint8 *back_array = back.getPixelsPtr();
    const sf::Uint8 *front_array = front.getPixelsPtr();

    sf::Vector2u back_size = back.getSize();
    sf::Vector2u front_size = front.getSize();

    alphaBlendArrays(back_array,  back_size,
                     front_array, front_size,
                     result,      shift);
}

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

    alphaBlendImages(back, front, result_array, shift);

    sf::RenderWindow window(sf::VideoMode(WIDTH, HEIGHT), "AlphaBlending");

    sf::Texture resultTexture;
    resultTexture.create(WIDTH, HEIGHT);
    resultTexture.update(resultTexture);

    sf::Sprite resultSprite(resultTexture);

    sf::Font font;
    if(!font.loadFromFile("impact.ttf")) {
        printf("Font not found!\n");
    }

    char label[12] = {};

    sf::Text text;
    text.setFont(font);
    text.setString(label);
    text.setCharacterSize(24);
    text.setFillColor(sf::Color::Black);

    sf::Int64 blending_time = 0;
    sf::Clock clock = sf::Clock();
    sf::Time previousTime;
    previousTime = clock.getElapsedTime();
    sf::Time currentTime;

    while(window.isOpen()) {
        sf::Event event;

        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed){
                window.close();
            }
        }

        alphaBlendImages(back, front, result_array, shift);
        resultTexture.update(result_array);

        resultSprite.setTexture(resultTexture);

        currentTime = clock.getElapsedTime();
        blending_time = currentTime.asMicroseconds() - previousTime.asMicroseconds(); 
        previousTime = currentTime;

        sprintf(label, "%lld ms", blending_time);
        text.setString(label);

        window.clear();
        window.draw(resultSprite);
        window.draw(text);
        window.display();
    }

    sf::Image resultImage;
        resultImage.create(WIDTH, HEIGHT, result_array);

    if(!resultImage.saveToFile(result_path)) {
        printf("Failed to save result\n");
    }

    free(result_array);

    return 0;
}