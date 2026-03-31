#include "EdgeHelper.h"

bool EdgeHelper::addDirectedEdge(Vec2 p, int weight, std::vector<Node>& nodes)    
{
    // Check if a node has been clicked
    Vec2 c = {-1, -1};
    for (auto &n : nodes)
    {
        if (n.disCenter(p) < n.getRadius())
        {
            c = {n.getX(), n.getY()};
            break;
        }
    }
    // No node clicked
    if (c.x == -1) return false;

    // If already in placing state (m_lastP has a value) add the edge 
    // else put in placing state
    if (placing)
    {
        // Nodes has to be different
        if (c.x == m_lastP.x && c.y == m_lastP.y) return false;

        // If already exists delete and add the new one
        for (auto it = m_edges.begin(); it != m_edges.end(); )
        {
            if (it->getP() == m_lastP && it->getP1() == c)
            {
                it = m_edges.erase(it);
            }
            else
            {
                ++it;
            }
        }

        // Add edge and reset
        m_edges.push_back(Edge({m_lastP.x, m_lastP.y}, {c.x, c.y}, weight, nodes));
        m_lastP = {-1, -1};
        placing = false;

        return true;
    }
    else
    {
        // Put in placing state by giving m_lastP a value
        m_lastP = {c.x, c.y};
        placing = true;

        return false;
    }
}

bool EdgeHelper::addUndirectedEdge(Vec2 p, int weight, std::vector<Node> &nodes)
{
    // Check if a node has been clicked
    Vec2 c = {-1, -1};
    for (auto &n : nodes)
    {
        if (n.disCenter(p) < n.getRadius())
        {
            c = {n.getX(), n.getY()};
            break;
        }
    }
    // No node clicked
    if (c.x == -1) return false;

    // If already in placing state (m_lastP has a value) add the edge 
    // else put in placing state
    if (placing)
    {
        // Nodes has to be different
        if (c.x == m_lastP.x && c.y == m_lastP.y) return false;

        // If already exists delete and add the new one
        for (auto it = m_edges.begin(); it != m_edges.end(); )
        {
            if (it->getP() == m_lastP && it->getP1() == c || it->getP() == c && it->getP1() == m_lastP)
            {
                it = m_edges.erase(it);
            }
            else
            {
                ++it;
            }
        }

        // Add edge and reset
        m_edges.push_back(Edge({m_lastP.x, m_lastP.y}, {c.x, c.y}, weight, nodes));
        m_edges.push_back(Edge({c.x, c.y}, {m_lastP.x, m_lastP.y}, weight, nodes));
        m_lastP = {-1, -1};
        placing = false;

        return true;
    }
    else
    {
        // Put in placing state by giving m_lastP a value
        m_lastP = {c.x, c.y};
        placing = true;

        return false;
    }
}

std::pair<int, int> EdgeHelper::deleteEdge(Vec2 p, int n)
{
    // Check and delete if an edge no longer exist (so no need of a return)
    for (auto it = m_edges.begin(); it != m_edges.end(); )
    {
        if (it->getNode() == n || it->getNode1() == n)
        {
            m_edges.erase(it);
        }
        else
            ++it;
    }

    // Check and delete from a click
    for (auto it = m_edges.begin(); it != m_edges.end(); )
    {
        Vec2 p0 = it->getP();
        Vec2 p1 = it->getP1();

        // Direction vector from p0 to p1
        Vec2f dir = {(float)(p1.x - p0.x), (float)(p1.y - p0.y)};
        
        // Normalize direction
        float length = sqrt(dir.x * dir.x + dir.y * dir.y);
        if (length != 0)
        {
            dir.x /= length;
            dir.y /= length;
        }

        
        Vec2f t = {(float)p1.x - dir.x * 30, (float)p1.y - dir.y * 30};
        if (distance(Vec2f(p), t) < 10)
        {
            std::pair<int, int> p(it->getNode(), it->getNode1());
            it = m_edges.erase(it);
            return p;
        }
        else
            ++it;
    }

    return std::pair<int, int>(-1, -1);
}

std::vector<Edge> &EdgeHelper::getEdges()
{
    return m_edges;
}