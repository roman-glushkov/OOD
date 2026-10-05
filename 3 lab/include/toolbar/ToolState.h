#pragma once

#include "toolbar/ITool.h"
#include "core/IShape.h"

#include <functional>
#include <memory>
#include <string>

class ToolState : public ITool
{
public:
    using PressAction = std::function<bool(Editor&, sf::Vector2f, bool)>;
    using MoveAction = std::function<void(Editor&, sf::Vector2f)>;
    using ReleaseAction = std::function<void(Editor&, sf::Vector2f)>;

    ToolState(
        std::string name,
        bool isDragMode,
        PressAction onPressed,
        MoveAction onMoved,
        ReleaseAction onReleased
    );

    bool HandleEvent(const sf::Event& event, Editor& editor) override;
    std::string GetName() const override;

    static std::unique_ptr<ITool> CreateDrag();
    static std::unique_ptr<ITool> CreateFill(sf::Color color);

    using Creator = std::function<std::unique_ptr<IShape>(sf::Vector2f)>;
    static std::unique_ptr<ITool> CreateAddShape(std::string name, Creator creator);

private:
    std::string m_name;
    bool m_isDragMode;
    PressAction m_onPressed;
    MoveAction m_onMoved;
    ReleaseAction m_onReleased;
    bool m_isDragging = false;
    sf::Vector2f m_lastMousePos;
};
