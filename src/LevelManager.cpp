#include "LevelManager.h"
#include <fstream>
#include <sstream>
#include <iostream>

std::vector<Brick> LevelManager::loadLevel(const std::string& filename) {
    std::vector<Brick> bricks;
    std::ifstream file(filename); // dosyayı okumak için aç

    // dosya açılamazsa hata ver ve boş liste döndür
    if (!file.is_open()) {
        std::cerr << "Hata: Bolum dosyasi bulunamadi! (" << filename << ")\n";
        return bricks; 
    }

    std::string line;
    int satir = 0; // y ekseni için satır sayacı

    // dosyayı satır satır okuyoruz
    while (std::getline(file, line)) {
        std::stringstream ss(line);
        int typeVal;
        int sutun = 0; // x ekseni için sütun sayacı

        // satırdaki rakamları boşluklara göre tek tek okuyoruz
        while (ss >> typeVal) {
            // eğer rakam 0'dan büyükse (yani boşluk değilse, bir blok tipi ise)
            if (typeVal > 0) {
                // ekrandaki gerçek X ve Y pozisyonunu hesapla
                float x = startX + (sutun * brickWidth);
                float y = startY + (satir * brickHeight);

                // yeni bloğu oluşturup listeye ekle
                bricks.emplace_back(x, y, brickWidth, brickHeight, typeVal);
            }
            sutun++; // yan sütuna geç
        }
        satir++; // alt satıra geç
    }

    file.close(); // dosyayı kapat
    return bricks;
}