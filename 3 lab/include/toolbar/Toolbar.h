#pragma once
#include "toolbar/Button.h"
#include "toolbar/ITool.h"
#include <memory>
#include <vector>
#include <SFML/Graphics.hpp>
#include "utils/ConfigToolbar.h"

class Editor;

class Toolbar
{
public:
    explicit Toolbar(Editor& editor);
    bool HandleEvent(const sf::Event& event); // обработать событие
    void Draw(sf::RenderWindow& window) const;// нарисовать
    bool m_isFillMode = false;

private:
    void BuildButtons();// создать кнопки

    Editor& m_editor;
    std::unique_ptr<ITool> m_tool;                    
    std::vector<std::unique_ptr<Button>> m_buttons;  
};