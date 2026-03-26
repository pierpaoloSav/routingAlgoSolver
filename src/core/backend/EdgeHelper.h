#pragma once

#include <vector>
#include"vecMath.h"
#include "Edge.h"
#include "Node.h"

class EdgeHelper
{
public:
    bool addDirectedEdge(Vec2 p, int weight, std::vector<Node>& nodes);
    bool addUndirectedEdge(Vec2 p, int weight, std::vector<Node>& nodes);
    
    std::pair<int, int> deleteEdge(Vec2 p, int n);

    std::vector<Edge>& getEdges();
    
private:
    std::vector<Edge> m_edges;
    Vec2 m_lastP = {-1, -1};
};