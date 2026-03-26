#pragma once

#include <vector>
#include <iostream>

class Graph
{
public:
    void addUndirectedEdge(int node, int node1, int weight);
    void addDirectedEdge(int node, int node1, int weight);
    
    void deleteNode(int node);
    void deleteEdge(int node, int node1);

    std::vector<int> dijkstra(int src);

    void printAdj();

private:
    std::vector<std::vector<std::pair<int,int>>> m_adj = {{}};
};