// main.cpp
#include <iostream>
#include <fstream>
#include <vector>
#include <memory>
#include <string>
#include "ShapeFactory.h"

int main(int argc, char* argv[]) {
    // Проверяем аргумент --draw
    bool showGraphics = false;
    if (argc > 1 && std::string(argv[1]) == "--draw") {
        showGraphics = true;
    }
    
    // Чтение файла
    std::ifstream file("input.txt");
    std::vector<std::shared_ptr<IShape>> shapes;
    std::string line;
    
    while (std::getline(file, line)) {
        if (!line.empty()) {
            shapes.push_back(ShapeFactory::Create(line));
        }
    }
    file.close();
    
    // Запись в файл
    std::ofstream out("output.txt");
    for (const auto& shape : shapes) {
        out << shape->ToString() << std::endl;
    }
    out.close();
    
    // Вывод в консоль
    std::cout << "Shapes processed: " << shapes.size() << std::endl;
    for (const auto& shape : shapes) {
        std::cout << shape->ToString() << std::endl;
    }
    
    // Визуализация (если указан --draw)
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