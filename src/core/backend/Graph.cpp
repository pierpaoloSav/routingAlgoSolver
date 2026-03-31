#include "Graph.h"

void Graph::addUndirectedEdge(int node, int node1, int weight)
{
    // Resize list
    if (node >= m_adj.size() || node1 >= m_adj.size())
    {
        m_adj.resize(max(node, node1)+1);
    }

    // If already exists delete and add the new one
    for (auto it = m_adj[node].begin(); it != m_adj[node].end(); ) {
        if (it->first == node1)
            it = m_adj[node].erase(it);
        else
            ++it;
    }
    for (auto it = m_adj[node1].begin(); it != m_adj[node1].end(); ) {
        if (it->first == node)
            it = m_adj[node1].erase(it);
        else
            ++it;
    }

    // Add edges
    m_adj[node].push_back({node1, weight});
    m_adj[node1].push_back({node, weight});    
}

void Graph::addDirectedEdge(int node, int node1, int weight)
{
   // Resize list
    if (node >= m_adj.size() || node1 >= m_adj.size())
    {
        m_adj.resize(max(node, node1)+1);
    }

    // If already exists delete and add the new one
    for (auto it = m_adj[node].begin(); it != m_adj[node].end(); ) {
        if (it->first == node1)
            it = m_adj[node].erase(it);
        else
            ++it;
    }

    // Add edges
    m_adj[node].push_back({node1, weight});
}

void Graph::deleteNode(int node)
{
    if (node < 0 || node >= m_adj.size()) return;

    // Delete all the edges from the node
    m_adj[node] = vector<pair<int,int>>();

    // Delete all the edges to the node from others
    for (size_t i = 0; i < m_adj.size(); i++) 
    {
        for (auto it = m_adj[i].begin(); it != m_adj[i].end(); ) 
        {
            if (it->first == node)
                it = m_adj[i].erase(it);
            else
                ++it;
        }
    }

    // Memory optimization
    while (m_adj.size() > 1 && m_adj.back().empty())
    {
        m_adj.pop_back();
    }
}

void Graph::deleteEdge(int node, int node1)
{
    if (node < 0 || node1 < 0) return;

    // Delete the edge
    for (auto it = m_adj[node].begin(); it != m_adj[node].end(); )
    {
        if (it->first == node1)
            it = m_adj[node].erase(it);
        else
            ++it;
    }

    // Memory optimization
    while (m_adj.size() > 1 && m_adj.back().empty())
    {
        m_adj.pop_back();
    }
}

void Graph::printAdj() {
    for (int i = 0; i < m_adj.size(); i++) 
    {
        cout << "Nodo " << i << " -> ";

        for (const auto& [v, peso] :m_adj[i]) 
        {
            cout << "(" << v << ", " << peso << ") ";
        }

        cout << endl;
    }
}