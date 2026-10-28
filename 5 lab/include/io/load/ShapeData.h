#pragma once
#include <string>
#include <vector>
#include "core/CPoint.h"

// Промежуточные данные для Builder.
// Для COMPOSITE используется поле children.
struct ShapeData
{
    std::string type;                    // "TRIANGLE" / "RECTANGLE" / "CIRCLE" / "COMPOSITE"
    std::vector<CPoint> points;
    double radius = 0.0;
    std::vector<ShapeData> children;     // только для COMPOSITE
};