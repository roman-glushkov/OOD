#pragma once

#include "toolbar/Button.h"
#include "toolbar/ITool.h"

#include <memory>
#include <vector>
#include <SFML/Graphics.hpp>

class Editor;

// НОВОЕ: панель инструментов (ЛР3)
class Toolbar
{
public:
    explicit Toolbar(Editor& editor);
    bool HandleEvent(const sf::Event& event);          // обработать событие
    void Draw(sf::RenderWindow& window) const;          // нарисовать

private:
    void BuildButtons();                                // создать кнопки

    Editor& m_editor;
    std::unique_ptr<ITool> m_tool;                      // текущий инструмент (State)
    std::vector<std::unique_ptr<Button>> m_buttons;     // все кнопки
    sf::Color m_color = sf::Color(255, 100, 100);       // текущий цвет
};