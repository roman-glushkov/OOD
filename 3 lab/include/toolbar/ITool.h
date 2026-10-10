#pragma once

#include <SFML/Graphics.hpp>
#include <string>

class Editor;

// НОВОЕ: интерфейс инструмента (паттерн State, ЛР3)
class ITool
{
public:
    virtual ~ITool() = default;
    virtual bool HandleEvent(const sf::Event& event, Editor& editor) = 0;  // обработать событие
    virtual std::string GetName() const = 0;                                // имя инструмента
};