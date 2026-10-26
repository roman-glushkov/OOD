#include "toolbar/ToolState.h"
#include "editor/Editor.h"
#include "memento/CanvasMemento.h"
#include "utils/ConfigToolbar.h"
#include <utility>

ToolState::ToolState(std::string name, bool isDragMode, PressAction onPressed)
    : m_name(std::move(name))
    , m_isDragMode(isDragMode)
    , m_onPressed(std::move(onPressed))
{
}

bool ToolState::HandleEvent(const sf::Event& event, Editor& editor)
{
    if (auto* mp = event.getIf<sf::Event::MouseButtonPressed>())
    {
        if (mp->button != sf::Mouse::Button::Left) return false;

        sf::Vector2f pos(
            static_cast<float>(mp->position.x),
            static_cast<float>(mp->position.y)
        );

        // --- Добавление фигуры ---
        if (m_creator)
        {
            auto snapshot = m_createSnapshot ? m_createSnapshot() : nullptr;
            auto shape = m_creator(pos);
            if (shape)
            {
                if (snapshot && m_saveSnapshot) m_saveSnapshot(std::move(snapshot));
                editor.AddShape(std::move(shape));
            }
            return true;
        }

        if (!m_onPressed) return false;

        bool shift = sf::Keyboard::isKeyPressed(sf::Keyboard::Key::LShift)
                  || sf::Keyboard::isKeyPressed(sf::Keyboard::Key::RShift);

        bool ok = m_onPressed(editor, pos, shift);

        if (m_isDragMode && ok)
        {
            m_isDragging = true;
            m_dragMoved = false;
            m_lastMousePos = pos;
            // Снимок создаём, но в историю пока НЕ кладём
            m_pendingSnapshot = m_createSnapshot ? m_createSnapshot() : nullptr;
        }
        return true;
    }

    if (auto* mm = event.getIf<sf::Event::MouseMoved>())
    {
        if (!m_isDragging) return false;
        sf::Vector2f pos(
            static_cast<float>(mm->position.x),
            static_cast<float>(mm->position.y)
        );
        float dx = pos.x - m_lastMousePos.x;
        float dy = pos.y - m_lastMousePos.y;
        if (dx != 0.0f || dy != 0.0f)
        {
            editor.MoveSelected(dx, dy);
            m_lastMousePos = pos;
            m_dragMoved = true;
        }
        return true;
    }

    if (auto* mr = event.getIf<sf::Event::MouseButtonReleased>())
    {
        if (mr->button != sf::Mouse::Button::Left) return false;

        if (m_isDragging)
        {
            m_isDragging = false;
            if (m_dragMoved && m_pendingSnapshot && m_saveSnapshot)
            {
                m_saveSnapshot(std::move(m_pendingSnapshot));
            }
            m_pendingSnapshot.reset();
            m_dragMoved = false;
        }
        return true;
    }

    return false;
}

std::string ToolState::GetName() const
{
    return m_name;
}

std::unique_ptr<ToolState> ToolState::CreateDrag()
{
    using namespace ConfigToolbar;
    return std::make_unique<ToolState>(
        TOOL_NAME_DRAG, true,
        [](Editor& editor, sf::Vector2f pos, bool shift) {
            return editor.SelectShapeAt(pos, shift);
        }
    );
}

std::unique_ptr<ToolState> ToolState::CreateFill()
{
    using namespace ConfigToolbar;
    return std::make_unique<ToolState>(
        TOOL_NAME_FILL, false,
        [](Editor& editor, sf::Vector2f pos, bool shift) {
            return editor.SelectShapeAt(pos, shift);
        }
    );
}

std::unique_ptr<ToolState> ToolState::CreateAddShape(std::string name, Creator creator)
{
    auto tool = std::make_unique<ToolState>(std::move(name), false, nullptr);
    tool->m_creator = std::move(creator);
    return tool;
}