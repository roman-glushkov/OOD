#pragma once
#include "ShapeAdapter.h"
#include "CPoint.h"
#include "../utils/Config.h"

class CCircle : public ShapeAdapter<sf::CircleShape> 
{
public:
    CCircle(const CPoint& center, double radius);

    double GetArea() const override;
    double GetPerimeter() const override;
    bool Contains(const sf::Vector2f& point) const override;
    void Move(float dx, float dy) override;

    std::string GetTypePrefix() const override { return Config::TYPE_CIRCLE; }

protected:
    sf::Color GetDefaultOutlineColor() const override;

private:
    CPoint m_center;
    double m_radius;
};