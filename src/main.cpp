#include <SFML/Graphics.hpp> // kütüphane eklendi. 
#include <vector>
#include "Paddle.h"
#include "Ball.h"
#include "Brick.h"
#include "LevelManager.h"

int main()
{
    sf::RenderWindow window(sf::VideoMode({800, 600}), "Arkanoid"); // "Arkanoid" başlıklı pencere oluşturur. 

    Paddle paddle(340.f,550.f); // paddle oluşturur.

    Ball ball(400.f,300.f); //top oluşturur. 

    LevelManager levelManager; // level okuyucuyu oluşturur. 
    std::vector<Brick> bricks = levelManager.loadLevel("levels/level1.txt"); //dosyadan blokları okur. 

    while (window.isOpen())
    {
        while (auto event = window.pollEvent())
        {
            if (event->is<sf::Event::Closed>())
                window.close(); // pencereyi kapatır. 
        }

        paddle.handleInput(); // sağ-sol hareket. 
        paddle.update(); // ekrandan çıkmasını engeller.  

        // top henüz fırlatılmamışsa.
        if(!ball.getActive())
        {
            // topu paddle'ın tam ortasına ve üstüne hizala
            float targetX = paddle.getPosition().x + (paddle.getSize().x / 2.f) -10.f;
            float targetY = paddle.getPosition().y - 20.f;
            ball.setPosition(targetX, targetY);

            // boşluk tuşuna basıldığında topu fırlat.
            if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Space))
            {
                ball.launch(); // topu fırlatır.
            }
        }  
            
        // top havadaysa.
        else
        {
            ball.update(); // topu hareket ettirir ve duvarlardan sektirir.

            // top ile paddle çakışıyor mu kontrolü. buradaki 20.f topun çapı.
            // sadece üstten çarpma.  
            if (ball.getPosition().y + 20.f >= paddle.getPosition().y &&
                ball.getPosition().x + 20.f >= paddle.getPosition().x &&
                ball.getPosition().x <= paddle.getPosition().x + paddle.getSize().x &&
                ball.getPosition().y < paddle.getPosition().y)
            {
                ball.setPosition(ball.getPosition().x,paddle.getPosition().y-20.f); // topu paddle'ın hemen üstünde koyar, içine girmesini engeller. 
                ball.reverseY(); // topun yönünü yukarı çevirir. 
            }

            // tüm blokları tek tek kontrol et.
            for(auto& brick : bricks)
            {
                // eğer blok kırılmamışsa. 
                if(!brick.isDestroyed())
                {
                    sf::FloatRect bounds = brick.getBounds(); // bloğun sınırlarını al. 

                    if (ball.getPosition().x < bounds.position.x + bounds.size.x &&
                    ball.getPosition().x + 20.f > bounds.position.x &&
                    ball.getPosition().y < bounds.position.y + bounds.size.y &&
                    ball.getPosition().y + 20.f > bounds.position.y)
                    {
                        brick.hit(); // blok vurulur.  (canı azalır veya kırılır)
                        ball.reverseY(); // topu ters yöne sektir. 
                        break; // aynı anda iki bloğa birden çarpıp mantık hatası yaratmasını engellemek için döngüyü bitir. 
                    }
                }
            }
            // topun aşağı düşme kontrolü. 
            if (ball.getPosition().y > 600.f)
            {
                ball.reset(); // topu tekrar paddle'a bağlar. 
            }
        }


        window.clear(); // her karede ekranı sıfırlar. 

        // listedeki tüm bloklara teker teker bakar. 
        for (auto& brick : bricks)
        {
            brick.draw(window); // var olan blokları çizer. 
        }

        paddle.draw(window); // paddle ekrana çizilir. 
        ball.draw(window); // top ekrana çizilir. 

        window.display(); // ekrana çizilenleri gösterir. 
    }
    

    return 0;
}
