#include "toolbar/Toolbar.h"

#include "commands/ModifyShapesCommand.h"
#include "editor/Editor.h"
#include "shapes/CCircle.h"
#include "shapes/CRectangle.h"
#include "shapes/CTriangle.h"
#include "toolbar/ToolState.h"
#include "utils/Config.h"

#include <functional>
#include <utility>

Toolbar::Toolbar(Editor& editor)
    : m_editor(editor)
{
    BuildAllButtons();
    SetCurrentTool(ToolState::CreateDrag());
    UpdateVisibleButtons();
}

void Toolbar::BuildAllButtons()
{
    const float size = Config::TOOLBAR_BUTTON_SIZE;

    // === D — drag ===
    m_dragButton = std::make_unique<Button>(
        sf::FloatRect({0, 0}, {size, size}),
        "D",
        [this]()
        {
            m_mode = Mode::Drag;
            SetCurrentTool(ToolState::CreateDrag());
            UpdateVisibleButtons();
        }
    );
    m_dragButton->SetFillColor(sf::Color(180, 220, 255));

    // === T — добавить треугольник ===
    m_addTriangleButton = std::make_unique<Button>(
        sf::FloatRect({0, 0}, {size, size}),
        "T",
        [this]()
        {
            SetCurrentTool(ToolState::CreateAddShape(
                "Triangle",
                [](sf::Vector2f pos)
                {
                    return std::make_unique<CTriangle>(
                        CPoint(pos.x, pos.y),
                        CPoint(pos.x + 80, pos.y),
                        CPoint(pos.x + 40, pos.y + 80)
                    );
                }
            ));
            UpdateVisibleButtons();
        }
    );
    m_addTriangleButton->SetFillColor(sf::Color(255, 220, 180));

    // === R — добавить прямоугольник ===
    m_addRectangleButton = std::make_unique<Button>(
        sf::FloatRect({0, 0}, {size, size}),
        "R",
        [this]()
        {
            SetCurrentTool(ToolState::CreateAddShape(
                "Rectangle",
                [](sf::Vector2f pos)
                {
                    return std::make_unique<CRectangle>(
                        CPoint(pos.x, pos.y),
                        CPoint(pos.x + 100, pos.y + 60)
                    );
                }
            ));
            UpdateVisibleButtons();
        }
    );
    m_addRectangleButton->SetFillColor(sf::Color(255, 200, 200));

    // === C — добавить круг ===
    m_addCircleButton = std::make_unique<Button>(
        sf::FloatRect({0, 0}, {size, size}),
        "C",
        [this]()
        {
            SetCurrentTool(ToolState::CreateAddShape(
                "Circle",
                [](sf::Vector2f pos)
                {
                    return std::make_unique<CCircle>(
                        CPoint(pos.x, pos.y),
                        40.0
                    );
                }
            ));
            UpdateVisibleButtons();
        }
    );
    m_addCircleButton->SetFillColor(sf::Color(200, 220, 255));

    // === O — режим обводки ===
    m_outlineButton = std::make_unique<Button>(
        sf::FloatRect({0, 0}, {size, size}),
        "O",
        [this]()
        {
            m_mode = Mode::Outline;
            UpdateVisibleButtons();
        }
    );
    m_outlineButton->SetFillColor(sf::Color(255, 220, 180));

    // === F — режим заливки ===
    m_fillButton = std::make_unique<Button>(
        sf::FloatRect({0, 0}, {size, size}),
        "F",
        [this]()
        {
            m_mode = Mode::Fill;
            SetCurrentTool(ToolState::CreateFill(m_currentFillColor));
            UpdateVisibleButtons();
        }
    );
    m_fillButton->SetFillColor(sf::Color(180, 255, 180));

    // === Цвета ===
    auto addColorButton = [this, size](sf::Color color)
    {
        auto btn = std::make_unique<Button>(
            sf::FloatRect({0, 0}, {size, size}),
            "",
            [this, color]()
            {
                m_currentFillColor = color;

                const auto& selected = m_editor.GetSelected();
                if (selected.empty()) return;

                ModifyShapesCommand cmd(
                    selected,
                    [this, color](IShape* s)
                    {
                        if (m_mode == Mode::Fill)
                            s->SetFillColor(color);
                        else
                            s->SetOutlineColor(color);
                    }
                );
                cmd.Execute();
            }
        );
        btn->SetFillColor(color);
        m_colorButtons.push_back(std::move(btn));
    };

    addColorButton(sf::Color(Config::PALETTE_RED_R,    Config::PALETTE_RED_G,    Config::PALETTE_RED_B));
    addColorButton(sf::Color(Config::PALETTE_GREEN_R,  Config::PALETTE_GREEN_G,  Config::PALETTE_GREEN_B));
    addColorButton(sf::Color(Config::PALETTE_BLUE_R,   Config::PALETTE_BLUE_G,   Config::PALETTE_BLUE_B));
    addColorButton(sf::Color(Config::PALETTE_YELLOW_R, Config::PALETTE_YELLOW_G, Config::PALETTE_YELLOW_B));
    addColorButton(sf::Color(Config::PALETTE_BLACK_R,  Config::PALETTE_BLACK_G,  Config::PALETTE_BLACK_B));

    // === Толщины ===
    auto addThicknessButton = [this, size](float t, const std::string& label)
    {
        auto btn = std::make_unique<Button>(
            sf::FloatRect({0, 0}, {size, size}),
            label,
            [this, t]()
            {
                const auto& selected = m_editor.GetSelected();
                if (selected.empty()) return;

                ModifyShapesCommand cmd(
                    selected,
                    [t](IShape* s) { s->SetOutlineThickness(t); }
                );
                cmd.Execute();
            }
        );
        btn->SetFillColor(sf::Color(230, 230, 230));
        m_thicknessButtons.push_back(std::move(btn));
    };

    addThicknessButton(Config::THICKNESS_THIN,   "1");
    addThicknessButton(Config::THICKNESS_MEDIUM, "3");
    addThicknessButton(Config::THICKNESS_THICK,  "5");
}

void Toolbar::UpdateVisibleButtons()
{
    m_visibleButtons.clear();

    // --- Всегда видимые: D, T, R, C ---
    m_visibleButtons.push_back(m_dragButton.get());
    m_visibleButtons.push_back(m_addTriangleButton.get());
    m_visibleButtons.push_back(m_addRectangleButton.get());
    m_visibleButtons.push_back(m_addCircleButton.get());

    // --- Если есть выделение ---
    bool hasSelection = !m_editor.GetSelected().empty();

    if (hasSelection)
    {
        m_visibleButtons.push_back(m_outlineButton.get());
        m_visibleButtons.push_back(m_fillButton.get());

        if (m_mode == Mode::Outline)
        {
            for (auto& b : m_colorButtons)     m_visibleButtons.push_back(b.get());
            for (auto& b : m_thicknessButtons) m_visibleButtons.push_back(b.get());
        }
        else if (m_mode == Mode::Fill)
        {
            for (auto& b : m_colorButtons) m_visibleButtons.push_back(b.get());
        }
    }
    else
    {
        m_mode = Mode::Drag;
    }

    UpdateButtonsPosition();
}

void Toolbar::UpdateButtonsPosition()
{
    const float size = Config::TOOLBAR_BUTTON_SIZE;
    float x = Config::TOOLBAR_PADDING;
    const float y = Config::TOOLBAR_PADDING;

    for (Button* btn : m_visibleButtons)
    {
        btn->SetBounds(sf::FloatRect({x, y}, {size, size}));
        x += size + Config::TOOLBAR_PADDING;
    }
}

bool Toolbar::HandleEvent(const sf::Event& event)
{
    if (event.is<sf::Event::MouseButtonPressed>())
    {
        UpdateVisibleButtons();
    }

    if (auto* mousePressed = event.getIf<sf::Event::MouseButtonPressed>())
    {
        if (mousePressed->position.y < Config::TOOLBAR_HEIGHT)
        {
            if (mousePressed->button == sf::Mouse::Button::Left)
            {
                sf::Vector2f pos(
                    static_cast<float>(mousePressed->position.x),
                    static_cast<float>(mousePressed->position.y)
                );
                for (Button* btn : m_visibleButtons)
                {
                    if (btn->Contains(pos))
                    {
                        btn->Click();
                        return true;
                    }
                }
            }
            return true;
        }
    }

    if (m_currentTool)
    {
        bool handled = m_currentTool->HandleEvent(event, m_editor);
        if (handled)
        {
            UpdateVisibleButtons();
        }
        return handled;
    }
    return false;
}

void Toolbar::Draw(sf::RenderWindow& window) const
{
    sf::RectangleShape background;
    background.setSize({
        static_cast<float>(Config::WINDOW_WIDTH),
        Config::TOOLBAR_HEIGHT
    });
    background.setPosition({0, 0});
    background.setFillColor(sf::Color(230, 230, 230));
    window.draw(background);

    for (Button* btn : m_visibleButtons)
    {
        btn->Draw(window);
    }
}

void Toolbar::SetCurrentTool(std::unique_ptr<ITool> tool)
{
    m_currentTool = std::move(tool);
}