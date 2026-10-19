#pragma once
#include "toolbar/ITool.h"
#include "core/IShape.h"
#include <functional>
#include <memory>
#include <string>

class CanvasMemento;

class ToolState : public ITool
{
public:
    using PressAction = std::function<bool(Editor&, sf::Vector2f, bool)>;
    using Creator = std::function<std::unique_ptr<IShape>(sf::Vector2f)>;
    using CreateSnapshot = std::function<std::unique_ptr<CanvasMemento>()>;
    using SaveSnapshot = std::function<void(std::unique_ptr<CanvasMemento>)>;

    ToolState(std::string name, bool isDragMode, PressAction onPressed);

    void SetSnapshotCallbacks(CreateSnapshot create, SaveSnapshot save)
    {
        m_createSnapshot = std::move(create);
        m_saveSnapshot = std::move(save);
    }

    void ResetDragState()
    {
        m_isDragging = false;
        m_dragMoved = false;
        m_pendingSnapshot.reset();
    }

    bool HandleEvent(const sf::Event& event, Editor& editor) override;
    std::string GetName() const override;

    static std::unique_ptr<ToolState> CreateDrag();
    static std::unique_ptr<ToolState> CreateFill();
    static std::unique_ptr<ToolState> CreateAddShape(std::string name, Creator creator);

private:
    std::string m_name;
    bool m_isDragMode;
    PressAction m_onPressed;
    Creator m_creator;
    CreateSnapshot m_createSnapshot;
    SaveSnapshot m_saveSnapshot;

    bool m_isDragging = false;
    bool m_dragMoved = false;
    sf::Vector2f m_lastMousePos;
    std::unique_ptr<CanvasMemento> m_pendingSnapshot;
};