#include <iostream>
#include <fstream>
#include <vector>
#include <memory>
#include <string>
#include <SFML/Graphics.hpp>

#include "../include/ShapeParser.h"
#include "../include/ShapeFactory.h"

int main(int argc, char* argv[]) {
    bool showGraphics = false;

    if (argc > 1 && std::string(argv[1]) == "--draw") {
        showGraphics = true;
    }

    std::ifstream file("input.txt");
    std::vector<std::unique_ptr<IShape>> shapes;
    std::string line;

    while (std::getline(file, line)) {
        if (!line.empty()) {
            auto data = ShapeParser::Parse(line);
            auto shape = ShapeFactory::Create(data);

            if (shape) {
                shapes.push_back(std::move(shape));
            }
        }
    }

    std::ofstream out("output.txt");
    for (const auto& shape : shapes) {
        out << shape->ToString() << std::endl;
    }

    std::cout << "Shapes processed: " << shapes.size() << std::endl;
    for (const auto& shape : shapes) {
        std::cout << shape->ToString() << std::endl;
    }

    if (showGraphics) {
        sf::RenderWindow window(sf::VideoMode({800, 600}), "Geometry Visualizer");

        IShape* selected = nullptr;

        while (window.isOpen()) {
            while (auto event = window.pollEvent()) {
                if (event->is<sf::Event::Closed>()) {
                    window.close();
                }

                if (const auto* mouse = event->getIf<sf::Event::MouseButtonPressed>()) {
                    if (mouse->button == sf::Mouse::Button::Left) {
                        sf::Vector2f pos(
                            static_cast<float>(mouse->position.x),
                            static_cast<float>(mouse->position.y)
                        );

                        selected = nullptr;
                        // идём с конца — верхняя фигура имеет приоритет
                        for (auto it = shapes.rbegin(); it != shapes.rend(); ++it) {
                            if ((*it)->Contains(pos)) {
                                selected = it->get();
                                break;
                            }
                        }
                    }
                }
            }

            window.clear(sf::Color::White);

            for (const auto& shape : shapes) {
                shape->SetSelected(shape.get() == selected);
                shape->Draw(window);
            }

            window.display();
        }
    }

    return 0;
}