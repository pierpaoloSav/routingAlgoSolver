#include "NodeHelper.h"

// Adds a node with p as the center
// if inside margin and there aren't any near nodes
int NodeHelper::addNode(Vec2 p, int radius)
{
    // Check near nodes
    bool add = true;
    for (auto &n : m_nodes)
    {
        if (n.disCenter(p) < n.getRadius()*4)
        {
            add = false;
            break;
        }
    }

    if (add)
    {
        int n;
        if (m_deleted.empty())
            n = m_nodes.size();
        else
        {
            n = m_deleted.top();
            m_deleted.pop();
        }

        m_nodes.push_back(Node(p, radius, std::to_string(n)));

        return n;
    }

    return -1;
}

// If p inside the node it is eliminated 
int NodeHelper::deleteNode(Vec2 p)
{
    for (auto it = m_nodes.begin(); it != m_nodes.end(); )
    {
        if (it->disCenter(p) < it->getRadius())
        {
            int deletedIndex = std::stoi(it->getTitle());
            m_deleted.push(deletedIndex);
            it = m_nodes.erase(it);
            return deletedIndex;
        }
        else
            ++it;
    }

    return -1;
}

void NodeHelper::clear()
{
    m_nodes.clear();
    m_deleted = std::priority_queue<int, std::vector<int>, std::greater<int>>();
}

std::vector<Node> &NodeHelper::getNodes()
{
    return m_nodes;
}

void NodeHelper::createDefaultGraph(Vec2 start, int n, int radius)
{
    int count = (n < 5) ? 5 : n;

    int spacing = 200;

    this->addNode(start, radius);

    int created = 1;
    int row = 0;
    int col = 1;

    while (created < count)
    {
        Vec2 pos(
            start.x + col * spacing,
            start.y + row * spacing
        );

        if (col == 1 && row%2 == 1)
        {
            pos.y += radius*3;
        }

        this->addNode(pos, radius);

        created++;
        col++;

        if (col > 2)
        {
            col = 0;
            row++;
        }
    }
}