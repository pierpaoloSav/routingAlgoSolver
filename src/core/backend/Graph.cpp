#include "Graph.h"
#include <unordered_map>

void Graph::addNode(int node)
{
    if (m_adj.find(node) == m_adj.end()) m_adj[node] = {};
}

void Graph::addUndirectedEdge(int node, int node1, int weight)
{
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
    // Delete all the edges from the node
    m_adj.erase(node);

    // Delete all the edges to the node from others
    for (auto& [key, edges] : m_adj) 
    {
        for (auto it = edges.begin(); it != edges.end(); ) 
        {
            if (it->first == node)
                it = edges.erase(it);
            else
                ++it;
        }
    }
}

void Graph::deleteEdge(int node, int node1)
{
    // Delete the edge
    auto itMap = m_adj.find(node);
    if (itMap != m_adj.end()) {
        auto& edges = itMap->second;
        for (auto it = edges.begin(); it != edges.end(); )
        {
            if (it->first == node1)
                it = edges.erase(it);
            else
                ++it;
        }
    }
}