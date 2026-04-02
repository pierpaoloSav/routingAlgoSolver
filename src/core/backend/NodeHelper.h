#pragma once

#include <vector>
#include <queue>
#include <utility>
#include "vecMath.h"
#include "Node.h"

class NodeHelper
{
public:
    int addNode(Vec2 p, int radius);
    int deleteNode(Vec2 p);
    void clear();

    void createDefaultGraph(Vec2 start, int n, int radius);

    std::vector<Node>& getNodes();
    
private:
    std::vector<Node> m_nodes;
    std::priority_queue<int, std::vector<int>, std::greater<int>> m_deleted;
};