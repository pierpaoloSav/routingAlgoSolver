#pragma once

#include <raylib.h>
#include <vector>
#include "globals.h"
#include "Renderer.h"

#include "ui.h"
#include "graphHandling.h"

class Application
{
public:
    Application(int screenWidth, int screenHeight, const char* title);
    ~Application();

    void run();

private:
    void Loop();
    void Render();

    void randomGraph(int n, bool oneDirection);

private:
    Window window;
    Camera2D camera;

    OutputWindow *ow = nullptr;

    int xMargin = WIDTH-70;
    int yMargin = HEIGHT-50;

    TextCase weightTCase;
    Checkbox directionCheckbox;
    Button defButton1;
    Button defButton2;
    Button defButton3;
    
    TextCase srcTCase;
    TextCase targetTCase;
    Button dijkstraButton;
    Button fordButton;
    

    NodeHelper nodes;
    EdgeHelper edges;

    Graph graph;
};