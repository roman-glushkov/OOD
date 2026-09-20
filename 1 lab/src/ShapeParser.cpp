#include "../include/ShapeParser.h" 
#include <sstream>

// разбираем строку с координатами точки
CPoint ShapeParser::ParsePoint(const std::string& str) {
    size_t comma = str.find(Config::COORD_SEPARATOR);
    double x = std::stod(str.substr(0, comma));
    double y = std::stod(str.substr(comma + 1));
    return CPoint(x, y);
}

// получаем значение нужного параметра из строки
std::string ShapeParser::GetParamValue(const std::string& line, const std::string& paramName) {
    size_t pos = line.find(paramName + Config::PARAM_ASSIGN);
    size_t end = line.find(Config::PARAM_SEPARATOR, pos);
    if (end == std::string::npos) end = line.length();
    return line.substr(pos + paramName.length() + 1, end - pos - paramName.length() - 1);
}

// разбираем строку и заполняем данные фигуры
ShapeParser::ParsedData ShapeParser::Parse(const std::string& line) {
    ParsedData result;

    if (line.find(Config::PREFIX_TRIANGLE) == 0) {
        result.type = Config::TYPE_TRIANGLE;
        result.points.push_back(ParsePoint(GetParamValue(line, Config::PARAM_P1)));
        result.points.push_back(ParsePoint(GetParamValue(line, Config::PARAM_P2)));
        result.points.push_back(ParsePoint(GetParamValue(line, Config::PARAM_P3)));
    }
    else if (line.find(Config::PREFIX_RECTANGLE) == 0) {
        result.type = Config::TYPE_RECTANGLE;
        result.points.push_back(ParsePoint(GetParamValue(line, Config::PARAM_P1)));
        result.points.push_back(ParsePoint(GetParamValue(line, Config::PARAM_P2)));
    }
    else if (line.find(Config::PREFIX_CIRCLE) == 0) {
        result.type = Config::TYPE_CIRCLE;
        result.points.push_back(ParsePoint(GetParamValue(line, Config::PARAM_C)));
        result.radius = std::stod(GetParamValue(line, Config::PARAM_R));
    }

    return result;
}
