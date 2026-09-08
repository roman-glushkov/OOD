// ShapeFactory.cpp
#include "ShapeFactory.h"
#include "CTriangle.h"
#include "CRectangle.h"
#include "CCircle.h"
#include "../utils/Colors.h"
#include <sstream>

CPoint ShapeFactory::ParsePoint(const std::string& str) {
    size_t comma = str.find(',');
    double x = std::stod(str.substr(0, comma));
    double y = std::stod(str.substr(comma + 1));
    return CPoint(x, y);
}

std::string ShapeFactory::GetParamValue(const std::string& line, const std::string& paramName) {
    size_t pos = line.find(paramName + "=");
    size_t end = line.find(';', pos);
    if (end == std::string::npos) end = line.length();
    return line.substr(pos + paramName.length() + 1, end - pos - paramName.length() - 1);
}

// ВСЯ НАСТРОЙКА SFML ЗДЕСЬ!
std::shared_ptr<IShape> ShapeFactory::Create(const std::string& line) {
    if (line.find("TRIANGLE:") == 0) {
        CPoint p1 = ParsePoint(GetParamValue(line, "P1"));
        CPoint p2 = ParsePoint(GetParamValue(line, "P2"));
        CPoint p3 = ParsePoint(GetParamValue(line, "P3"));
        
        // Создаём и настраиваем SFML-объект
        sf::ConvexShape shape;
        shape.setPointCount(3);
        shape.setPoint(0, sf::Vector2f(static_cast<float>(p1.x), static_cast<float>(p1.y)));
        shape.setPoint(1, sf::Vector2f(static_cast<float>(p2.x), static_cast<float>(p2.y)));
        shape.setPoint(2, sf::Vector2f(static_cast<float>(p3.x), static_cast<float>(p3.y)));
        shape.setFillColor(ShapeColors::TriangleFill());
        shape.setOutlineColor(ShapeColors::TriangleOutline());
        shape.setOutlineThickness(ShapeColors::OutlineThickness());
        
        return std::make_shared<CTriangle>(p1, p2, p3, shape);
    }
    else if (line.find("RECTANGLE:") == 0) {
        CPoint p1 = ParsePoint(GetParamValue(line, "P1"));
        CPoint p2 = ParsePoint(GetParamValue(line, "P2"));
        
        float width = static_cast<float>(std::abs(p2.x - p1.x));
        float height = static_cast<float>(std::abs(p2.y - p1.y));
        
        // Создаём и настраиваем SFML-объект
        sf::RectangleShape shape;
        shape.setSize(sf::Vector2f(width, height));
        shape.setPosition({
            static_cast<float>(std::min(p1.x, p2.x)),
            static_cast<float>(std::min(p1.y, p2.y))
        });
        shape.setFillColor(ShapeColors::RectangleFill());
        shape.setOutlineColor(ShapeColors::RectangleOutline());
        shape.setOutlineThickness(ShapeColors::OutlineThickness());
        
        return std::make_shared<CRectangle>(p1, p2, shape);
    }
    else if (line.find("CIRCLE:") == 0) {
        CPoint center = ParsePoint(GetParamValue(line, "C"));
        double radius = std::stod(GetParamValue(line, "R"));
        
        // Создаём и настраиваем SFML-объект
        sf::CircleShape shape;
        shape.setRadius(static_cast<float>(radius));
        shape.setPosition({
            static_cast<float>(center.x - radius),
            static_cast<float>(center.y - radius)
        });
        shape.setPointCount(ShapeColors::CirclePointCount());
        shape.setFillColor(ShapeColors::CircleFill());
        shape.setOutlineColor(ShapeColors::CircleOutline());
        shape.setOutlineThickness(ShapeColors::OutlineThickness());
        
        return std::make_shared<CCircle>(center, radius, shape);
    }
    return nullptr;
}