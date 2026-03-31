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

private:
    Window window;
    Camera2D camera;

    int xMargin = WIDTH-70;
    int yMargin = HEIGHT-50;

    TextCase weightTCase;
    TextCase srcTCase;
    TextCase targetTCase;
    Button dijkstraButton;
    Button fordButton;
    Checkbox directionCheckbox;

    NodeHelper nodes;
    EdgeHelper edges;

    Graph graph;
};