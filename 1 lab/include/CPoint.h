#pragma once
#include "../utils/Config.h"

struct CPoint 
{
    double x;
    double y;

    CPoint(double x = Config::DEFAULT_COORDINATE, double y = Config::DEFAULT_COORDINATE)
        : x(x), y(y) {}
};