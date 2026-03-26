#include "Application.h"

Application::Application(int screenWidth, int screenHeight, const char* title) :
    window(screenWidth, screenHeight, title),
    weightTCase(WIDTH-30-50/2, 10, 50, 10, 5),
    dijkstraButton(WIDTH/2-100-10, HEIGHT-20-10, 100, 20, "Dijkstra", 20),
    fordButton(WIDTH/2+10, HEIGHT-20-10, 100, 20, "Bellman-Ford", 13),
    directionCheckbox(WIDTH-30-10/2, 40, 10, "Directed")
{
    // Window Init
    window.setMinSize(xMargin, yMargin);

    // First Scaling
    {
        float xScale = (float)GetScreenWidth()/(float)WIDTH;
        float yScale = (float)GetScreenHeight()/(float)HEIGHT;

        xMargin = (WIDTH-70)*xScale;
        yMargin = (HEIGHT-50)*yScale;

        dijkstraButton.setScale(xScale, yScale);
        fordButton.setScale(xScale, yScale);
        directionCheckbox.setScale(xScale, yScale);
        weightTCase.setScale(xScale, yScale);
    }

    // Textcase Init
    std::unordered_set<char> tempSet = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9'};
    weightTCase.setValid(tempSet);
    weightTCase.setTitle("Weight");
}

Application::~Application()
{
}

void Application::run()
{
    while (window.isOpen())
    {
        this->Loop();
        this->Render();
    }
}

void Application::Loop()
{
    Vec2 p;
    p.x = GetMouseX();
    p.y = GetMouseY();

    // Direction input
    directionCheckbox.event();
    // Weight input
    weightTCase.event();

    // Check Margins
    if (p.x > xMargin || p.y > yMargin) goto skipInputs;
    // Adding Elements
    if (IsMouseButtonReleased(0))
    {
        nodes.addNode(p, NODE_RADIUS);
    }
    if (IsMouseButtonReleased(1))
    {
        // Get the weight from textcase
        std::string tempString = weightTCase.getText();
        int w = 0;
        if (tempString.empty()) w = 0;
        else w = std::stoi(tempString);

        if (directionCheckbox.getStatus())
        {
            // Adding the edge on frontend
            if (edges.addDirectedEdge(p, w, nodes.getNodes()))
            {
                // If an edge is added (so isn't in placing state or misscliks) add on backend
                graph.addDirectedEdge(edges.getEdges()[edges.getEdges().size()-1].getNode(),
                                      edges.getEdges()[edges.getEdges().size()-1].getNode1(),
                                      edges.getEdges()[edges.getEdges().size()-1].getWeight());
            }
        }
        else
        {
            // Adding the edge on frontend
            if (edges.addUndirectedEdge(p, w, nodes.getNodes()))
            {
                // If an edge is added (so isn't in placing state or misscliks) add on backend
                graph.addUndirectedEdge(edges.getEdges()[edges.getEdges().size()-1].getNode(),
                                        edges.getEdges()[edges.getEdges().size()-1].getNode1(),
                                        edges.getEdges()[edges.getEdges().size()-1].getWeight());
            }
        }
    }
    // Deleting elements
    if (IsKeyReleased(KEY_BACKSPACE))
    {  
        // Deleting a node from frontend
        int n = nodes.deleteNode(p);
        // Deleting the node from backend
        graph.deleteNode(n);

        // Deleting an edge from frontend
        std::pair<int, int> ns = edges.deleteEdge(p, n);
        // Deleting the edge from backend
        graph.deleteEdge(ns.first, ns.second);
    }

    skipInputs:
    // Scaling
    if (IsWindowResized())
    {
        float xScale = (float)GetScreenWidth()/(float)WIDTH;
        float yScale = (float)GetScreenHeight()/(float)HEIGHT;

        xMargin = (WIDTH-70)*xScale;
        yMargin = (HEIGHT-50)*yScale;

        dijkstraButton.setScale(xScale, yScale);
        fordButton.setScale(xScale, yScale);
        directionCheckbox.setScale(xScale, yScale);
        weightTCase.setScale(xScale, yScale);
    }
}

void Application::Render()
{
    BeginDrawing();
    ClearBackground(WHITE);

    // Graph elements render
    for (auto &n : nodes.getNodes())
    {
        Renderer::drawNode(n);
    }
    for (auto &e : edges.getEdges())
    {
        Renderer::drawEdge(e);
    }

    // UI render
    Renderer::drawXMargin(yMargin+NODE_RADIUS, WIDTH*(float)GetScreenWidth()/(float)WIDTH);
    Renderer::drawYMargin(xMargin+NODE_RADIUS, HEIGHT*(float)GetScreenHeight()/(float)HEIGHT);
    weightTCase.render();
    dijkstraButton.render();
    fordButton.render();
    directionCheckbox.render();

    EndDrawing();
}