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

        //top ile paddle çakışıyor mu kontrolü. buradaki 20.f topun çapı. 
        if (ball.getPosition().x < paddle.getPosition().x + paddle.getSize().x && ball.getPosition().x + 20.f > paddle.getPosition().x && ball.getPosition().y < paddle.getPosition().y + paddle.getSize().y && ball.getPosition().y + 20.f > paddle.getPosition().y && ball.getPosition().y < paddle.getPosition().y)
        {
            ball.setPosition(ball.getPosition().x,paddle.getPosition().y-20.f); // topu paddle'ın hemen üstünde koyar, içine girmesini engeller. 
            ball.reverseY(); // topun yönünü yukarı çevirir. 
        }

        window.clear(); // her karede ekranı sıfırlar. 

        paddle.draw(window); // paddle ekrana çizilir. 
        ball.draw(window); // top ekrana çizilir. 

        window.display(); // ekrana çizilenleri gösterir. 
    }
    

    return 0;
}
