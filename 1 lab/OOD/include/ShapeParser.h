// ShapeParser.h
#pragma once
#include <string>
#include <vector>     // ← ОБЯЗАТЕЛЬНО!
#include "CPoint.h"

class ShapeParser {
public:
    struct ParsedData {
        std::string type;
        std::vector<CPoint> points;
        double radius = 0.0;
    };
    
    static ParsedData Parse(const std::string& line);
    
private:
    static CPoint ParsePoint(const std::string& str);
    static std::string GetParamValue(const std::string& line, const std::string& paramName);
};