#pragma once

#include "toolbar/ITool.h"
#include "core/IShape.h"

#include <functional>
#include <memory>
#include <string>

class ToolState : public ITool
{
public:
    using PressAction = std::function<bool(Editor&, sf::Vector2f, bool)>; // обработка нажатия лкм
    using Creator = std::function<std::unique_ptr<IShape>(sf::Vector2f)>; // фабрика фигур

    ToolState(std::string name, bool isDragMode, PressAction onPressed);

    bool HandleEvent(const sf::Event& event, Editor& editor) override; // обработка событий
    std::string GetName() const override; // имя инструмента

    // фабрики создание инструмента
    static std::unique_ptr<ITool> CreateDrag();
    static std::unique_ptr<ITool> CreateFill(sf::Color color);
    static std::unique_ptr<ITool> CreateAddShape(std::string name, Creator creator);

private:
    std::string m_name;
    bool m_isDragMode;
    PressAction m_onPressed;
    bool m_isDragging = false;
    sf::Vector2f m_lastMousePos;
};