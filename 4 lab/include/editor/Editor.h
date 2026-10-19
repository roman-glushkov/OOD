#pragma once
#include "core/IShape.h"
#include <memory>
#include <vector>
#include <SFML/Graphics.hpp>

class Editor
{
public:
    explicit Editor(std::vector<std::unique_ptr<IShape>>& shapes);
    void DrawSelectionFrame(sf::RenderWindow& window) const;
    void ClearSelection();
    void MoveSelected(float dx, float dy);
    void GroupSelected();
    void UngroupSelected();
    bool SelectShapeAt(const sf::Vector2f& pos, bool additive);
    IShape* GetShapeAt(const sf::Vector2f& pos) const;

    const std::vector<IShape*>& GetSelected() const;
    std::vector<std::unique_ptr<IShape>>& GetShapes();

    void AddShape(std::unique_ptr<IShape> shape);
    std::vector<std::unique_ptr<IShape>> GetShapesCopy() const;
    void SetShapes(std::vector<std::unique_ptr<IShape>> newShapes);

private:
    std::vector<std::unique_ptr<IShape>>& m_shapes;
    std::vector<IShape*> m_selected;
    bool IsSelected(const IShape* shape) const;
    void SelectOne(IShape* shape);
    void DeselectOne(IShape* shape);
};