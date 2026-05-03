#pragma once
#include <vector>
#include <string>
#include "Brick.h"

class LevelManager {
public:
    // .txt dosyasını okuyup içindeki blokları liste halinde döndürür
    std::vector<Brick> loadLevel(const std::string& filename);

private:
    // blokların ekrana dizilirken kullanacağı varsayılan ölçüler
    float startX = 60.f;      // ilk bloğun soldan boşluğu
    float startY = 60.f;      // ilk bloğun yukarıdan boşluğu
    float brickWidth = 60.f;  // blok genişliği
    float brickHeight = 20.f; // blok yüksekliği
};