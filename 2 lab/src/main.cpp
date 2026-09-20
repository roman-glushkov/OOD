#include <iostream>
#include <fstream>
#include <vector>
#include <memory>
#include <string>
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
    file.close();
    
    std::ofstream out("output.txt");
    for (const auto& shape : shapes) {
        out << shape->ToString() << std::endl;
    }
    out.close();
    
    std::cout << "Shapes processed: " << shapes.size() << std::endl;
    for (const auto& shape : shapes) {
        std::cout << shape->ToString() << std::endl;
    }
    
    if (showGraphics) {
        sf::RenderWindow window(sf::VideoMode({800, 600}), "Geometry Visualizer");
        
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