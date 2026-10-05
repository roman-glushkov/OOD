#pragma once
#include <string>
#include <functional>
#include <SFML/Graphics.hpp>

class Button 
{
public:
    Button(sf::FloatRect bounds, const std::string& label, std::function<void()> onClick);
    bool Contains(sf::Vector2f pos) const;
    void Click();
    void SetActive(bool active) { m_active = active; }
    void SetBounds(sf::FloatRect bounds) { m_bounds = bounds; }
    bool IsActive() const { return m_active; }
    void SetFillColor(sf::Color c) { m_fillColor = c; }
    void Draw(sf::RenderWindow& window) const;

private:
    sf::FloatRect m_bounds;
    std::string m_label;
    std::function<void()> m_onClick;
    bool m_active = false;
    sf::Color m_fillColor = sf::Color(220, 220, 220);
};
