#include "toolbar/Button.h"
#include "utils/ConfigToolbar.h"
#include <utility>

Button::Button(sf::FloatRect bounds, const std::string& label, std::function<void()> onClick)
    : m_bounds(bounds), m_label(label), m_onClick(std::move(onClick)) {}

bool Button::Contains(sf::Vector2f pos) const
{
    return m_bounds.contains(pos);
}

void Button::Click()
{
    if (m_onClick) m_onClick();
}

void Button::Draw(sf::RenderWindow& window) const
{
    using namespace ConfigToolbar;

    // фон
    sf::RectangleShape rect;
    rect.setPosition(m_bounds.position);
    rect.setSize(m_bounds.size);
    sf::Color defaultOutline(BUTTON_OUTLINE_R, BUTTON_OUTLINE_G, BUTTON_OUTLINE_B);
    rect.setFillColor(m_isOutline ? sf::Color::Transparent : m_fillColor);
    rect.setOutlineColor(m_isOutline ? m_fillColor : defaultOutline);
    rect.setOutlineThickness(m_isOutline ? BUTTON_OUTLINE_THICKNESS_HOLLOW : BUTTON_OUTLINE_THICKNESS);
    window.draw(rect);

    if (m_label.empty()) return;

    // текст
    static sf::Font font;
    static bool loaded = false;
    static bool attempted = false;

    if (!attempted)
    {
        loaded = font.openFromFile(BUTTON_FONT_PATH);
        attempted = true;
    }

    if (!loaded) return;

    sf::Text text(font, m_label, BUTTON_TEXT_SIZE);
    text.setFillColor(sf::Color::Black);
    sf::FloatRect textBounds = text.getLocalBounds();
    text.setPosition({
        m_bounds.position.x + m_bounds.size.x / 2 - textBounds.size.x / 2,
        m_bounds.position.y + m_bounds.size.y / 2 - textBounds.size.y / 2 - BUTTON_TEXT_OFFSET_Y
    });
    window.draw(text);
}