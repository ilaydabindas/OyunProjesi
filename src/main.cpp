#include <SFML/Graphics.hpp> // kütüphane eklendi. 
#include <vector>
#include "Paddle.h"
#include "Ball.h"
#include "Brick.h"
#include "LevelManager.h"
#include <string> // skor yazdırmak için
#include <iostream> // hata mesajı için

int main()
{
    sf::RenderWindow window(sf::VideoMode({1000, 600}), "Arkanoid"); // "Arkanoid" başlıklı pencere oluşturur. 

    Paddle paddle(340.f,550.f); // paddle oluşturur.

    Ball ball(400.f,300.f); //top oluşturur. 

    LevelManager levelManager; // level okuyucuyu oluşturur. 
    std::vector<Brick> bricks = levelManager.loadLevel("levels/level1.txt"); //dosyadan blokları okur. 

    int score = 0;

    sf::Font font;
    
    if (!font.openFromFile("assets/BoldPixels.ttf")) 
    {
        std::cout << "Font dosyasi bulunamadi!" << std::endl;
    }
    sf::RectangleShape panel({200.f,600.f});
    panel.setPosition({800.f,0.f}); 
    panel.setFillColor(sf::Color(25,25,30));

    sf::RectangleShape ayiriciCizgi({5.f,600.f});
    ayiriciCizgi.setPosition({800.f,0.f});
    ayiriciCizgi.setFillColor(sf::Color(100,100,100));

    sf::Text scoreText(font);
    scoreText.setCharacterSize(28); // yazı boyutu
    scoreText.setFillColor(sf::Color::White); // Yazı rengi
    scoreText.setPosition({815.f, 30.f}); // sağ panel
    scoreText.setString("SKOR: 0"); // başlangıç yazısı

    sf::Text canSayisi(font);
    canSayisi.setCharacterSize(28);
    canSayisi.setFillColor(sf::Color(180,0,0));
    canSayisi.setPosition({815.f,100.f});
    canSayisi.setString("Can:");

    sf::Texture kalp;
    if(!kalp.loadFromFile("assets/heart.png"))
    {
        std::cout << "Kalp resmi bulunamadı!" << std::endl;
        return -1;
    }
    sf::Sprite kalpSprite(kalp);
    kalpSprite.setScale({0.07f,0.07f}); // kalp.png büyüklüğü 1024x1024 olduğundan küçültüyoruz. 
    int aktifCanSayisi = 3;

    sf::Text powerup(font);
    powerup.setCharacterSize(20);
    powerup.setFillColor(sf::Color(178,102,255));
    powerup.setPosition({815.f,180.f});
    powerup.setString(U"Aktif Güçlendirme:"); // başa U koyarak türkçe karakter desteği verdik. 
    powerup.setStyle(sf::Text::Underlined); // altı çizili.

    sf::Text powerupList(font);
    powerupList.setCharacterSize(20);
    powerupList.setFillColor(sf::Color::White);
    powerupList.setPosition({815.f,205.f});
    powerupList.setString("- YOK -");


    sf::Text ballSpeed(font);
    ballSpeed.setCharacterSize(22);
    ballSpeed.setFillColor(sf::Color(224,224,224));
    ballSpeed.setPosition({815.f,450.f});
    ballSpeed.setString(U"Top Hızı : %100");

    sf::Text level(font);
    level.setCharacterSize(24);
    level.setFillColor(sf::Color(255,200,0));
    level.setPosition({815.f,520.f});
    level.setString("LEVEL : 1");


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
                        int kazanilanPuan = brick.hit(); // blok vurulur.  (canı azalır veya kırılır)
                        if (kazanilanPuan > 0)
                        {
                            score += kazanilanPuan; // skoru güncelle. 
                            scoreText.setString("SKOR: "+ std::to_string(score)); // ekrandaki yazıyı güncelle. 
                        }
                        ball.reverseY(); // topu ters yöne sektir. 
                        break; // aynı anda iki bloğa birden çarpıp mantık hatası yaratmasını engellemek için döngüyü bitir. 
                    }
                }
            }
            // topun aşağı düşme kontrolü. 
            if (ball.getPosition().y > 600.f)
            {
                aktifCanSayisi--; // bir can azalt. 

                if(aktifCanSayisi >0)
                {
                    ball.reset(); // topu tekrar paddle'a bağlar. 
                }
                else
                {
                    std::cout << "OYUN BİTTİ" << std::endl;
                    window.close(); // ileride burası game over arayüzüne bağlanacak şu anlık pencereyi kapatıyoruz. 
                }
                
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
        window.draw(panel); // paneli çizer.  
        window.draw(ayiriciCizgi); // ayırıcı çizgiyi çizer.
        window.draw(scoreText); // aktif skor ekrana çizilir. 

        window.draw(canSayisi); // aktif can sayısını çizer. 
        for (int i=0; i< aktifCanSayisi; i++)
        {
            // her kalbi x ekseninde 30 piksel sağa kaydırarak yerleştir.
            kalpSprite.setPosition({850.f + (i*32.f),88.f});
            window.draw(kalpSprite);
        }

        window.draw(powerup); // aktif güçlendirme başlığını çizer.
        window.draw(powerupList); // aktif güçlendirmeleri listeler. 
        window.draw(ballSpeed); // aktif top hızını yazar. 
        window.draw(level); // aktif leveli çizer. 

        window.display(); // ekrana çizilenleri gösterir. 
    }
    

    return 0;
}
