#pragma once
#include <vector>
#include <memory>
#include <SFML/Graphics.hpp>
#include "core/IShape.h"

class Editor 
{
public:
    explicit Editor(std::vector<std::unique_ptr<IShape>>& shapes);
    void Run();

private:
    std::vector<std::unique_ptr<IShape>>& m_shapes; 
    std::vector<IShape*> m_selected;                
    bool m_dragging = false;
    sf::Vector2f m_lastMouse; // прошлая позиция мыши

    void HandleEvent(const sf::Event& event); // разбор события
    void HandleKeyPressed(const sf::Event::KeyPressed& key);         
    void HandleMousePressed(const sf::Event::MouseButtonPressed& mouse); 
    void HandleMouseMoved(const sf::Event::MouseMoved& move);       
    void HandleMouseReleased(const sf::Event::MouseButtonReleased& release); // отпустили кнопку

    bool IsSelected(IShape* shape) const; 
    void SelectOne(IShape* shape);
    void DeselectOne(IShape* shape); 
    void ClearSelection(); 

    IShape* FindShapeAt(const sf::Vector2f& pos); // найти фигуру под курсором

    void GroupSelected();   // Ctrl+G
    void UngroupSelected(); // Ctrl+U
    
    void MoveSelected(float dx, float dy); // сдвинуть выделенные

    void DrawSelectionFrame(sf::RenderWindow& window) const;
};