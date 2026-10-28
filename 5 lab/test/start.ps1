g++ -std=c++17 -I../include `
    ../src/main.cpp `
    ../src/app/Application.cpp `
    ../src/editor/Editor.cpp `
    ../src/memento/CanvasMemento.cpp `
    ../src/memento/HistoryCaretaker.cpp `
    ../src/io/parse/ShapeFactory.cpp `
    ../src/io/parse/ShapeFormatter.cpp `
    ../src/io/parse/ShapeParser.cpp `
    ../src/shapes/CCircle.cpp `
    ../src/shapes/CompositeShape.cpp `
    ../src/shapes/CRectangle.cpp `
    ../src/shapes/CTriangle.cpp `
    ../src/toolbar/Button.cpp `
    ../src/toolbar/Toolbar.cpp `
    ../src/toolbar/ToolState.cpp `
    ../src/io/save/TextSaveStrategy.cpp `
    ../src/io/save/BinarySaveStrategy.cpp `
    ../src/io/save/BinarySaveVisitor.cpp `
    ../src/io/save/ShapeSaver.cpp `
    ../src/io/load/TriangleBuilder.cpp `
    ../src/io/load/RectangleBuilder.cpp `
    ../src/io/load/CircleBuilder.cpp `
    ../src/io/load/ShapeBuildDirector.cpp `
    ../src/io/load/ShapeLoader.cpp `
    ../src/io/load/TextShapeLoader.cpp `
    ../src/io/load/BinaryShapeLoader.cpp `
    ../src/io/save/TextSaveVisitor.cpp `
    -I"C:/msys64/ucrt64/include" `
    -L"C:/msys64/ucrt64/lib" `
    -lsfml-graphics -lsfml-window -lsfml-system `
    -o app.exe
$env:PATH = "C:\msys64\ucrt64\bin;" + $env:PATH
.\app.exe --draw