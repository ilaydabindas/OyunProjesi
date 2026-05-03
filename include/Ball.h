#pragma once
#include <SFML/Graphics.hpp>

class Ball
{
    private:
        sf::CircleShape shape; // daire şeklinde top oluşturur. 
        sf::Vector2f velocity; //hız
    
    public:
        Ball(float startX, float startY);
        void update(); //hareket etmesini sağlar. 
        void draw(sf::RenderWindow& window); // topu ekrana çizer

        // duvarlara çarpınca sekmesi için yardımcı fonksiyonlar. 
        void bounceSides(); // x yönü (sol-sağ)
        void bounceTop(); //y yönü (üst)

        // hızı ters çevirir.
        void reverseX();
        void reverseY();

        sf::Vector2f getPosition(); // topun mevcut pozisyonu. 
};