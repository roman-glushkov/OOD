g++ -std=c++17 -I../include `
    ../src/main.cpp `
    ../src/app/Application.cpp `
    ../src/commands/AddShapeCommand.cpp `
    ../src/commands/ModifyShapesCommand.cpp `
    ../src/editor/Editor.cpp `
    ../src/io/ShapeFactory.cpp `
    ../src/io/ShapeFormatter.cpp `
    ../src/io/ShapeParser.cpp `
    ../src/shapes/CCircle.cpp `
    ../src/shapes/CompositeShape.cpp `
    ../src/shapes/CRectangle.cpp `
    ../src/shapes/CTriangle.cpp `
    ../src/toolbar/Button.cpp `
    ../src/toolbar/Toolbar.cpp `
    ../src/toolbar/ToolState.cpp `
    -I"C:/msys64/ucrt64/include" `
    -L"C:/msys64/ucrt64/lib" `
    -lsfml-graphics -lsfml-window -lsfml-system `
    -o app.exe
$env:PATH = "C:\msys64\ucrt64\bin;" + $env:PATH
.\app.exe --draw