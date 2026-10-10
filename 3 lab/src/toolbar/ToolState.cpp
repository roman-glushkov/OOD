#include "toolbar/ToolState.h"

#include "commands/AddShapeCommand.h"
#include "commands/ModifyShapesCommand.h"
#include "editor/Editor.h"

#include <utility>
#include <vector>

ToolState::ToolState(std::string name, bool isDragMode, PressAction onPressed)
    : m_name(std::move(name))
    , m_isDragMode(isDragMode)
    , m_onPressed(std::move(onPressed))
{
}

bool ToolState::HandleEvent(const sf::Event& event, Editor& editor)
{
    if (auto* mousePressed = event.getIf<sf::Event::MouseButtonPressed>())
    {
        if (mousePressed->button != sf::Mouse::Button::Left || !m_onPressed)
        {
            return false;
        }

        bool shift = sf::Keyboard::isKeyPressed(sf::Keyboard::Key::LShift)
                  || sf::Keyboard::isKeyPressed(sf::Keyboard::Key::RShift);

        sf::Vector2f pos(
            static_cast<float>(mousePressed->position.x),
            static_cast<float>(mousePressed->position.y)
        );

        bool ok = m_onPressed(editor, pos, shift);

        if (m_isDragMode && ok)
        {
            m_isDragging = true;
            m_lastMousePos = pos;
        }

        return true;
    }

    if (auto* mouseMoved = event.getIf<sf::Event::MouseMoved>())
    {
        if (!m_isDragging)
        {
            return false;
        }

        sf::Vector2f pos(
            static_cast<float>(mouseMoved->position.x),
            static_cast<float>(mouseMoved->position.y)
        );

        editor.MoveSelected(
            pos.x - m_lastMousePos.x,
            pos.y - m_lastMousePos.y
        );

        m_lastMousePos = pos;
        return true;
    }

    if (auto* mouseReleased = event.getIf<sf::Event::MouseButtonReleased>())
    {
        if (mouseReleased->button != sf::Mouse::Button::Left)
        {
            return false;
        }

        m_isDragging = false;
        return true;
    }

    return false;
}

std::string ToolState::GetName() const
{
    return m_name;
}

std::unique_ptr<ITool> ToolState::CreateDrag()
{
    return std::make_unique<ToolState>(
        "Drag",
        true,
        [](Editor& editor, sf::Vector2f pos, bool shift)
        {
            return editor.SelectShapeAt(pos, shift);
        }
    );
}

std::unique_ptr<ITool> ToolState::CreateFill(sf::Color color)
{
    return std::make_unique<ToolState>(
        "Fill",
        false,
        [color](Editor& editor, sf::Vector2f pos, bool)
        {
            IShape* hit = editor.GetShapeAt(pos);
            if (!hit) return false;

            std::vector<IShape*> target = {hit};
            ModifyShapesCommand cmd(
                target,
                [color](IShape* s) { s->SetFillColor(color); }
            );
            cmd.Execute();
            return true;
        }
    );
}

std::unique_ptr<ITool> ToolState::CreateAddShape(std::string name, Creator creator)
{
    return std::make_unique<ToolState>(
        std::move(name),
        false,
        [creator = std::move(creator)](Editor& editor, sf::Vector2f pos, bool)
        {
            auto shape = creator(pos);
            if (!shape) return false;

            AddShapeCommand cmd(editor.GetShapes(), std::move(shape));
            cmd.Execute();
            return true;
        }
    );
}