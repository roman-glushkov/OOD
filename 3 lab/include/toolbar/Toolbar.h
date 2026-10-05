#pragma once

#include "toolbar/Button.h"
#include "toolbar/ITool.h"

#include <memory>
#include <vector>

#include <SFML/Graphics.hpp>

class Editor;

class Toolbar
{
public:
    explicit Toolbar(Editor& editor);
    bool HandleEvent(const sf::Event& event);
    void Draw(sf::RenderWindow& window) const;
    void SetCurrentTool(std::unique_ptr<ITool> tool);

private:
    enum class Mode { Drag, Outline, Fill };

    void BuildAllButtons();
    void UpdateVisibleButtons();
    void UpdateButtonsPosition();

    Editor& m_editor;
    Mode m_mode = Mode::Drag;
    bool m_hadSelection = false;

    std::unique_ptr<ITool> m_currentTool;

    // Кнопки режимов
    std::unique_ptr<Button> m_dragButton;
    std::unique_ptr<Button> m_outlineButton;
    std::unique_ptr<Button> m_fillButton;

    // Кнопки добавления фигур
    std::unique_ptr<Button> m_addTriangleButton;
    std::unique_ptr<Button> m_addRectangleButton;
    std::unique_ptr<Button> m_addCircleButton;

    // Цвета и толщины
    std::vector<std::unique_ptr<Button>> m_colorButtons;
    std::vector<std::unique_ptr<Button>> m_thicknessButtons;

    // Видимые кнопки (то, что рисуется и обрабатывается)
    std::vector<Button*> m_visibleButtons;

    sf::Color m_currentFillColor = sf::Color(100, 150, 255);
    sf::Color m_currentOutlineColor = sf::Color::Black;
};