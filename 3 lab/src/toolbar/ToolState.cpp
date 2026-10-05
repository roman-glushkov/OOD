#include "toolbar/ToolState.h"

#include "commands/AddShapeCommand.h"
#include "commands/ModifyShapesCommand.h"
#include "editor/Editor.h"

#include <utility>
#include <vector>

ToolState::ToolState(
    std::string name,
    bool isDragMode,
    PressAction onPressed,
    MoveAction onMoved,
    ReleaseAction onReleased
)
    : m_name(std::move(name))
    , m_isDragMode(isDragMode)
    , m_onPressed(std::move(onPressed))
    , m_onMoved(std::move(onMoved))
    , m_onReleased(std::move(onReleased))
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

        bool actionSucceeded = m_onPressed(editor, pos, shift);

        if (m_isDragMode && actionSucceeded)
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

        if (m_isDragMode)
        {
            editor.MoveSelected(
                pos.x - m_lastMousePos.x,
                pos.y - m_lastMousePos.y
            );
        }
        else if (m_onMoved)
        {
            m_onMoved(editor, pos);
        }

        m_lastMousePos = pos;
        return true;
    }

    if (auto* mouseReleased = event.getIf<sf::Event::MouseButtonReleased>())
    {
        if (mouseReleased->button != sf::Mouse::Button::Left)
        {
            return false;
        }

        if (m_onReleased)
        {
            sf::Vector2f pos(
                static_cast<float>(mouseReleased->position.x),
                static_cast<float>(mouseReleased->position.y)
            );
            m_onReleased(editor, pos);
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
        },
        nullptr,
        nullptr
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
            if (!hit)
            {
                return false;
            }

            std::vector<IShape*> target = {hit};
            ModifyShapesCommand command(
                target,
                [color](IShape* shape)
                {
                    shape->SetFillColor(color);
                }
            );
            command.Execute();
            return true;
        },
        nullptr,
        nullptr
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
            if (!shape)
            {
                return false;
            }

            AddShapeCommand command(editor.GetShapes(), std::move(shape));
            command.Execute();
            return true;
        },
        nullptr,
        nullptr
    );
}
