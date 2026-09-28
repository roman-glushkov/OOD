#include "editor/Editor.h"
#include "shapes/CompositeShape.h"
#include "utils/Colors.h"
#include "utils/Config.h"
#include <algorithm>

Editor::Editor(std::vector<std::unique_ptr<IShape>>& shapes)
    : m_shapes(shapes) {}

void Editor::Run() 
{
    sf::RenderWindow window(
        sf::VideoMode({Config::WINDOW_WIDTH, Config::WINDOW_HEIGHT}),
        Config::WINDOW_TITLE);

    while (window.isOpen()) 
    {
        while (auto event = window.pollEvent()) 
        {
            if (event->is<sf::Event::Closed>()) window.close();
            HandleEvent(*event);
        }

        window.clear(sf::Color::White);
        for (const auto& s : m_shapes) s->Draw(window);
        DrawSelectionFrame(window);
        window.display();
    }
}

void Editor::DrawSelectionFrame(sf::RenderWindow& window) const 
{
    for (IShape* s : m_selected) 
    {
        sf::FloatRect b = s->GetBounds();

        b.position.x -= Config::SELECTION_FRAME_PADDING;
        b.position.y -= Config::SELECTION_FRAME_PADDING;
        b.size.x += Config::SELECTION_FRAME_PADDING * 2;
        b.size.y += Config::SELECTION_FRAME_PADDING * 2;

        sf::RectangleShape frame;
        frame.setPosition(b.position);
        frame.setSize(b.size);
        frame.setFillColor(sf::Color::Transparent);
        frame.setOutlineColor(ShapeColors::SelectionFrameOutline());
        frame.setOutlineThickness(Config::SELECTION_FRAME_THICKNESS);
        window.draw(frame);

        const float m = Config::SELECTION_MARKER_SIZE;
        sf::Vector2f corners[8] = {
            {b.position.x, b.position.y},
            {b.position.x + b.size.x / 2, b.position.y},
            {b.position.x + b.size.x, b.position.y},
            {b.position.x, b.position.y + b.size.y / 2},
            {b.position.x + b.size.x, b.position.y + b.size.y / 2},
            {b.position.x, b.position.y + b.size.y},
            {b.position.x + b.size.x / 2, b.position.y + b.size.y},
            {b.position.x + b.size.x, b.position.y + b.size.y}
        };

        for (int i = 0; i < 8; ++i) 
        {
            sf::RectangleShape marker({m, m});
            marker.setPosition({corners[i].x - m / 2, corners[i].y - m / 2});
            marker.setFillColor(ShapeColors::SelectionMarkerFill());
            marker.setOutlineColor(ShapeColors::SelectionMarkerOutline());
            marker.setOutlineThickness(Config::SELECTION_MARKER_THICKNESS);
            window.draw(marker);
        }
    }
}

void Editor::HandleEvent(const sf::Event& event) 
{
    if (auto* k = event.getIf<sf::Event::KeyPressed>())           HandleKeyPressed(*k);
    if (auto* m = event.getIf<sf::Event::MouseButtonPressed>())   HandleMousePressed(*m);
    if (auto* m = event.getIf<sf::Event::MouseMoved>())           HandleMouseMoved(*m);
    if (auto* m = event.getIf<sf::Event::MouseButtonReleased>())  HandleMouseReleased(*m);
}

void Editor::HandleKeyPressed(const sf::Event::KeyPressed& key) 
{
    bool ctrl = sf::Keyboard::isKeyPressed(sf::Keyboard::Key::LControl) 
             || sf::Keyboard::isKeyPressed(sf::Keyboard::Key::RControl);
    if (ctrl && key.code == sf::Keyboard::Key::G) GroupSelected();
    if (ctrl && key.code == sf::Keyboard::Key::U) UngroupSelected();
}

void Editor::HandleMousePressed(const sf::Event::MouseButtonPressed& mouse) 
{
    if (mouse.button != sf::Mouse::Button::Left) return;

    sf::Vector2f pos(static_cast<float>(mouse.position.x), static_cast<float>(mouse.position.y));

    IShape* hit = FindShapeAt(pos);

    bool shift = sf::Keyboard::isKeyPressed(sf::Keyboard::Key::LShift) || sf::Keyboard::isKeyPressed(sf::Keyboard::Key::RShift);

    if (shift) 
    {
        if (hit) { IsSelected(hit) ? DeselectOne(hit) : SelectOne(hit); }
    } 
    else 
    {
        if (!hit || !IsSelected(hit)) 
        {
            ClearSelection();
            if (hit) SelectOne(hit);
        }
    }

    if (hit && IsSelected(hit)) 
    {
        m_dragging = true;
        m_lastMouse = pos;
    }
}

void Editor::HandleMouseMoved(const sf::Event::MouseMoved& move) 
{
    if (!m_dragging) return;

    sf::Vector2f pos(static_cast<float>(move.position.x), static_cast<float>(move.position.y));

    MoveSelected(pos.x - m_lastMouse.x, pos.y - m_lastMouse.y);
    m_lastMouse = pos;
}

void Editor::HandleMouseReleased(const sf::Event::MouseButtonReleased& release) 
{
    if (release.button == sf::Mouse::Button::Left) m_dragging = false;
}

bool Editor::IsSelected(IShape* shape) const 
{
    return std::find(m_selected.begin(), m_selected.end(), shape) != m_selected.end();
}

void Editor::SelectOne(IShape* shape) 
{
    if (!shape || IsSelected(shape)) return;
    shape->SetSelected(true);
    m_selected.push_back(shape);
}

void Editor::DeselectOne(IShape* shape) 
{
    shape->SetSelected(false);
    m_selected.erase(
        std::remove(m_selected.begin(), m_selected.end(), shape),
        m_selected.end());
}

void Editor::ClearSelection() 
{
    for (IShape* s : m_selected) s->SetSelected(false);
    m_selected.clear();
}

IShape* Editor::FindShapeAt(const sf::Vector2f& pos) 
{
    for (auto it = m_shapes.rbegin(); it != m_shapes.rend(); ++it) 
    {
        if ((*it)->Contains(pos)) return it->get();
    }
    return nullptr;
}

void Editor::GroupSelected() 
{
    if (m_selected.size() < Config::MIN_SHAPES_FOR_GROUP) return;

    std::vector<std::unique_ptr<IShape>> children;
    for (auto it = m_shapes.begin(); it != m_shapes.end(); ) 
    {
        if (IsSelected(it->get())) 
        {
            children.push_back(std::move(*it));
            it = m_shapes.erase(it);
        } 
        else ++it;
    }

    auto composite = std::make_unique<CompositeShape>();
    for (auto& c : children) composite->Add(std::move(c));

    IShape* ptr = composite.get();
    m_shapes.push_back(std::move(composite));

    ClearSelection();
    SelectOne(ptr);
}

void Editor::UngroupSelected() 
{
    std::vector<std::unique_ptr<IShape>> released;

    for (auto it = m_shapes.begin(); it != m_shapes.end(); ) 
    {
        if (!IsSelected(it->get())) { ++it; continue; }

        if (auto* comp = dynamic_cast<CompositeShape*>(it->get())) 
        {
            auto kids = comp->Release();
            for (auto& k : kids) 
            { 
                k->SetSelected(false); 
                released.push_back(std::move(k)); 
            }
            it = m_shapes.erase(it);
        } 
        else ++it;
    }

    m_selected.clear();

    for (auto& r : released) 
    {
        IShape* raw = r.get();
        m_shapes.push_back(std::move(r));
        SelectOne(raw);
    }
}

void Editor::MoveSelected(float dx, float dy) 
{
    for (IShape* s : m_selected) s->Move(dx, dy);
}