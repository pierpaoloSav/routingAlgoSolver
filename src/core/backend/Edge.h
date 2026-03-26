#pragma once

#include "vecMath.h"
#include "Node.h"

class Edge
{
public:
    Edge(Vec2 p, Vec2 p1, int weight, std::vector<Node>& nodes);

    Vec2 getP();
    Vec2 getP1();
    Vec2 getMidP();

    int getNode();
    int getNode1();

    int getWeight();
    
private:
    Vec2 m_p;
    Vec2 m_p1;
    Vec2 m_midP;
    int m_node;
    int m_node1;
    int m_weight;
};