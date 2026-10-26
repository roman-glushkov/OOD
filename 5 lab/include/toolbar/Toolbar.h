#pragma once
#include "toolbar/Button.h"
#include "toolbar/ToolState.h"
#include "memento/HistoryCaretaker.h"
#include <memory>
#include <vector>
#include <SFML/Graphics.hpp>
#include "utils/ConfigToolbar.h"

class Editor;

class Toolbar
{
public:
    explicit Toolbar(Editor& editor);
    bool HandleEvent(const sf::Event& event);
    void Draw(sf::RenderWindow& window) const;

    void Undo();
    void Redo();

    bool m_isFillMode = false;

private:
    void BuildButtons();
    void SetTool(std::unique_ptr<ToolState> tool);

    Editor& m_editor;
    std::unique_ptr<ToolState> m_tool;
    std::vector<std::unique_ptr<Button>> m_buttons;
    HistoryCaretaker m_history;
};