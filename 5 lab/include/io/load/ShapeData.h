#pragma once
#include <string>
#include <vector>
#include "core/CPoint.h"
#include <SFML/Graphics.hpp>

struct ShapeData
{
    std::string type;
    std::vector<CPoint> points;
    double radius = 0.0;
    std::vector<ShapeData> children;

    // стиль
    sf::Color outlineColor = sf::Color::Black;
    sf::Color fillColor    = sf::Color::White;
    float thickness        = 0.0f;
};