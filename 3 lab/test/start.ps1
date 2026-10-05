g++ -std=c++17 -I../include `
    ../src/main.cpp `
    ../src/shapes/CTriangle.cpp `
    ../src/shapes/CRectangle.cpp `
    ../src/shapes/CCircle.cpp `
    ../src/shapes/CompositeShape.cpp `
    ../src/io/ShapeParser.cpp `
    ../src/io/ShapeFactory.cpp `
    ../src/io/ShapeFormatter.cpp `
    ../src/editor/Editor.cpp `
    -I"C:/msys64/ucrt64/include" `
    -L"C:/msys64/ucrt64/lib" `
    -lsfml-graphics -lsfml-window -lsfml-system `
    -o app.exe
$env:PATH = "C:\msys64\ucrt64\bin;" + $env:PATH
.\app.exe --draw