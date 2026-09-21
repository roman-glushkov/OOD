#pragma once
#include "ShapeAdapter.h"
#include "CPoint.h"
#include "../utils/Config.h"

class CTriangle : public ShapeAdapter<sf::ConvexShape> 
{
public:
    CTriangle(const CPoint& p1, const CPoint& p2, const CPoint& p3);

    double GetArea() const override;
    double GetPerimeter() const override;
    bool Contains(const sf::Vector2f& point) const override;
    void Move(float dx, float dy) override;

    std::string GetTypePrefix() const override { return Config::TYPE_TRIANGLE; }

protected:
    sf::Color GetDefaultOutlineColor() const override;

private:
    CPoint m_p1, m_p2, m_p3;
};