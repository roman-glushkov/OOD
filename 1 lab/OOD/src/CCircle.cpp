// CCircle.cpp
#include "CCircle.h"
#include "../utils/Colors.h"
#include <cmath>

const double PI = 3.141592653589793;

CCircle::CCircle(const CPoint& center, double radius)
    : m_center(center), m_radius(radius) {
    m_shape.setRadius(static_cast<float>(radius));
    m_shape.setPosition({
        static_cast<float>(center.x - radius),
        static_cast<float>(center.y - radius)
    });
    m_shape.setPointCount(ShapeColors::CirclePointCount());
    
    m_shape.setFillColor(ShapeColors::CircleFill());
    m_shape.setOutlineColor(ShapeColors::CircleOutline());
    m_shape.setOutlineThickness(ShapeColors::OutlineThickness());
}

double CCircle::GetArea() const {
    return PI * m_radius * m_radius;
}

double CCircle::GetPerimeter() const {
    return 2.0 * PI * m_radius;
}