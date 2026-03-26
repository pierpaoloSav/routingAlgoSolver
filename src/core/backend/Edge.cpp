#include "Edge.h"

Edge::Edge(Vec2 p, Vec2 p1, int weight, std::vector<Node>& nodes) :
    m_p(p), m_p1(p1), m_weight(weight), m_midP({(p.x+p1.x)/2, (p.y+p1.y)/2})
{
    // Init nodes
    m_node = -1;
    m_node1 = -1;
    for (Node n : nodes)
    {
        if (n.getX() == p.x && n.getY() == p.y)
        {
            m_node = std::stoi(n.getTitle());
        }
        
        if (n.getX() == p1.x && n.getY() == p1.y)
        {
            m_node1 = std::stoi(n.getTitle());
        }
    }
}

Vec2 Edge::getP()
{
    return m_p;
}

Vec2 Edge::getP1()
{
    return m_p1;
}

Vec2 Edge::getMidP()
{
    return m_midP;
}

int Edge::getNode()
{
    return m_node;
}

int Edge::getNode1()
{
    return m_node1;
}

int Edge::getWeight()
{
    return m_weight;
}