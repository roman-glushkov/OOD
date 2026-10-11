#pragma once
#include <SFML/Graphics.hpp>
#include <string>
#include "utils/Config.h"

namespace ConfigToolbar
{
    const float SIZE    = Config::TOOLBAR_BUTTON_SIZE;
    const float PADDING = Config::TOOLBAR_PADDING;
    const float Y       = Config::TOOLBAR_PADDING;

    // === Позиции ===
    const float POS_DRAG     = PADDING;
    const float POS_ADD_TRI  = POS_DRAG      + SIZE + PADDING;
    const float POS_ADD_RECT = POS_ADD_TRI   + SIZE + PADDING;
    const float POS_ADD_CIRC = POS_ADD_RECT  + SIZE + PADDING;

    const float POS_COLOR_1  = POS_ADD_CIRC  + SIZE + PADDING * 2;
    const float POS_COLOR_2  = POS_COLOR_1   + SIZE + PADDING;
    const float POS_COLOR_3  = POS_COLOR_2   + SIZE + PADDING;
    const float POS_COLOR_4  = POS_COLOR_3   + SIZE + PADDING;
    const float POS_COLOR_5  = POS_COLOR_4   + SIZE + PADDING;

    const float POS_FILL_COLOR_1 = POS_COLOR_5     + SIZE + PADDING * 2;
    const float POS_FILL_COLOR_2 = POS_FILL_COLOR_1 + SIZE + PADDING;
    const float POS_FILL_COLOR_3 = POS_FILL_COLOR_2 + SIZE + PADDING;
    const float POS_FILL_COLOR_4 = POS_FILL_COLOR_3 + SIZE + PADDING;
    const float POS_FILL_COLOR_5 = POS_FILL_COLOR_4 + SIZE + PADDING;

    const float POS_THICK_1  = POS_FILL_COLOR_5 + SIZE + PADDING * 2;
    const float POS_THICK_2  = POS_THICK_1      + SIZE + PADDING;
    const float POS_THICK_3  = POS_THICK_2      + SIZE + PADDING;

    // === Тексты на кнопках ===
    const std::string LABEL_DRAG     = "D";
    const std::string LABEL_FILL     = "F";
    const std::string LABEL_TRIANGLE = "T";
    const std::string LABEL_RECT     = "R";
    const std::string LABEL_CIRCLE   = "C";
    const std::string LABEL_EMPTY    = "";

    const std::string LABEL_THICK_1 = "1";
    const std::string LABEL_THICK_3 = "3";
    const std::string LABEL_THICK_5 = "5";

    // === Имена инструментов ===
    const std::string TOOL_TRIANGLE = "T";
    const std::string TOOL_RECT     = "R";
    const std::string TOOL_CIRCLE   = "C";

    // === Цвета кнопок режимов ===
    inline sf::Color DragColor()  { return sf::Color(180, 220, 255); }
    inline sf::Color FillColor()  { return sf::Color(180, 255, 180); }
    inline sf::Color AddColor()   { return sf::Color(255, 220, 180); }
    inline sf::Color ThickColor() { return sf::Color(230, 230, 230); }

    // === Палитра ===
    const int PALETTE_SIZE = 5;

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

    // === Смещения фигур ===
    const float TRI_OFFSET_X1 = 80.0f;
    const float TRI_OFFSET_Y1 = 0.0f;
    const float TRI_OFFSET_X2 = 40.0f;
    const float TRI_OFFSET_Y2 = 80.0f;

    const float RECT_WIDTH  = 100.0f;
    const float RECT_HEIGHT = 60.0f;

    const float CIRCLE_RADIUS = 40.0f;

    // === Стиль кнопки ===
    const float BUTTON_OUTLINE_THICKNESS        = 1.0f;
    const float BUTTON_OUTLINE_THICKNESS_HOLLOW = 3.0f;

    const int BUTTON_OUTLINE_R = 80;
    const int BUTTON_OUTLINE_G = 80;
    const int BUTTON_OUTLINE_B = 80;

    const int BUTTON_TEXT_SIZE = 14;
    const float BUTTON_TEXT_OFFSET_Y = 4.0f;

    const std::string BUTTON_FONT_PATH = "arial.ttf";

    // === Фон тулбара ===
    const int TOOLBAR_BG_R = 230;
    const int TOOLBAR_BG_G = 230;
    const int TOOLBAR_BG_B = 230;

    inline sf::Color ToolbarBackground()
    {
        return sf::Color(TOOLBAR_BG_R, TOOLBAR_BG_G, TOOLBAR_BG_B);
    }

    // === Цвет по умолчанию ===
    const int DEFAULT_COLOR_R = 255;
    const int DEFAULT_COLOR_G = 100;
    const int DEFAULT_COLOR_B = 100;

    inline sf::Color DefaultColor()
    {
        return sf::Color(DEFAULT_COLOR_R, DEFAULT_COLOR_G, DEFAULT_COLOR_B);
    }

    const std::string TOOL_NAME_DRAG = "Drag";
    const std::string TOOL_NAME_FILL = "Fill";
}