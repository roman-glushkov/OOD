#include "toolbar/Button.h"

#include <utility>

// конструктор: сохраняем границы, текст, обработчик
Button::Button(sf::FloatRect bounds, const std::string& label, std::function<void()> onClick)
    : m_bounds(bounds), m_label(label), m_onClick(std::move(onClick)) {}

// проверка попадания точки в кнопку
bool Button::Contains(sf::Vector2f pos) const
{
    return m_bounds.contains(pos);
}

// вызвать обработчик клика
void Button::Click()
{
    if (m_onClick) m_onClick();
}

// нарисовать кнопку
void Button::Draw(sf::RenderWindow& window) const
{
    // фон (залитый или полый)
    sf::RectangleShape rect;
    rect.setPosition(m_bounds.position);
    rect.setSize(m_bounds.size);
    rect.setFillColor(m_isOutline ? sf::Color::Transparent : m_fillColor);  // полый или залитый
    rect.setOutlineColor(m_isOutline ? m_fillColor : sf::Color(80, 80, 80)); // цвет контура
    rect.setOutlineThickness(m_isOutline ? 3.0f : 1.0f);                     // толще для полых
    window.draw(rect);

    // если нет текста — выходим
    if (m_label.empty()) return;

    // ленивая загрузка шрифта (один раз)
    static sf::Font font;
    static bool loaded = false;
    static bool attempted = false;

    if (!attempted)
    {
        loaded = font.openFromFile("arial.ttf");
        attempted = true;
    }

    if (!loaded) return;

    // текст по центру кнопки
    sf::Text text(font, m_label, 14);
    text.setFillColor(sf::Color::Black);
    sf::FloatRect textBounds = text.getLocalBounds();
    text.setPosition({
        m_bounds.position.x + m_bounds.size.x / 2 - textBounds.size.x / 2,
        m_bounds.position.y + m_bounds.size.y / 2 - textBounds.size.y / 2 - 4
    });
    window.draw(text);
}