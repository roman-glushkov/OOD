#pragma once
#include "CanvasMemento.h"
#include <vector>
#include <memory>

class HistoryCaretaker
{
public:
    void Save(std::unique_ptr<CanvasMemento> memento); 
    std::unique_ptr<CanvasMemento> Undo(std::unique_ptr<CanvasMemento> currentState);
    std::unique_ptr<CanvasMemento> Redo(std::unique_ptr<CanvasMemento> currentState);

private:
    std::vector<std::unique_ptr<CanvasMemento>> m_undoStack;
    std::vector<std::unique_ptr<CanvasMemento>> m_redoStack;
};