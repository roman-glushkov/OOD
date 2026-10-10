#include "toolbar/Toolbar.h"

#include "commands/ModifyShapesCommand.h"
#include "editor/Editor.h"
#include "shapes/CCircle.h"
#include "shapes/CRectangle.h"
#include "shapes/CTriangle.h"
#include "toolbar/ToolState.h"
#include "utils/Config.h"
#include "utils/ConfigToolbar.h"

#include <functional>
#include <utility>

Toolbar::Toolbar(Editor& editor)
    : m_editor(editor)
{
    BuildButtons();
    m_tool = ToolState::CreateDrag();
}

void Toolbar::BuildButtons()
{
    using namespace ConfigToolbar;

    auto add = [this](float x, const std::string& label, sf::Color color, std::function<void()> onClick)
    {
        auto btn = std::make_unique<Button>(
            sf::FloatRect({x, Y}, {SIZE, SIZE}), label, std::move(onClick));
        btn->SetFillColor(color);
        m_buttons.push_back(std::move(btn));
    };

    add(POS_DRAG, "D", DragColor(), [this]() { m_tool = ToolState::CreateDrag(); });
    add(POS_FILL, "F", FillColor(), [this]() { m_tool = ToolState::CreateFill(m_color); });

    add(POS_ADD_TRI, "T", AddColor(), [this]() {
        m_tool = ToolState::CreateAddShape("T", [](sf::Vector2f p) {
            return std::make_unique<CTriangle>(
                CPoint(p.x, p.y),
                CPoint(p.x + TRI_OFFSET_X1, p.y + TRI_OFFSET_Y1),
                CPoint(p.x + TRI_OFFSET_X2, p.y + TRI_OFFSET_Y2));
        });
    });
    add(POS_ADD_RECT, "R", AddColor(), [this]() {
        m_tool = ToolState::CreateAddShape("R", [](sf::Vector2f p) {
            return std::make_unique<CRectangle>(
                CPoint(p.x, p.y),
                CPoint(p.x + RECT_WIDTH, p.y + RECT_HEIGHT));
        });
    });
    add(POS_ADD_CIRC, "C", AddColor(), [this]() {
        m_tool = ToolState::CreateAddShape("C", [](sf::Vector2f p) {
            return std::make_unique<CCircle>(CPoint(p.x, p.y), CIRCLE_RADIUS);
        });
    });

    const float outlinePositions[] = {POS_COLOR_1, POS_COLOR_2, POS_COLOR_3, POS_COLOR_4, POS_COLOR_5};

    for (int i = 0; i < 5; ++i)
    {
        sf::Color c = PaletteColor(i);

        auto btn = std::make_unique<Button>(
            sf::FloatRect({outlinePositions[i], Y}, {SIZE, SIZE}),
            "",
            [this, c]() {
                const auto& sel = m_editor.GetSelected();
                if (sel.empty()) return;
                ModifyShapesCommand cmd(sel, [c](IShape* s) { s->SetOutlineColor(c); });
                cmd.Execute();
            });
        btn->SetFillColor(c);
        btn->SetOutlineMode(true);
        m_buttons.push_back(std::move(btn));
    }

    const float fillPositions[] = {POS_FILL_COLOR_1, POS_FILL_COLOR_2, POS_FILL_COLOR_3, POS_FILL_COLOR_4, POS_FILL_COLOR_5};

    for (int i = 0; i < 5; ++i)
    {
        sf::Color c = PaletteColor(i);

        auto btn = std::make_unique<Button>(
            sf::FloatRect({fillPositions[i], Y}, {SIZE, SIZE}),
            "",
            [this, c]() {
                const auto& sel = m_editor.GetSelected();
                if (sel.empty()) return;
                ModifyShapesCommand cmd(sel, [c](IShape* s) { s->SetFillColor(c); });
                cmd.Execute();
            });
        btn->SetFillColor(c);
        m_buttons.push_back(std::move(btn));
    }

    auto addThickness = [this, &add](float x, float t, const std::string& label) {
        add(x, label, ThickColor(), [this, t]() {
            const auto& sel = m_editor.GetSelected();
            if (sel.empty()) return;
            ModifyShapesCommand cmd(sel, [t](IShape* s) { s->SetOutlineThickness(t); });
            cmd.Execute();
        });
    };

    addThickness(POS_THICK_1, Config::THICKNESS_THIN,   "1");
    addThickness(POS_THICK_2, Config::THICKNESS_MEDIUM, "3");
    addThickness(POS_THICK_3, Config::THICKNESS_THICK,  "5");
}

bool Toolbar::HandleEvent(const sf::Event& event)
{
    if (auto* p = event.getIf<sf::Event::MouseButtonPressed>())
    {
        if (p->position.y < Config::TOOLBAR_HEIGHT && p->button == sf::Mouse::Button::Left)
        {
            sf::Vector2f pos(p->position.x, p->position.y);
            for (auto& btn : m_buttons)
            {
                if (btn->Contains(pos)) { btn->Click(); return true; }
            }
            return true;
        }
    }

    if (m_tool) return m_tool->HandleEvent(event, m_editor);
    return false;
}

void Toolbar::Draw(sf::RenderWindow& window) const
{
    sf::RectangleShape bg({static_cast<float>(Config::WINDOW_WIDTH), Config::TOOLBAR_HEIGHT});
    bg.setFillColor(sf::Color(230, 230, 230));
    window.draw(bg);

    for (const auto& btn : m_buttons) btn->Draw(window);
}