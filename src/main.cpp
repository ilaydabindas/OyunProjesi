#include <SFML/Graphics.hpp> // kütüphane eklendi. 
#include "Paddle.h"
int main()
{
    sf::RenderWindow window(sf::VideoMode({800, 600}), "Arkanoid"); // "Arkanoid" başlıklı pencere oluşturur. 

    Paddle paddle(340.f,550.f); // paddle oluşturur.

    while (window.isOpen())
    {
        while (auto event = window.pollEvent())
        {
            if (event->is<sf::Event::Closed>())
                window.close(); // pencereyi kapatır. 
        }

        paddle.handleInput();
        paddle.update();


        window.clear(); // her karede ekranı sıfırlar. 

        paddle.draw(window);

        window.display(); // ekrana çizilenleri gösterir. 
    }
    

    return 0;
}
