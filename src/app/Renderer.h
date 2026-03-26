#pragma once

#include <string>
#include <raylib.h>
#include "globals.h"
#include "Node.h"
#include "Edge.h"

class Renderer
{
public:
    static void drawNode(Node& n);
    static void drawEdge(Edge& e);
    static void drawXMargin(int y, int lenght);
    static void drawYMargin(int x, int lenght);
};