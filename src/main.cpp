#include <SFML/Graphics.hpp> // kütüphane eklendi. 
#include "Paddle.h"
#include "Ball.h"
int main()
{
    sf::RenderWindow window(sf::VideoMode({800, 600}), "Arkanoid"); // "Arkanoid" başlıklı pencere oluşturur. 

    Paddle paddle(340.f,550.f); // paddle oluşturur.

    Ball ball(400.f,300.f); //top oluşturur. 

    while (window.isOpen())
    {
        while (auto event = window.pollEvent())
        {
            if (event->is<sf::Event::Closed>())
                window.close(); // pencereyi kapatır. 
        }

        paddle.handleInput(); // sağ-sol hareket. 
        paddle.update(); // ekrandan çıkmasını engeller.  

        ball.update(); // topu hareket ettirir ve duvarlardan sektirir.

        window.clear(); // her karede ekranı sıfırlar. 

        paddle.draw(window); // paddle ekrana çizilir. 
        ball.draw(window); // top ekrana çizilir. 

        window.display(); // ekrana çizilenleri gösterir. 
    }
    

    return 0;
}
