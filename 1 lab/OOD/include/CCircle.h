// CCircle.h
#pragma once
#include "IShape.h"
#include "CPoint.h"
#include <SFML/Graphics.hpp>

class CCircle : public IShape {
public:
    CCircle(const CPoint& center, double radius);
    
    double GetArea() const override;
    double GetPerimeter() const override;
    std::string ToString() const override;
    void Draw(sf::RenderWindow& window) const override;  // Новый метод
    
private:
    CPoint m_center;
    double m_radius;
    
    // Адаптируемый объект SFML (создается при первом вызове Draw)
    mutable sf::CircleShape m_sfmlShape;
    mutable bool m_initialized = false;
};