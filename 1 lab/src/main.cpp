#include <iostream>
#include <fstream>
#include <vector>
#include <memory>
#include <string>
#include <SFML/Graphics.hpp>

#include "../include/ShapeParser.h"
#include "../include/ShapeFactory.h"
#include "../utils/Config.h"

int main(int argc, char* argv[]) {
    bool showGraphics = false;

    if (argc > 1 && std::string(argv[1]) == Config::ARG_DRAW) {
        showGraphics = true;
    }

    std::ifstream file(Config::INPUT_FILE);
    std::vector<std::unique_ptr<IShape>> shapes;
    std::string line;

    while (std::getline(file, line)) {
        if (!line.empty()) {
            auto data = ShapeParser::Parse(line);
            auto shape = ShapeFactory::Create(data);
            if (shape) shapes.push_back(std::move(shape));
        }
    }

    std::ofstream out(Config::OUTPUT_FILE);
    for (const auto& shape : shapes) {
        out << shape->ToString() << std::endl;
    }

    std::cout << Config::MSG_SHAPES_PROCESSED << shapes.size() << std::endl;
    for (const auto& shape : shapes) {
        std::cout << shape->ToString() << std::endl;
    }

    if (showGraphics) {
        sf::RenderWindow window(
            sf::VideoMode({Config::WINDOW_WIDTH, Config::WINDOW_HEIGHT}),
            Config::WINDOW_TITLE);

        while (window.isOpen()) {
            while (auto event = window.pollEvent()) {
                if (event->is<sf::Event::Closed>()) {
                    window.close();
                }
            }

            window.clear(sf::Color::White);
            for (const auto& shape : shapes) {
                shape->Draw(window);
            }
            window.display();
        }
    }

    return 0;
}