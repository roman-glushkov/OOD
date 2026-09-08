#pragma once
#include <SFML/Graphics.hpp>

namespace ShapeColors {
    inline sf::Color TriangleFill() {
        return sf::Color(100, 255, 100, 180); 
    }
    
    inline sf::Color TriangleOutline() {
        return sf::Color(0, 150, 0);
    }
    
    inline sf::Color RectangleFill() {
        return sf::Color(255, 100, 100, 180);  
    }
    
    inline sf::Color RectangleOutline() {
        return sf::Color(150, 0, 0); 
    }
    
    inline sf::Color CircleFill() {
        return sf::Color(100, 200, 255, 180);  
    }
    
    inline sf::Color CircleOutline() {
        return sf::Color(0, 100, 200); 
    }
    
    inline float OutlineThickness() {
        return 2.0f;
    }
    
    inline int CirclePointCount() {
        return 100; 
    }
}