#include "toolbar/Toolbar.h"
#include "editor/Editor.h"
#include "shapes/CCircle.h"
#include "shapes/CRectangle.h"
#include "shapes/CTriangle.h"
#include "toolbar/ToolState.h"
#include "utils/Config.h"
#include "utils/ConfigToolbar.h"
#include "visitors/SetFillColorVisitor.h"
#include "visitors/SetOutlineColorVisitor.h"
#include "visitors/SetThicknessVisitor.h"
#include "memento/CanvasMemento.h"
#include <functional>
#include <utility>

Toolbar::Toolbar(Editor& editor)
    : m_editor(editor)
{
    BuildButtons();
    SetTool(ToolState::CreateDrag());
}

void Toolbar::SetTool(std::unique_ptr<ToolState> tool)
{
    tool->SetSnapshotCallbacks(
        [this]() {
            return std::make_unique<CanvasMemento>(m_editor.GetShapesCopy());
        },
        [this](std::unique_ptr<CanvasMemento> memento) {
            m_history.Save(std::move(memento));
        }
    );
    m_tool = std::move(tool);
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

    add(POS_DRAG, LABEL_DRAG, DragColor(), [this]() {
        SetTool(ToolState::CreateDrag());
        m_isFillMode = false;
    });

    add(POS_FILL, LABEL_FILL, FillColor(), [this]() {
        SetTool(ToolState::CreateFill());
        m_isFillMode = true;
    });

    add(POS_ADD_TRI, LABEL_TRIANGLE, AddColor(), [this]() {
        SetTool(ToolState::CreateAddShape(TOOL_TRIANGLE, [](sf::Vector2f p) {
            return std::make_unique<CTriangle>(
                CPoint(p.x, p.y),
                CPoint(p.x + TRI_OFFSET_X1, p.y + TRI_OFFSET_Y1),
                CPoint(p.x + TRI_OFFSET_X2, p.y + TRI_OFFSET_Y2));
        }));
        m_isFillMode = false;
    });

    add(POS_ADD_RECT, LABEL_RECT, AddColor(), [this]() {
        SetTool(ToolState::CreateAddShape(TOOL_RECT, [](sf::Vector2f p) {
            return std::make_unique<CRectangle>(
                CPoint(p.x, p.y),
                CPoint(p.x + RECT_WIDTH, p.y + RECT_HEIGHT));
        }));
        m_isFillMode = false;
    });

    add(POS_ADD_CIRC, LABEL_CIRCLE, AddColor(), [this]() {
        SetTool(ToolState::CreateAddShape(TOOL_CIRCLE, [](sf::Vector2f p) {
            return std::make_unique<CCircle>(CPoint(p.x, p.y), CIRCLE_RADIUS);
        }));
        m_isFillMode = false;
    });

    const float outlinePositions[] = {POS_COLOR_1, POS_COLOR_2, POS_COLOR_3, POS_COLOR_4, POS_COLOR_5};
    for (int i = 0; i < PALETTE_SIZE; ++i)
    {
        sf::Color c = PaletteColor(i);
        auto btn = std::make_unique<Button>(
            sf::FloatRect({outlinePositions[i], Y}, {SIZE, SIZE}), LABEL_EMPTY,
            [this, c]() {
                if (!m_isFillMode) return;
                const auto& sel = m_editor.GetSelected();
                if (sel.empty()) return;

                m_history.Save(std::make_unique<CanvasMemento>(m_editor.GetShapesCopy()));

                SetOutlineColorVisitor visitor(c);
                for (IShape* s : sel) s->Accept(visitor);
            });
        btn->SetFillColor(c);
        btn->SetOutlineMode(true);
        m_buttons.push_back(std::move(btn));
    }

    const float fillPositions[] = {POS_FILL_COLOR_1, POS_FILL_COLOR_2, POS_FILL_COLOR_3, POS_FILL_COLOR_4, POS_FILL_COLOR_5};
    for (int i = 0; i < PALETTE_SIZE; ++i)
    {
        sf::Color c = PaletteColor(i);
        auto btn = std::make_unique<Button>(
            sf::FloatRect({fillPositions[i], Y}, {SIZE, SIZE}), LABEL_EMPTY,
            [this, c]() {
                if (!m_isFillMode) return;
                const auto& sel = m_editor.GetSelected();
                if (sel.empty()) return;

                m_history.Save(std::make_unique<CanvasMemento>(m_editor.GetShapesCopy()));

                SetFillColorVisitor visitor(c);
                for (IShape* s : sel) s->Accept(visitor);
            });
        btn->SetFillColor(c);
        m_buttons.push_back(std::move(btn));
    }

    auto addThickness = [this, &add](float x, float t, const std::string& label) {
        add(x, label, ThickColor(), [this, t]() {
            if (!m_isFillMode) return;
            const auto& sel = m_editor.GetSelected();
            if (sel.empty()) return;

            m_history.Save(std::make_unique<CanvasMemento>(m_editor.GetShapesCopy()));

            SetThicknessVisitor visitor(t);
            for (IShape* s : sel) s->Accept(visitor);
        });
    };

    addThickness(POS_THICK_1, Config::THICKNESS_THIN,   LABEL_THICK_1);
    addThickness(POS_THICK_2, Config::THICKNESS_MEDIUM, LABEL_THICK_3);
    addThickness(POS_THICK_3, Config::THICKNESS_THICK,  LABEL_THICK_5);
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
    using namespace ConfigToolbar;
    sf::RectangleShape bg({static_cast<float>(Config::WINDOW_WIDTH), Config::TOOLBAR_HEIGHT});
    bg.setFillColor(ToolbarBackground());
    window.draw(bg);
    for (const auto& btn : m_buttons) btn->Draw(window);
}

void Toolbar::Undo()
{
    auto current = std::make_unique<CanvasMemento>(m_editor.GetShapesCopy());
    auto memento = m_history.Undo(std::move(current));
    if (memento)
    {
        m_editor.SetShapes(memento->GetShapesCopy());
        if (m_tool) m_tool->ResetDragState();
    }
}

void Toolbar::Redo()
{
    auto current = std::make_unique<CanvasMemento>(m_editor.GetShapesCopy());
    auto memento = m_history.Redo(std::move(current));
    if (memento)
    {
        m_editor.SetShapes(memento->GetShapesCopy());
        if (m_tool) m_tool->ResetDragState();
    }
}
