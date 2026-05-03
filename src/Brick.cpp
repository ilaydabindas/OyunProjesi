#include "Brick.h"

Brick::Brick(float x, float y, float width, float height, int typeVal) {
    // pozisyon ve boyut
    shape.setPosition({x, y});
    shape.setSize({width, height});
    
    // çerçeveyi bloğun içine çizdirmek için eksi değer kullanıyoruz. 
    shape.setOutlineThickness(-2.f); 
    shape.setOutlineColor(sf::Color::Black);
    
    // gelen değeri sınıfın kendi değişkenine atıyoruz. 
    type = typeVal;
    
    // tipe göre can, puan ve renk belirleme
    switch (type) {
        case 1: // gümüş Blok
            hp = 1;
            points = 10;
            shape.setFillColor(sf::Color(192, 192, 192));
            break;
        case 2: // çelik Blok
            hp = 2;
            points = 20;
            shape.setFillColor(sf::Color(105, 105, 105));
            break;
        case 3: // yakut Blok
            hp = 3;
            points = 30;
            shape.setFillColor(sf::Color(220, 20, 60));
            break;
        case 4: // altın Blok (kırılamaz)
            hp = 999; 
            points = 0; 
            unbreakable = true;
            shape.setFillColor(sf::Color(255, 215, 0));
            break;
        default:
            hp = 1;
            points = 10;
            shape.setFillColor(sf::Color::White);
            break;
    }
}

void Brick::draw(sf::RenderWindow& window) {
    // Sadece yok edilmemişse ekrana çiz
    if (!destroyed) {
        window.draw(shape);
    }
}

bool Brick::isDestroyed() const {
    return destroyed;
}

int Brick::hit() {
    // eğer altın bloksa (kırılamazsa) canı düşme, 0 puan ver
    if (unbreakable) {
        return 0; 
    }

    hp--; // normal bloksa canı 1 azalt

    // can bittiyse bloğu yok et ve puanını ver
    if (hp <= 0) {
        destroyed = true; 
        return points;    
    }
    
    // vuruldu ama henüz kırılmadıysa 0 puan ver
    return 0; 
}

sf::FloatRect Brick::getBounds() const {
    // çarpışma kontrolü için sınırları ver. 
    return shape.getGlobalBounds();
}