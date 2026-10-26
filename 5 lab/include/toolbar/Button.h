#pragma once
#include <string>
#include <functional>
#include <SFML/Graphics.hpp>

class Button 
{
public:
    Button(sf::FloatRect bounds, const std::string& label, std::function<void()> onClick); // конструктор
    bool Contains(sf::Vector2f pos) const; // попала ли точка в кнопку
    void Click();                                                    
    void SetFillColor(sf::Color c) { m_fillColor = c; }              
    void SetOutlineMode(bool outline) { m_isOutline = outline; } 
    void Draw(sf::RenderWindow& window) const;   

private:
    sf::FloatRect m_bounds; // позиция и размер
    std::string m_label; // текст на кнопке
    std::function<void()> m_onClick;            
    sf::Color m_fillColor = sf::Color(220, 220, 220);  
    bool m_isOutline = false;                  
};