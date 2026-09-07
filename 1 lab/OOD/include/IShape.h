// IShape.h
#pragma once
#include <string>
#include <SFML/Graphics.hpp>

class IShape {
public:
    virtual ~IShape() = default;
    
    virtual double GetArea() const = 0;
    virtual double GetPerimeter() const = 0;
    virtual std::string ToString() const = 0;
    
    // Новый метод для визуализации
    virtual void Draw(sf::RenderWindow& window) const = 0;
};