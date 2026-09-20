#pragma once
#include <string>
#include <vector>
#include "../utils/Config.h"
#include "CPoint.h"

class ShapeParser {
public:
    struct ParsedData {
        std::string type;
        std::vector<CPoint> points;
        double radius = Config::DEFAULT_RADIUS;
    };

    static ParsedData Parse(const std::string& line);

private:
    static CPoint ParsePoint(const std::string& str);
    static std::string GetParamValue(const std::string& line, const std::string& paramName);
};