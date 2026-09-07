// main.cpp
#include <iostream>
#include <fstream>
#include <vector>
#include <memory>
#include <string>
#include <sstream>
#include "CTriangle.h"
#include "CRectangle.h"
#include "CCircle.h"

// Вспомогательная функция: парсит точку из строки "100,100"
CPoint ParsePoint(const std::string& str) {
    size_t comma = str.find(',');
    double x = std::stod(str.substr(0, comma));
    double y = std::stod(str.substr(comma + 1));
    return CPoint(x, y);
}

// Парсит строку типа "TRIANGLE: P1=100,100; P2=200,200; P3=150,150"
std::shared_ptr<IShape> ParseLine(const std::string& line) {
    if (line.find("TRIANGLE:") == 0) {
        size_t p1Pos = line.find("P1=");
        size_t p2Pos = line.find("P2=");
        size_t p3Pos = line.find("P3=");
        
        size_t p1End = line.find(';', p1Pos);
        size_t p2End = line.find(';', p2Pos);
        size_t p3End = line.find(';', p3Pos);
        if (p3End == std::string::npos) p3End = line.length();
        
        std::string p1Str = line.substr(p1Pos + 3, p1End - p1Pos - 3);
        std::string p2Str = line.substr(p2Pos + 3, p2End - p2Pos - 3);
        std::string p3Str = line.substr(p3Pos + 3, p3End - p3Pos - 3);
        
        CPoint p1 = ParsePoint(p1Str);
        CPoint p2 = ParsePoint(p2Str);
        CPoint p3 = ParsePoint(p3Str);
        
        return std::make_shared<CTriangle>(p1, p2, p3);
    }
    else if (line.find("RECTANGLE:") == 0) {
        size_t p1Pos = line.find("P1=");
        size_t p2Pos = line.find("P2=");
        
        size_t p1End = line.find(';', p1Pos);
        size_t p2End = line.find(';', p2Pos);
        if (p2End == std::string::npos) p2End = line.length();
        
        std::string p1Str = line.substr(p1Pos + 3, p1End - p1Pos - 3);
        std::string p2Str = line.substr(p2Pos + 3, p2End - p2Pos - 3);
        
        CPoint p1 = ParsePoint(p1Str);
        CPoint p2 = ParsePoint(p2Str);
        
        return std::make_shared<CRectangle>(p1, p2);
    }
    else if (line.find("CIRCLE:") == 0) {
        size_t cPos = line.find("C=");
        size_t rPos = line.find("R=");
        
        size_t cEnd = line.find(';', cPos);
        size_t rEnd = line.length();
        
        std::string cStr = line.substr(cPos + 2, cEnd - cPos - 2);
        std::string rStr = line.substr(rPos + 2);
        
        CPoint center = ParsePoint(cStr);
        double radius = std::stod(rStr);
        
        return std::make_shared<CCircle>(center, radius);
    }
    
    return nullptr;
}

int main(int argc, char* argv[]) {
    // Парсинг аргументов командной строки
    std::string inputFile = "input.txt";
    std::string outputFile = "output.txt";
    bool showGraphics = false;
    
    for (int i = 1; i < argc; i++) {
        std::string arg = argv[i];
        if (arg == "--draw" || arg == "-d") {
            showGraphics = true;
        } else if (arg == "-i" && i + 1 < argc) {
            inputFile = argv[++i];
        } else if (arg == "-o" && i + 1 < argc) {
            outputFile = argv[++i];
        }
    }
    
    // 1. Читаем input.txt
    std::ifstream inputFileStream(inputFile);
    if (!inputFileStream.is_open()) {
        std::cerr << "Failed to open " << inputFile << std::endl;
        return 1;
    }
    
    std::vector<std::shared_ptr<IShape>> shapes;
    std::string line;
    
    while (std::getline(inputFileStream, line)) {
        if (line.empty()) continue;
        
        auto shape = ParseLine(line);
        if (shape) {
            shapes.push_back(shape);
        }
    }
    inputFileStream.close();
    
    if (shapes.empty()) {
        std::cerr << "No shapes found in input file!" << std::endl;
        return 1;
    }
    
    // 2. Выводим в output.txt
    std::ofstream outputFileStream(outputFile);
    if (!outputFileStream.is_open()) {
        std::cerr << "Failed to create " << outputFile << std::endl;
        return 1;
    }
    
    for (const auto& shape : shapes) {
        outputFileStream << shape->ToString() << std::endl;
    }
    outputFileStream.close();
    
    // 3. Выводим в консоль для проверки
    std::cout << "Shapes processed: " << shapes.size() << std::endl;
    for (const auto& shape : shapes) {
        std::cout << shape->ToString() << std::endl;
    }
    
    // 4. Визуализация (если запрошена)
    if (showGraphics) {
        // SFML 3.0: VideoMode принимает Vector2u
        sf::RenderWindow window(sf::VideoMode({800, 600}), "Geometry Visualizer");
        
        // SFML 3.0: loadFromFile -> openFromFile
        sf::Font font;
        bool fontLoaded = font.openFromFile("arial.ttf");
        
        while (window.isOpen()) {
            // SFML 3.0: pollEvent() возвращает std::optional
            while (auto event = window.pollEvent()) {
                // SFML 3.0: проверка через is<>()
                if (event->is<sf::Event::Closed>()) {
                    window.close();
                }
            }
            
            window.clear(sf::Color::White);
            
            // Рисуем все фигуры
            for (const auto& shape : shapes) {
                shape->Draw(window);
            }
            
            // Показываем информацию о фигурах на экране
            if (fontLoaded) {
                float yPos = 10.0f;
                for (const auto& shape : shapes) {
                    sf::Text text(font, shape->ToString(), 14);
                    text.setFillColor(sf::Color::Black);
                    text.setPosition({10.0f, yPos});
                    window.draw(text);
                    yPos += 20.0f;
                }
            }
            
            window.display();
        }
    }
    
    return 0;
}