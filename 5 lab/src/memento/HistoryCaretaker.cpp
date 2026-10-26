#include "memento/HistoryCaretaker.h"

void HistoryCaretaker::Save(std::unique_ptr<CanvasMemento> memento)
{
    if (!memento) return;
    m_undoStack.push_back(std::move(memento));
    m_redoStack.clear();
}

std::unique_ptr<CanvasMemento> HistoryCaretaker::Undo(std::unique_ptr<CanvasMemento> currentState)
{
    if (m_undoStack.empty()) return nullptr;

    auto before = std::move(m_undoStack.back());
    m_undoStack.pop_back();

    m_redoStack.push_back(std::move(currentState));

    return before;
}

std::unique_ptr<CanvasMemento> HistoryCaretaker::Redo(std::unique_ptr<CanvasMemento> currentState)
{
    if (m_redoStack.empty()) return nullptr;

    auto after = std::move(m_redoStack.back());
    m_redoStack.pop_back();

    m_undoStack.push_back(std::move(currentState));

    return after;
}