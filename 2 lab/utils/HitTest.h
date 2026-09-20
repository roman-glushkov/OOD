#pragma once
#include "CPoint.h"
#include <SFML/System/Vector2.hpp>
#include <algorithm>
#include <cmath>

namespace HitTest {
    inline bool InCircle(const sf::Vector2f& p, const CPoint& center, double radius) {
        double dx = p.x - center.x;
        double dy = p.y - center.y;
        return (dx * dx + dy * dy) <= (radius * radius);
    }
    inline bool InRectangle(const sf::Vector2f& p, const CPoint& a, const CPoint& b) {
        double minX = std::min(a.x, b.x);
        double maxX = std::max(a.x, b.x);
        double minY = std::min(a.y, b.y);
        double maxY = std::max(a.y, b.y);

        return p.x >= minX && p.x <= maxX &&
               p.y >= minY && p.y <= maxY;
    }

    inline bool InTriangle(const sf::Vector2f& p,
                           const CPoint& a,
                           const CPoint& b,
                           const CPoint& c) {
        auto sign = [](const CPoint& v1, const CPoint& v2, const sf::Vector2f& pt) {
            return (pt.x - v2.x) * (v1.y - v2.y) - (v1.x - v2.x) * (pt.y - v2.y);
        };

        double d1 = sign(a, b, p);
        double d2 = sign(b, c, p);
        double d3 = sign(c, a, p);

        bool hasNeg = (d1 < 0) || (d2 < 0) || (d3 < 0);
        bool hasPos = (d1 > 0) || (d2 > 0) || (d3 > 0);

        return !(hasNeg && hasPos);
    }
}