#include "toolbar/Button.h"

#include <utility>

Button::Button(
    sf::FloatRect bounds,
    const std::string& label,
    std::function<void()> onClick
)
    : m_bounds(bounds)
    , m_label(label)
    , m_onClick(std::move(onClick))
{
}

bool Button::Contains(sf::Vector2f pos) const
{
    return m_bounds.contains(pos);
}

void Button::Click()
{
    if (m_onClick)
    {
        m_onClick();
    }
}

void Button::Draw(sf::RenderWindow& window) const
{
    sf::RectangleShape rect;
    rect.setPosition(m_bounds.position);
    rect.setSize(m_bounds.size);
    rect.setFillColor(m_fillColor);
    rect.setOutlineColor(sf::Color(80, 80, 80));
    rect.setOutlineThickness(1.0f);
    window.draw(rect);

    if (m_label.empty())
    {
        return;
    }

    static sf::Font font;
    static bool loaded = false;
    static bool attempted = false;

    if (!attempted)
    {
        loaded = font.openFromFile("arial.ttf");
        attempted = true;
    }

    if (!loaded)
    {
        return;
    }

    sf::Text text(font, m_label, 14);
    text.setFillColor(sf::Color::Black);
    sf::FloatRect textBounds = text.getLocalBounds();
    text.setPosition({
        m_bounds.position.x + m_bounds.size.x / 2 - textBounds.size.x / 2,
        m_bounds.position.y + m_bounds.size.y / 2 - textBounds.size.y / 2 - 4
    });
    window.draw(text);
}
