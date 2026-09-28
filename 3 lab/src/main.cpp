#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <memory>

#include "io/ShapeParser.h"
#include "io/ShapeFactory.h"
#include "io/ShapeFormatter.h"
#include "editor/Editor.h"
#include "utils/Config.h"

int main(int argc, char* argv[]) 
{
    bool showGraphics = (argc > Config::MIN_ARGC_FOR_DRAW &&
                         std::string(argv[1]) == Config::ARG_DRAW);

    std::ifstream file(Config::INPUT_FILE);
    std::vector<std::unique_ptr<IShape>> shapes;
    std::string line;

    while (std::getline(file, line)) 
    {
        if (line.empty()) continue;
        auto data  = ShapeParser::Parse(line);
        auto shape = ShapeFactory::Create(data);
        if (shape) shapes.push_back(std::move(shape));
    }

    std::ofstream out(Config::OUTPUT_FILE);
    std::cout << Config::MSG_SHAPES_PROCESSED << shapes.size() << std::endl;

    for (const auto& shape : shapes) 
    {
        std::string s = ShapeFormatter::ToString(*shape);
        out << s << std::endl;
        std::cout << s << std::endl;
    }

    if (showGraphics) 
    {
        Editor editor(shapes);
        editor.Run();
    }

    return 0;
}