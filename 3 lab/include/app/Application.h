#pragma once
#include <memory>
#include <string>
#include <vector>
#include <SFML/Graphics.hpp>
#include "core/IShape.h"
#include "editor/Editor.h"
#include "toolbar/Toolbar.h"

class Application 
{
public:
    static Application& Instance();

    void Run(const std::string& inputFile);

private:
    Application() = default;
    Application(const Application&) = delete;
    Application& operator=(const Application&) = delete;

    sf::RenderWindow m_window;
    std::vector<std::unique_ptr<IShape>> m_shapes;
    std::unique_ptr<Editor> m_editor;
    std::unique_ptr<Toolbar> m_toolbar;
};
