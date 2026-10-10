#pragma once
#include <string>
#include <functional>
#include <SFML/Graphics.hpp>

// НОВОЕ: кнопка тулбара (ЛР3)
class Button 
{
public:
    Button(sf::FloatRect bounds, const std::string& label, std::function<void()> onClick);
    bool Contains(sf::Vector2f pos) const;                            // попала ли точка в кнопку
    void Click();                                                     // вызвать обработчик
    void SetFillColor(sf::Color c) { m_fillColor = c; }               // задать цвет
    void SetOutlineMode(bool outline) { m_isOutline = outline; }      // true = полый квадрат, false = залитый
    void Draw(sf::RenderWindow& window) const;                        // нарисовать

private:
    sf::FloatRect m_bounds;                     // позиция и размер
    std::string m_label;                        // текст на кнопке
    std::function<void()> m_onClick;            // что делать при клике
    sf::Color m_fillColor = sf::Color(220, 220, 220);  // цвет фона
    bool m_isOutline = false;                   // полый квадрат (для цветов обводки)?
};