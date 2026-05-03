#pragma once
#include <SFML/Graphics.hpp>

class Brick {
public:
    // bloğun konumunu (X, Y), boyutlarını ve tipini alır.
    Brick(float x, float y, float width, float height, int typeVal);

    // bloğu ekrana çizdiren fonksiyon.
    void draw(sf::RenderWindow& window);

    // bloğun tamamen yok olup olmadığını kontrol eder.
    bool isDestroyed() const;

    // top bloğa çarptığında çağrılır. 
    // bloğun canını azaltır. eğer kırıldıysa puan döndürür, kırılmadıysa 0 döndürür.
    int hit(); 

    // çarpışma kontrolleri için bloğun sınır kutusunu döndürür.
    sf::FloatRect getBounds() const;

private:
    sf::RectangleShape shape; // bloğun şeklini çizer
    int type; // bloğun tipi (1= gümüş, 2= çelik, 3= yakut, 4= altın)
    int hp; // bloğun dayanıklılığı (kalan vuruş sayısı)
    int points; // blok tamamen kırıldığında kazanılacak puan
    bool destroyed{ false }; // başlangıçta tüm bloklar sağlamdır. 
    bool unbreakable{ false }; // altın bloklar için kırılmazlık. 
};