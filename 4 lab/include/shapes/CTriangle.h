#pragma once
#include "adapter/ShapeAdapter.h"
#include "core/CPoint.h"
#include "utils/Config.h"

class CTriangle : public ShapeAdapter<sf::ConvexShape> 
{
public:
    CTriangle(const CPoint& p1, const CPoint& p2, const CPoint& p3);
    double GetArea() const override;
    double GetPerimeter() const override;
    std::string GetTypePrefix() const override { return Config::TYPE_TRIANGLE; }

    bool Contains(const sf::Vector2f& point) const override; 
    void Move(float dx, float dy) override; 

private:
    CPoint m_p1, m_p2, m_p3;
};
