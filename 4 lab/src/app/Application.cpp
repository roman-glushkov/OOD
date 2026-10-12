#include "app/Application.h"
#include "io/ShapeFactory.h"
#include "io/ShapeFormatter.h"
#include "io/ShapeParser.h"
#include "utils/Config.h"
#include <fstream>
#include <iostream>
#include <utility>

Application& Application::Instance()
{
    static Application instance;
    return instance;
}

void Application::Run(const std::string& inputFile)
{
    // чтение фигур
    std::ifstream file(inputFile);
    std::string line;

    while (std::getline(file, line))
    {
        if (line.empty()) continue;

        auto data = ShapeParser::Parse(line);
        auto shape = ShapeFactory::Create(data);
        if (shape)
        {
            m_shapes.push_back(std::move(shape));
        }
    }

    // вывод
    std::ofstream out(Config::OUTPUT_FILE);
    std::cout << Config::MSG_SHAPES_PROCESSED << m_shapes.size() << std::endl;

    for (const auto& shape : m_shapes)
    {
        std::string result = ShapeFormatter::ToString(*shape);
        out << result << std::endl;
        std::cout << result << std::endl;
    }

    // создание окна
    m_window.create(
        sf::VideoMode({Config::WINDOW_WIDTH, Config::WINDOW_HEIGHT}),
        Config::WINDOW_TITLE
    );

    // тулбар
    m_editor  = std::make_unique<Editor>(m_shapes);
    m_toolbar = std::make_unique<Toolbar>(*m_editor);

    while (m_window.isOpen())
    {
        while (auto event = m_window.pollEvent())
        {
            if (event->is<sf::Event::Closed>())
            {
                m_window.close();
                continue;
            }

            // горячие клавиши: Ctrl+G / Ctrl+U
            if (auto* keyPressed = event->getIf<sf::Event::KeyPressed>())
            {
                bool ctrl = sf::Keyboard::isKeyPressed(sf::Keyboard::Key::LControl)
                         || sf::Keyboard::isKeyPressed(sf::Keyboard::Key::RControl);

                if (ctrl && keyPressed->code == sf::Keyboard::Key::G)
                {
                    m_editor->GroupSelected();     
                    continue;
                }

                if (ctrl && keyPressed->code == sf::Keyboard::Key::U)
                {
                    m_editor->UngroupSelected();    
                    continue;
                }
            }

            m_toolbar->HandleEvent(*event);
        }

        m_window.clear(sf::Color::White);

        for (const auto& shape : m_shapes)
        {
            shape->Draw(m_window);
        }

        m_editor->DrawSelectionFrame(m_window);

        m_toolbar->Draw(m_window);

        m_window.display();
    }
}