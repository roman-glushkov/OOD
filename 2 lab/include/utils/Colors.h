#pragma once
#include <SFML/Graphics.hpp>
#include "Config.h"

namespace ShapeColors 
{
    inline sf::Color TriangleFill() 
    {
        return sf::Color(Config::TRIANGLE_FILL_R, Config::TRIANGLE_FILL_G,
                         Config::TRIANGLE_FILL_B, Config::TRIANGLE_FILL_A);
    }
    inline sf::Color TriangleOutline() 
    {
        return sf::Color(Config::TRIANGLE_OUT_R, Config::TRIANGLE_OUT_G, Config::TRIANGLE_OUT_B);
    }

    inline sf::Color RectangleFill() 
    {
        return sf::Color(Config::RECT_FILL_R, Config::RECT_FILL_G,
                         Config::RECT_FILL_B, Config::RECT_FILL_A);
    }
    inline sf::Color RectangleOutline() 
    {
        return sf::Color(Config::RECT_OUT_R, Config::RECT_OUT_G, Config::RECT_OUT_B);
    }

    inline sf::Color CircleFill() 
    {
        return sf::Color(Config::CIRCLE_FILL_R, Config::CIRCLE_FILL_G,
                         Config::CIRCLE_FILL_B, Config::CIRCLE_FILL_A);
    }
    inline sf::Color CircleOutline() 
    {
        return sf::Color(Config::CIRCLE_OUT_R, Config::CIRCLE_OUT_G, Config::CIRCLE_OUT_B);
    }

    inline sf::Color SelectedOutline() 
    {
        return sf::Color(Config::SELECTED_R, Config::SELECTED_G, Config::SELECTED_B);
    }

    inline float OutlineThickness() 
    { 
        return Config::OUTLINE_THICKNESS; 
    }
    inline int   CirclePointCount() 
    { 
        return Config::CIRCLE_POINT_COUNT; 
    }
}