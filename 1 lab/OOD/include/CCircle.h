// CCircle.h
#pragma once
#include "IShape.h"
#include "CPoint.h"
#include <SFML/Graphics.hpp>

class CCircle : public IShape {
public:
    CCircle(const CPoint& center, double radius, const sf::CircleShape& shape);
    
    double GetArea() const override;
    double GetPerimeter() const override;
    void Draw(sf::RenderWindow& window) const override;
    
protected:
    std::string GetTypePrefix() const override { return "CIRCLE"; }
    
private:
    CPoint m_center;
    double m_radius;
    sf::CircleShape m_shape;
};