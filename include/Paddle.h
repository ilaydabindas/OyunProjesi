#pragma once // aynı header dosyasının birden çok eklenmesini engeller. 
#include <SFML/Graphics.hpp>

class Paddle // sınıf tanımlanır. 
{
private: // dışarıdan erişilemez. 
    sf::RectangleShape shape; //şekil çizer
    float speed; //hareket hızı

public: // dışarıdan erişilebilir. 
    Paddle(float startX, float startY); // başlangıç konumunu belirler. 

    void handleInput(); // klavye girişini kontrol eder. 
    void update(); // oyun güncelleme fonksiyonu
    void draw(sf::RenderWindow& window); // ekrana çizer. 

    sf::Vector2f getPosition(); // ekran konumunu verir.
    sf::Vector2f getSize(); // boyutunu verir. 
};