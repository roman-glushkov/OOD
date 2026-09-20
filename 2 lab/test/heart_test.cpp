#include <SFML/Graphics.hpp>
#include <cmath>

int main() {
    sf::RenderWindow window(sf::VideoMode({800, 600}), "I LOVE YOU");
    
    sf::ConvexShape heart;
    heart.setPointCount(100);
    
    const float scale = 15.0f;
    const float centerX = 400.0f;
    const float centerY = 300.0f;
    
    for (int i = 0; i < 100; i++) {
        float t = 2.0f * 3.14159f * i / 100.0f;
        
        float x = 16.0f * std::pow(std::sin(t), 3.0f);
        float y = 13.0f * std::cos(t) - 5.0f * std::cos(2.0f * t) - 
                  2.0f * std::cos(3.0f * t) - std::cos(4.0f * t);
        
        x = centerX + x * scale;
        y = centerY - y * scale;
        
        heart.setPoint(i, sf::Vector2f(x, y));
    }
    
    heart.setFillColor(sf::Color::Red);
    heart.setOutlineColor(sf::Color(200, 0, 0));
    heart.setOutlineThickness(2.0f);
    
    while (window.isOpen()) {
        while (auto event = window.pollEvent()) {
            if (event->is<sf::Event::Closed>()) {
                window.close();
            }
            if (const auto* keyEvent = event->getIf<sf::Event::KeyPressed>()) {
                if (keyEvent->code == sf::Keyboard::Key::Escape) {
                    window.close();
                }
            }
        }
        
        window.clear(sf::Color::White);
        window.draw(heart);
        window.display();
    }
    
    return 0;
}