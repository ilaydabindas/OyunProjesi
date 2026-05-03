#include <SFML/Graphics.hpp> // kütüphane eklendi. 

int main()
{
    sf::RenderWindow window(sf::VideoMode({800, 600}), "Arkanoid"); // "Arkanoid" başlıklı pencere oluşturur. 

    while (window.isOpen())
    {
        while (auto event = window.pollEvent())
        {
            if (event->is<sf::Event::Closed>())
                window.close(); // pencereyi kapatır. 
        }

        window.clear(); // her karede ekranı sıfırlar. 
        window.display(); // ekrana çizilenleri gösterir. 
    }

    return 0;
}
