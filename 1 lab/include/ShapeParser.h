#pragma once
#include <string>
#include <vector>     
#include "CPoint.h"
#include "../utils/Config.h"

class ShapeParser {
public:
    struct ParsedData { 
        std::string type; // тип фигуры
        std::vector<CPoint> points; // точки
        double radius = Config::DEFAULT_RADIUS; // радиус
    };
    
    static ParsedData Parse(const std::string& line); // разбираем строку и получаем данные фигуры
    
private:
    static CPoint ParsePoint(const std::string& str); // получаем точки
    static std::string GetParamValue(const std::string& line, const std::string& paramName); // получаем параметры
};