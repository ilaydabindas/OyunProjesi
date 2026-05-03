#include "Paddle.h"
Paddle::Paddle(float startX, float startY)
{
    shape.setSize(sf::Vector2f(100.f,15.f)); // genişlik ve yükseklik
    shape.setFillColor(sf::Color::White); // renk
    shape.setPosition(sf::Vector2f(startX, startY)); //başlangıç konumu
    speed = .2f; //hareket hızı
}

// klavye girişlerini kontrol eder. 
void Paddle::handleInput()
{
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left))
    {
        shape.move(sf::Vector2f(-speed, 0.f));
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right))
    {
        shape.move(sf::Vector2f(speed, 0.f));
    }
}

void Paddle::update()
{
    // sol sınır
    if(shape.getPosition().x < 0)
    {
        shape.setPosition(sf::Vector2f(0, shape.getPosition().y));
    }
    // sağ sınır (800 ekran genişliği)
    if(shape.getPosition().x + shape.getSize().x > 800)
    {
       shape.setPosition(sf::Vector2f(800 - shape.getSize().x, shape.getPosition().y));
    }
}

// ekrana çizim
void Paddle::draw(sf::RenderWindow& window)
{
    window.draw(shape);
}

// pozisyon bilgisi
sf::Vector2f Paddle::getPosition()
{
    return shape.getPosition();
}
    
// boyut bilgisi
sf::Vector2f Paddle::getSize()
{
    return shape.getSize();
}
