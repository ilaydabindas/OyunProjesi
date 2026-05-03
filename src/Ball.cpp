#include "Ball.h"

Ball::Ball(float startX, float startY)
{
    shape.setRadius(10.f); //topun yarıçapı. 
    shape.setFillColor(sf::Color::White); // topun rengi. 
    shape.setPosition(sf::Vector2f(startX, startY)); // topun başlangıç konumu. 
    velocity = sf::Vector2f(.12f, -.12f); // topun hareket hızı. 
}

void Ball::update() // topun hareketi burada gerçekleşir.
{
    // top aktif değilse hareketi ve çarpışmaları iptal et. 
    if (!active)
    {
        return;
    }

    shape.move(velocity); //topu hareket ettirir. 

    // sol-sağ duvar çarpışması. 
    if(shape.getPosition().x <= 0 || shape.getPosition().x + shape.getRadius()*2 >= 800)
    {
        reverseX();
    }

    // üst duvar çarpışması. 
    if (shape.getPosition().y <= 0)
    {
        reverseY();
    }
}

// topu ekrana çizer. 
void Ball::draw(sf::RenderWindow& window)
{
    window.draw(shape);
}

// sağ-sol değiştirir. 
void Ball::reverseX()
{
    velocity.x = -velocity.x;
}

// yukarı-aşağı değiştirir. 
void Ball::reverseY()
{
    velocity.y = -velocity.y;
}

// topun mevcut konumunu döndürür. 
sf::Vector2f Ball::getPosition()
{
    return shape.getPosition();
}

// topu istenen konuma taşır. 
void Ball::setPosition(float x, float y)
{
    shape.setPosition(sf::Vector2f(x,y));
}

// topun durumunu oku.
bool Ball::getActive() const
{
    return active;
}

// topu harekete geçirir. 
void Ball::launch()
{
    active = true;
    // top aşağı düştükten sonra hemen paddle'a çarpmasın diye yönünü yukarı çeviririz.
    if (velocity.y > 0)
    {
        velocity.y = -velocity.y;
    } 
}

// topu pasife alır, düştüğünde kullanacağız. 
void Ball::reset()
{
    active = false;
}