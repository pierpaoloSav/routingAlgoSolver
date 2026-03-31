#pragma once

#include <vector>

#include <iostream>

using namespace std;

class Graph
{
public:
    void addUndirectedEdge(int node, int node1, int weight);
    void addDirectedEdge(int node, int node1, int weight);
    
    void deleteNode(int node);
    void deleteEdge(int node, int node1);

    vector<pair<int,vector<int>>> dijkstra(int src, bool *error);
    vector<vector<int>> getPaths(vector<pair<int,vector<int>>> &dist, int src, int target);
    vector<pair<int,vector<int>>> bellmanFord(int src, bool *error);

    void printAdj();

private:
    vector<vector<pair<int,int>>> m_adj = {{}};
};