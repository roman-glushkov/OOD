#include "editor/Editor.h"

#include "shapes/CompositeShape.h"
#include "utils/Colors.h"
#include "utils/Config.h"

#include <algorithm>

Editor::Editor(std::vector<std::unique_ptr<IShape>>& shapes)
    : m_shapes(shapes)
{
}

void Editor::DrawSelectionFrame(sf::RenderWindow& window) const
{
    for (IShape* shape : m_selected)
    {
        sf::FloatRect bounds = shape->GetBounds();
        bounds.position.x -= Config::SELECTION_FRAME_PADDING;
        bounds.position.y -= Config::SELECTION_FRAME_PADDING;
        bounds.size.x += Config::SELECTION_FRAME_PADDING * 2;
        bounds.size.y += Config::SELECTION_FRAME_PADDING * 2;

        sf::RectangleShape frame;
        frame.setPosition(bounds.position);
        frame.setSize(bounds.size);
        frame.setFillColor(sf::Color::Transparent);
        frame.setOutlineColor(ShapeColors::SelectionFrameOutline());
        frame.setOutlineThickness(Config::SELECTION_FRAME_THICKNESS);
        window.draw(frame);

        const float markerSize = Config::SELECTION_MARKER_SIZE;
        sf::Vector2f corners[8] = {
            {bounds.position.x, bounds.position.y},
            {bounds.position.x + bounds.size.x / 2, bounds.position.y},
            {bounds.position.x + bounds.size.x, bounds.position.y},
            {bounds.position.x, bounds.position.y + bounds.size.y / 2},
            {bounds.position.x + bounds.size.x, bounds.position.y + bounds.size.y / 2},
            {bounds.position.x, bounds.position.y + bounds.size.y},
            {bounds.position.x + bounds.size.x / 2, bounds.position.y + bounds.size.y},
            {bounds.position.x + bounds.size.x, bounds.position.y + bounds.size.y}
        };

        for (const sf::Vector2f& corner : corners)
        {
            sf::RectangleShape marker({markerSize, markerSize});
            marker.setPosition({
                corner.x - markerSize / 2,
                corner.y - markerSize / 2
            });
            marker.setFillColor(ShapeColors::SelectionMarkerFill());
            marker.setOutlineColor(ShapeColors::SelectionMarkerOutline());
            marker.setOutlineThickness(Config::SELECTION_MARKER_THICKNESS);
            window.draw(marker);
        }
    }
}

bool Editor::SelectShapeAt(const sf::Vector2f& pos, bool additive)
{
    IShape* hit = GetShapeAt(pos);

    if (additive)
    {
        if (!hit)
        {
            return false;
        }

        if (IsSelected(hit))
        {
            DeselectOne(hit);
            return false;
        }

        SelectOne(hit);
        return true;
    }

    if (!hit || !IsSelected(hit))
    {
        ClearSelection();

        if (!hit)
        {
            return false;
        }

        SelectOne(hit);
    }

    return true;
}

void Editor::ClearSelection()
{
    for (IShape* shape : m_selected)
    {
        shape->SetSelected(false);
    }
    m_selected.clear();
}

void Editor::MoveSelected(float dx, float dy)
{
    for (IShape* shape : m_selected)
    {
        shape->Move(dx, dy);
    }
}

IShape* Editor::GetShapeAt(const sf::Vector2f& pos) const
{
    for (auto it = m_shapes.rbegin(); it != m_shapes.rend(); ++it)
    {
        if ((*it)->Contains(pos))
        {
            return it->get();
        }
    }
    return nullptr;
}

bool Editor::IsSelected(const IShape* shape) const
{
    return std::find(m_selected.begin(), m_selected.end(), shape) != m_selected.end();
}

void Editor::SelectOne(IShape* shape)
{
    if (!shape || IsSelected(shape))
    {
        return;
    }
    shape->SetSelected(true);
    m_selected.push_back(shape);
}

void Editor::DeselectOne(IShape* shape)
{
    if (!shape)
    {
        return;
    }
    shape->SetSelected(false);
    m_selected.erase(
        std::remove(m_selected.begin(), m_selected.end(), shape),
        m_selected.end()
    );
}

const std::vector<IShape*>& Editor::GetSelected() const
{
    return m_selected;
}

std::vector<std::unique_ptr<IShape>>& Editor::GetShapes()
{
    return m_shapes;
}

void Editor::GroupSelected()
{
    if (m_selected.size() < Config::MIN_SHAPES_FOR_GROUP)
    {
        return;
    }

    std::vector<std::unique_ptr<IShape>> children;
    for (auto it = m_shapes.begin(); it != m_shapes.end(); )
    {
        if (IsSelected(it->get()))
        {
            children.push_back(std::move(*it));
            it = m_shapes.erase(it);
        }
        else
        {
            ++it;
        }
    }

    auto composite = std::make_unique<CompositeShape>();
    for (auto& child : children)
    {
        composite->Add(std::move(child));
    }

    IShape* compositePtr = composite.get();
    m_shapes.push_back(std::move(composite));
    ClearSelection();
    SelectOne(compositePtr);
}

void Editor::UngroupSelected()
{
    std::vector<std::unique_ptr<IShape>> released;

    for (auto it = m_shapes.begin(); it != m_shapes.end(); )
    {
        if (!IsSelected(it->get()))
        {
            ++it;
            continue;
        }

        if (auto* composite = dynamic_cast<CompositeShape*>(it->get()))
        {
            auto children = composite->Release();
            for (auto& child : children)
            {
                child->SetSelected(false);
                released.push_back(std::move(child));
            }
            it = m_shapes.erase(it);
        }
        else
        {
            ++it;
        }
    }

    m_selected.clear();

    for (auto& shape : released)
    {
        IShape* raw = shape.get();
        m_shapes.push_back(std::move(shape));
        SelectOne(raw);
    }
}
