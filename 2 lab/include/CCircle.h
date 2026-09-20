#pragma once
#include "ShapeAdapter.h"
#include "CPoint.h"

class CCircle : public ShapeAdapter<sf::CircleShape> {
public:
    CCircle(const CPoint& center, double radius);
    
    double GetArea() const override;
    double GetPerimeter() const override;
    bool Contains(const sf::Vector2f& point) const override;
    
protected:
    std::string GetTypePrefix() const override { return "CIRCLE"; }
    sf::Color GetDefaultOutlineColor() const override;
    
private:
    CPoint m_center;
    double m_radius;
};