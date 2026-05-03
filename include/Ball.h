#pragma once
#include <SFML/Graphics.hpp>

class Ball
{
    private:
        sf::CircleShape shape; // daire şeklinde top oluşturur. 
        sf::Vector2f velocity; //hız
        bool active {false}; // topun aktif hareket durumu. başlangıçta hareket etmez.
    public:
        Ball(float startX, float startY);
        void update(); //hareket etmesini sağlar. 
        void draw(sf::RenderWindow& window); // topu ekrana çizer

        // topun konumunu ayarlamak için, çarpışma sonucu oluşabilecek sorunları gidermek için kullanacağız. 
        void setPosition(float x, float y);

        // duvarlara çarpınca sekmesi için yardımcı fonksiyonlar. 
        void bounceSides(); // x yönü (sol-sağ)
        void bounceTop(); //y yönü (üst)

        // hızı ters çevirir.
        void reverseX();
        void reverseY();

        sf::Vector2f getPosition(); // topun mevcut pozisyonu. 

        bool getActive() const; // topun aktif olup olmadığını döndürür.
        void launch(); // topu fırlatarak harekete geçirir.
        void reset(); //topu hareketsiz duruma getirir. paddle ortasına bağlar. 
};