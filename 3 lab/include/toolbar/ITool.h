#pragma once

#include <SFML/Graphics.hpp>
#include <string>

class Editor;

class ITool
{
public:
    virtual ~ITool() = default;
    virtual bool HandleEvent(const sf::Event& event, Editor& editor) = 0;
    virtual std::string GetName() const = 0;
};
