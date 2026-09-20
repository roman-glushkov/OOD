#pragma once
#include "ShapeAdapter.h"
#include "CPoint.h"
#include "../utils/Config.h"

class CRectangle : public ShapeAdapter<sf::RectangleShape> {
public:
    CRectangle(const CPoint& p1, const CPoint& p2);

    double GetArea() const override;
    double GetPerimeter() const override;
    bool Contains(const sf::Vector2f& point) const override;
    void Move(float dx, float dy) override;

protected:
    std::string GetTypePrefix() const override { return Config::TYPE_RECTANGLE; }
    sf::Color GetDefaultOutlineColor() const override;

private:
    CPoint m_p1, m_p2;
};