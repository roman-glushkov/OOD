#pragma once
#include <string>

namespace Config
{
    const double PI = 3.141592653589793;

    const double DEFAULT_COORDINATE = 0.0;
    const double DEFAULT_RADIUS     = 0.0;
    const double FACTOR_TWO         = 2.0;
    const double AREA_DIVISOR       = 2.0;

    const int PRECISION = 2;

    const std::string TYPE_TRIANGLE  = "TRIANGLE";
    const std::string TYPE_RECTANGLE = "RECTANGLE";
    const std::string TYPE_CIRCLE    = "CIRCLE";

    const char PARAM_SEPARATOR     = ';';
    const char COORD_SEPARATOR     = ',';
    const char PARAM_ASSIGN        = '=';
    const std::string PREFIX_TRIANGLE  = "TRIANGLE:";
    const std::string PREFIX_RECTANGLE = "RECTANGLE:";
    const std::string PREFIX_CIRCLE    = "CIRCLE:";
    const std::string PARAM_P1 = "P1";
    const std::string PARAM_P2 = "P2";
    const std::string PARAM_P3 = "P3";
    const std::string PARAM_C  = "C";
    const std::string PARAM_R  = "R";

    const std::string LABEL_PERIMETER = "P=";
    const std::string LABEL_AREA      = "S=";
    const std::string LABEL_SEPARATOR = ": ";
    const std::string VALUE_SEPARATOR = "; ";

    const int TRIANGLE_FILL_R = 100, TRIANGLE_FILL_G = 255, TRIANGLE_FILL_B = 100, TRIANGLE_FILL_A = 180;
    const int TRIANGLE_OUT_R  =   0, TRIANGLE_OUT_G  = 150, TRIANGLE_OUT_B  =   0;

    const int RECT_FILL_R = 255, RECT_FILL_G = 100, RECT_FILL_B = 100, RECT_FILL_A = 180;
    const int RECT_OUT_R  = 150, RECT_OUT_G  =   0, RECT_OUT_B  =   0;

    const int CIRCLE_FILL_R = 100, CIRCLE_FILL_G = 200, CIRCLE_FILL_B = 255, CIRCLE_FILL_A = 180;
    const int CIRCLE_OUT_R  =   0, CIRCLE_OUT_G  = 100, CIRCLE_OUT_B  = 200;

    const int SELECTED_R = 0, SELECTED_G = 255, SELECTED_B = 0;   
    const float SELECTED_THICKNESS_FACTOR = 2.0f;

    const float OUTLINE_THICKNESS  = 2.0f;
    const int   CIRCLE_POINT_COUNT = 100;

    const unsigned WINDOW_WIDTH  = 800;
    const unsigned WINDOW_HEIGHT = 600;
    const std::string WINDOW_TITLE = "Geometry Visualizer";

    const std::string INPUT_FILE  = "input.txt";
    const std::string OUTPUT_FILE = "output.txt";
    const std::string ARG_DRAW    = "--draw";
    const std::string MSG_SHAPES_PROCESSED = "Shapes processed: ";
}