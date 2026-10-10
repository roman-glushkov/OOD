#pragma once
#include <SFML/Graphics.hpp>
#include "utils/Config.h"

namespace ConfigToolbar
{
    const float SIZE    = Config::TOOLBAR_BUTTON_SIZE;
    const float PADDING = Config::TOOLBAR_PADDING;
    const float Y       = Config::TOOLBAR_PADDING;

    const float POS_DRAG     = PADDING;
    const float POS_FILL     = POS_DRAG      + SIZE + PADDING;
    const float POS_ADD_TRI  = POS_FILL      + SIZE + PADDING;
    const float POS_ADD_RECT = POS_ADD_TRI   + SIZE + PADDING;
    const float POS_ADD_CIRC = POS_ADD_RECT  + SIZE + PADDING;

    const float POS_COLOR_1  = POS_ADD_CIRC  + SIZE + PADDING * 2;
    const float POS_COLOR_2  = POS_COLOR_1   + SIZE + PADDING;
    const float POS_COLOR_3  = POS_COLOR_2   + SIZE + PADDING;
    const float POS_COLOR_4  = POS_COLOR_3   + SIZE + PADDING;
    const float POS_COLOR_5  = POS_COLOR_4   + SIZE + PADDING;

    const float POS_FILL_COLOR_1 = POS_COLOR_5    + SIZE + PADDING * 2;
    const float POS_FILL_COLOR_2 = POS_FILL_COLOR_1 + SIZE + PADDING;
    const float POS_FILL_COLOR_3 = POS_FILL_COLOR_2 + SIZE + PADDING;
    const float POS_FILL_COLOR_4 = POS_FILL_COLOR_3 + SIZE + PADDING;
    const float POS_FILL_COLOR_5 = POS_FILL_COLOR_4 + SIZE + PADDING;

    const float POS_THICK_1  = POS_FILL_COLOR_5 + SIZE + PADDING * 2;
    const float POS_THICK_2  = POS_THICK_1    + SIZE + PADDING;
    const float POS_THICK_3  = POS_THICK_2    + SIZE + PADDING;

    inline sf::Color DragColor()  { return sf::Color(180, 220, 255); }
    inline sf::Color FillColor()  { return sf::Color(180, 255, 180); }
    inline sf::Color AddColor()   { return sf::Color(255, 220, 180); }
    inline sf::Color ThickColor() { return sf::Color(230, 230, 230); }

    inline sf::Color PaletteColor(int index)
    {
        switch (index)
        {
        case 0: return sf::Color(Config::PALETTE_RED_R,    Config::PALETTE_RED_G,    Config::PALETTE_RED_B);
        case 1: return sf::Color(Config::PALETTE_GREEN_R,  Config::PALETTE_GREEN_G,  Config::PALETTE_GREEN_B);
        case 2: return sf::Color(Config::PALETTE_BLUE_R,   Config::PALETTE_BLUE_G,   Config::PALETTE_BLUE_B);
        case 3: return sf::Color(Config::PALETTE_YELLOW_R, Config::PALETTE_YELLOW_G, Config::PALETTE_YELLOW_B);
        case 4: return sf::Color(Config::PALETTE_BLACK_R,  Config::PALETTE_BLACK_G,  Config::PALETTE_BLACK_B);
        }
        return sf::Color::White;
    }

    const float TRI_OFFSET_X1 = 80.0f;
    const float TRI_OFFSET_Y1 = 0.0f;
    const float TRI_OFFSET_X2 = 40.0f;
    const float TRI_OFFSET_Y2 = 80.0f;

    const float RECT_WIDTH  = 100.0f;
    const float RECT_HEIGHT = 60.0f;

    const float CIRCLE_RADIUS = 40.0f;
}