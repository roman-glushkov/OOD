g++ -std=c++17 -I../include ../src/main.cpp ../src/CTriangle.cpp ../src/CRectangle.cpp ../src/CCircle.cpp ../src/ShapeParser.cpp ../src/ShapeFactory.cpp -I"C:/msys64/ucrt64/include" -L"C:/msys64/ucrt64/lib" -lsfml-graphics -lsfml-window -lsfml-system -o app.exe
$env:PATH = "C:\msys64\ucrt64\bin;" + $env:PATH
.\app.exe --draw