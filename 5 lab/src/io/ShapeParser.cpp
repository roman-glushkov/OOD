#include "io/ShapeParser.h"
#include "utils/Config.h"
#include <sstream>

CPoint ShapeParser::ParsePoint(const std::string& str) 
{
    size_t comma = str.find(Config::COORD_SEPARATOR);
    double x = std::stod(str.substr(Config::FIRST_INDEX, comma));
    double y = std::stod(str.substr(comma + Config::COORD_OFFSET_AFTER_COMMA));
    return CPoint(x, y);
}

std::string ShapeParser::GetParamValue(const std::string& line, const std::string& paramName) 
{
    size_t pos = line.find(paramName + Config::PARAM_ASSIGN);
    size_t end = line.find(Config::PARAM_SEPARATOR, pos);
    if (end == std::string::npos) end = line.length();
    return line.substr(pos + paramName.length() + Config::PARAM_OFFSET_AFTER_NAME,
                       end - pos - paramName.length() - Config::PARAM_OFFSET_AFTER_NAME);
}

ShapeParser::ParsedData ShapeParser::Parse(const std::string& line) 
{
    ParsedData result;

    if (line.find(Config::PREFIX_TRIANGLE) == Config::FIRST_INDEX) 
    {
        result.type = Config::TYPE_TRIANGLE;
        result.points.push_back(ParsePoint(GetParamValue(line, Config::PARAM_P1)));
        result.points.push_back(ParsePoint(GetParamValue(line, Config::PARAM_P2)));
        result.points.push_back(ParsePoint(GetParamValue(line, Config::PARAM_P3)));
    }
    else if (line.find(Config::PREFIX_RECTANGLE) == Config::FIRST_INDEX) 
    {
        result.type = Config::TYPE_RECTANGLE;
        result.points.push_back(ParsePoint(GetParamValue(line, Config::PARAM_P1)));
        result.points.push_back(ParsePoint(GetParamValue(line, Config::PARAM_P2)));
    }
    else if (line.find(Config::PREFIX_CIRCLE) == Config::FIRST_INDEX) 
    {
        result.type = Config::TYPE_CIRCLE;
        result.points.push_back(ParsePoint(GetParamValue(line, Config::PARAM_C)));
        result.radius = std::stod(GetParamValue(line, Config::PARAM_R));
    }

    return result;
}
