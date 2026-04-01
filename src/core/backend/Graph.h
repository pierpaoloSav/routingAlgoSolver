#pragma once

#include <vector>
#include <map>
#include <iostream>

using namespace std;

class Graph
{
public:
    void addNode(int node);
    void addUndirectedEdge(int node, int node1, int weight);
    void addDirectedEdge(int node, int node1, int weight);
    
    void deleteNode(int node);
    void deleteEdge(int node, int node1);

    unordered_map<int, pair<int, vector<int>>> dijkstra(int src, bool *error);
    vector<vector<int>> getPaths(unordered_map<int, pair<int,vector<int>>> &dist, int src, int target);
    unordered_map<int, pair<int, vector<int>>> bellmanFord(int src, bool *error);

private:
    unordered_map<int, vector<pair<int,int>>> m_adj;
};