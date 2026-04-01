#include "Application.h"

Application::Application(int screenWidth, int screenHeight, const char* title) :
    window(screenWidth, screenHeight, title),

    weightTCase(WIDTH-50-10, 10, 50, 10, 9),
    directionCheckbox(WIDTH-10-30, 40, 10, "Directed"),

    srcTCase(10, HEIGHT-10-20, 30, 10, 9),
    targetTCase(10+30+10, HEIGHT-10-20, 30, 10, 9),

    dijkstraButton(WIDTH/2-100-10, HEIGHT-20-15, 100, 20, "Dijkstra", 20),
    fordButton(WIDTH/2+10, HEIGHT-20-15, 100, 20, "Bellman-Ford", 13)
{
    // Window Init
    window.setMinSize(xMargin, yMargin);

    // Camera Init
    camera.target = { (float)screenWidth/2, (float)screenHeight/2 };
    camera.offset = { (float)screenWidth/2, (float)screenHeight/2 };
    camera.rotation = 0.0f;
    camera.zoom = 1.0f;

    // Textcases Init
    std::unordered_set<char> tempSet = {'-', '0', '1', '2', '3', '4', '5', '6', '7', '8', '9'};
    weightTCase.setValid(tempSet);
    weightTCase.setTitle("Weight");
    
    tempSet.erase('-');
    srcTCase.setValid(tempSet);
    srcTCase.setTitle("From");
    targetTCase.setValid(tempSet);
    targetTCase.setTitle("To");

    // First Scaling
    float xScale = (float)GetScreenWidth()/(float)WIDTH;
    float yScale = (float)GetScreenHeight()/(float)HEIGHT;

    xMargin = (WIDTH-70)*xScale;
    yMargin = (HEIGHT-50)*yScale;

    srcTCase.setScale(xScale, yScale);
    targetTCase.setScale(xScale, yScale);
    weightTCase.setScale(xScale, yScale);
    dijkstraButton.setScale(xScale, yScale);
    fordButton.setScale(xScale, yScale);
    directionCheckbox.setScale(xScale, yScale);
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
    // Check Margins
    int mouseX = GetMouseX();
    int mouseY = GetMouseY();
    bool mouseOnUI = (mouseX > xMargin || mouseY > yMargin);

    // Mouse related cords
    Vector2 pRaylib = GetScreenToWorld2D({(float)mouseX, (float)mouseY}, camera);
    Vec2 p = {(int)pRaylib.x, (int)pRaylib.y};

    // Outputs
    bool dijkstraB = dijkstraButton.pressed();
    bool fordB = fordButton.pressed();
    if (dijkstraB || fordB)
    {
        // Get the nodes
        std::string tempString = srcTCase.getText();
        int src = 0;
        if (tempString.empty()) src = 0;
        else src = std::stoi(tempString);
        tempString = targetTCase.getText();
        int target = 0;
        if (tempString.empty()) target = 0;
        else target = std::stoi(tempString);

        // Execute Algorithm
        unordered_map<int, pair<int,vector<int>>> dist;

        bool err;
        if (dijkstraB)
            dist = graph.dijkstra(src, &err);
        if (fordB)
            dist = graph.bellmanFord(src, &err);

        //Output
        ow = new OutputWindow(WIDTH, HEIGHT);
        if (!err)
        {
            std::vector<std::vector<int>> paths = graph.getPaths(dist, src, target);

            if (paths.size() != 0)
            {
                std::string output;
                for (const auto& path : paths)
                {
                    for (size_t i = 0; i < path.size(); ++i)
                    {
                        output += std::to_string(path[i]);
                        if (i != path.size() - 1)
                            output += "->";
                    }
                    output += "\n\n";
                }

                ow->setText("Weight: " + std::to_string(dist[target].first));
                ow->setText1(output);
            }
            else
            {
                ow->setError();
                ow->setText("The target node is unreachable or doesn't exist");
            }
        }
        else
        {
            ow->setError();
            ow->setText("Something went wrong,\ncheck your inputs and graph values");
        }
    }
    if (ow) ow->update();
    if (ow && !ow->isOpen()) { delete ow; ow = nullptr; }

    // Get every other type of input if not in output window
    if (!ow)
    {   
        // Inputs
        // Direction input
        directionCheckbox.event();
        // Weight input
        weightTCase.event(); 
        // Src and Target input
        srcTCase.event();
        targetTCase.event();

        // Modifying Graph
        if (!mouseOnUI)
        {
            // Adding Elements
            if (IsKeyReleased(KEY_N))
            {
                int n = nodes.addNode(p, NODE_RADIUS);
                if (n >= 0) graph.addNode(n);
            }
            if (IsMouseButtonReleased(0))
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
        }

        // Modifying view
        if (IsMouseButtonDown(MOUSE_BUTTON_LEFT))
        {
            Vector2 delta = GetMouseDelta();
            camera.target.x -= delta.x / camera.zoom;
            camera.target.y -= delta.y / camera.zoom;
        }
        float wheel = GetMouseWheelMove();
        if (wheel != 0)
        {
            camera.zoom += wheel * 0.1f;
            if (camera.zoom < 0.1f) camera.zoom = 0.1f;
            if (camera.zoom > 3.0f) camera.zoom = 3.0f;
        }
    }

    // Scaling
    if (IsWindowResized())
    {
        float xScale = (float)GetScreenWidth()/(float)WIDTH;
        float yScale = (float)GetScreenHeight()/(float)HEIGHT;

        xMargin = (WIDTH-70)*xScale;
        yMargin = (HEIGHT-50)*yScale;

        srcTCase.setScale(xScale, yScale);
        targetTCase.setScale(xScale, yScale);
        weightTCase.setScale(xScale, yScale);
        dijkstraButton.setScale(xScale, yScale);
        fordButton.setScale(xScale, yScale);
        directionCheckbox.setScale(xScale, yScale);
        if (ow) ow->setScale(xScale, yScale);
    }
}

void Application::Render()
{
    BeginDrawing();
    ClearBackground(WHITE);

    // Elements moving on the screen (graph elements)
    BeginMode2D(camera);

    for (auto &n : nodes.getNodes())
        Renderer::drawNode(n);
    for (auto &e : edges.getEdges())
        Renderer::drawEdge(e);

    

    EndMode2D();

    // Elements fixed on the screen
    Renderer::drawXMargin(yMargin, WIDTH*(float)GetScreenWidth()/(float)WIDTH);
    Renderer::drawYMargin(xMargin, HEIGHT*(float)GetScreenHeight()/(float)HEIGHT);
    weightTCase.render();
    srcTCase.render();
    targetTCase.render();
    dijkstraButton.render();
    fordButton.render();
    directionCheckbox.render();
    if (ow) ow->render();

    EndDrawing();
}