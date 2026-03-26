#include <cmath>
#include "Node.h"

Node::Node(Vec2 c, int radius, std::string title) :
    m_c(c), m_radius(radius), m_title(title)
{
}

float Node::disCenter(Vec2 p)
{
    int dx = p.x - m_c.x;
    int dy = p.y - m_c.y;

    return std::sqrt(dx * dx + dy * dy);
}

int Node::getRadius()
{
    return m_radius;
}

Vec2 Node::getCenter()
{
    return m_c;
}

int Node::getX()
{
    return m_c.x;
}

int Node::getY()
{
    return m_c.y;
}

std::string Node::getTitle()
{
    return m_title;
}