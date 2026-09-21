#include <iostream>
#include <fstream>
#include <vector>
#include <memory>
#include <string>
#include <algorithm>
#include <SFML/Graphics.hpp>

#include "../include/ShapeParser.h"
#include "../include/ShapeFactory.h"
#include "../include/CompositeShape.h"
#include "../utils/Config.h"
#include "../include/ShapeFormatter.h"

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
            auto data  = ShapeParser::Parse(line);
            auto shape = ShapeFactory::Create(data);
            if (shape) shapes.push_back(std::move(shape));
        }
    }

    std::ofstream out(Config::OUTPUT_FILE);
    for (const auto& shape : shapes) {
        out << ShapeFormatter::ToString(*shape) << std::endl;
    }

    std::cout << Config::MSG_SHAPES_PROCESSED << shapes.size() << std::endl;
    for (const auto& shape : shapes) {
        std::cout << ShapeFormatter::ToString(*shape) << std::endl;
    }

    if (showGraphics) {
        sf::RenderWindow window(
            sf::VideoMode({Config::WINDOW_WIDTH, Config::WINDOW_HEIGHT}),
            Config::WINDOW_TITLE);

        std::vector<IShape*> selected;

        auto isSelected = [&](IShape* shape) {
            return std::find(selected.begin(), selected.end(), shape) != selected.end();
        };

        auto selectOne = [&](IShape* shape) {
            if (!shape || isSelected(shape)) return;
            shape->SetSelected(true);
            selected.push_back(shape);
        };

        auto deselectOne = [&](IShape* shape) {
            shape->SetSelected(false);
            selected.erase(
                std::remove(selected.begin(), selected.end(), shape),
                selected.end());
        };

        auto clearSelection = [&]() {
            for (IShape* s : selected) s->SetSelected(false);
            selected.clear();
        };

        auto findShapeAt = [&](const sf::Vector2f& pos) -> IShape* {
            for (auto it = shapes.rbegin(); it != shapes.rend(); ++it) {
                if ((*it)->Contains(pos)) return it->get();
            }
            return nullptr;
        };

        bool dragging = false;
        sf::Vector2f lastMouse;

        while (window.isOpen()) {
            while (auto event = window.pollEvent()) {
                if (event->is<sf::Event::Closed>()) {
                    window.close();
                }

                // ---- клавиатура ----
                if (const auto* key = event->getIf<sf::Event::KeyPressed>()) {
                    bool ctrl = sf::Keyboard::isKeyPressed(sf::Keyboard::Key::LControl)
                             || sf::Keyboard::isKeyPressed(sf::Keyboard::Key::RControl);

                    if (ctrl && key->code == sf::Keyboard::Key::G) {
                        if (selected.size() >= 2) {
                            std::vector<std::unique_ptr<IShape>> children;

                            for (auto it = shapes.begin(); it != shapes.end(); ) {
                                if (isSelected(it->get())) {
                                    children.push_back(std::move(*it));
                                    it = shapes.erase(it);
                                } else {
                                    ++it;
                                }
                            }

                            auto composite = std::make_unique<CompositeShape>();
                            for (auto& c : children) composite->Add(std::move(c));
                            IShape* compositePtr = composite.get();
                            shapes.push_back(std::move(composite));

                            clearSelection();
                            selectOne(compositePtr);
                        }
                    }

                    if (ctrl && key->code == sf::Keyboard::Key::U) {
                        std::vector<std::unique_ptr<IShape>> released;

                        for (auto it = shapes.begin(); it != shapes.end(); ) {
                            if (!isSelected(it->get())) { ++it; continue; }

                            if (auto* composite = dynamic_cast<CompositeShape*>(it->get())) {
                                auto kids = composite->Release();
                                for (auto& k : kids) {
                                    k->SetSelected(false);
                                    released.push_back(std::move(k));
                                }
                                it = shapes.erase(it);
                            } else {
                                ++it;
                            }
                        }

                        selected.clear();

                        for (auto& r : released) {
                            IShape* raw = r.get();
                            shapes.push_back(std::move(r));
                            selectOne(raw);
                        }
                    }
                }

                // ---- мышь: нажатие ----
                if (const auto* mouse = event->getIf<sf::Event::MouseButtonPressed>()) {
                    if (mouse->button == sf::Mouse::Button::Left) {
                        sf::Vector2f pos(
                            static_cast<float>(mouse->position.x),
                            static_cast<float>(mouse->position.y)
                        );

                        IShape* hit = findShapeAt(pos);

                        bool shift = sf::Keyboard::isKeyPressed(sf::Keyboard::Key::LShift)
                                  || sf::Keyboard::isKeyPressed(sf::Keyboard::Key::RShift);

                        if (shift) {
                            if (hit) {
                                if (isSelected(hit)) deselectOne(hit);
                                else                selectOne(hit);
                            }
                        } else {
                            if (!hit || !isSelected(hit)) {
                                clearSelection();
                                if (hit) selectOne(hit);
                            }
                        }

                        if (hit && isSelected(hit)) {
                            dragging = true;
                            lastMouse = pos;
                        }
                    }
                }

                // ---- мышь: движение ----
                if (const auto* move = event->getIf<sf::Event::MouseMoved>()) {
                    if (dragging) {
                        sf::Vector2f pos(
                            static_cast<float>(move->position.x),
                            static_cast<float>(move->position.y)
                        );
                        float dx = pos.x - lastMouse.x;
                        float dy = pos.y - lastMouse.y;

                        for (IShape* s : selected) {
                            s->Move(dx, dy);
                        }

                        lastMouse = pos;
                    }
                }

                // ---- мышь: отпускание ----
                if (const auto* rel = event->getIf<sf::Event::MouseButtonReleased>()) {
                    if (rel->button == sf::Mouse::Button::Left) {
                        dragging = false;
                    }
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