#include "app/Application.h"
#include "utils/Config.h"
#include <string>

int main(int argc, char* argv[]) 
{
    bool showGraphics = (argc > Config::MIN_ARGC_FOR_DRAW &&
                         std::string(argv[1]) == Config::ARG_DRAW);
    if (!showGraphics) return 0;

    Application::Instance().Run(Config::INPUT_FILE);
    return 0;
}