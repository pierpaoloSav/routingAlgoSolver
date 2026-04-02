#include "Graph.h"

// Dijkstra's algorithm as a member function of Graph.
// - Uses m_adj (unordered_map) as adjacency list; node indices may be non-contiguous
// - Sets *error to true if src is invalid or a negative weight edge is found
// - Returns unordered_map: key = node index, value = pair: .first = shortest distance from src, .second = vector of predecessors
// - On error, returns empty unordered_map
unordered_map<int, pair<int, vector<int>>> Graph::dijkstra(int src, bool *error)
{
    priority_queue<
        pair<int, int>,
        vector<pair<int, int>>,
        greater<pair<int, int>>
    > pq;

    *error = false;
    unordered_map<int, pair<int, vector<int>>> dist;

    // If there isn't the search node return now
    if (m_adj.find(src) == m_adj.end()) {*error = true; return dist;}

    dist[src] = {0, vector<int>()};
    pq.emplace(0, src);

    // Process the queue until all reachable vertices are finalized
    while (!pq.empty()) 
    {
        auto top = pq.top();
        pq.pop();

        int d = top.first;
        int u = top.second;

        // If this distance not the latest shortest one, skip it
        if (dist.find(u) == dist.end() || d > dist[u].first)
            continue;

        // Explore all neighbors of the current vertex
        auto it = m_adj.find(u);
        if (it == m_adj.end()) continue;
        for (auto &p : it->second) 
        {
            int v = p.first;
            int w = p.second;

            // If a negative weight is found, return immediately
            if (w < 0)
            {
                *error = true;
                return unordered_map<int, pair<int, vector<int>>>();
            }

            int newDist = dist[u].first + w;

            if (dist.find(v) == dist.end() || newDist < dist[v].first) 
            {
                dist[v].first = newDist;
                dist[v].second.clear();
                dist[v].second.push_back(u);
                pq.emplace(dist[v].first, v);
            }
            else if (newDist == dist[v].first) 
            {
                dist[v].second.push_back(u);
            }
        }
    }

    return dist;
}

// Bellman-Ford algorithm as a member function of Graph.
// - Uses m_adj (unordered_map) as adjacency list; node indices may be non-contiguous
// - Uses an hashset to check duplicates in the predecessors
// - Sets *error to true if src is invalid or a negative cycle is detected
// - Returns unordered_map: key = node index, value = pair: .first = distance, .second = vector of predecessors
// - On error, returns empty unordered_map
unordered_map<int, pair<int, vector<int>>> Graph::bellmanFord(int src, bool *error)
{
    *error = false;
    unordered_map<int, pair<int, vector<int>>> dist;

    // If src node is invalid
    if (m_adj.find(src) == m_adj.end()) 
    {
        *error = true;
        return dist;
    }

    dist[src].first = 0;

    unordered_map<int, unordered_set<int>> predSet;

    // Bellman-Ford main loop (V-1 times)
    int V = (int)m_adj.size();
    for (int i = 0; i < V - 1; ++i) 
    {
        bool updated = false;
        for (auto &entry : m_adj) 
        {
            int u = entry.first;
            if (dist.find(u) == dist.end() || dist[u].first == INT_MAX) continue;
            for (auto &p : entry.second) 
            {
                int v = p.first;
                int w = p.second;
                int newDist = dist[u].first + w;
                if (dist.find(v) == dist.end() || newDist < dist[v].first) 
                {
                    dist[v].first = newDist;
                    dist[v].second.clear();
                    predSet[v].clear();
                    if (predSet[v].find(u) == predSet[v].end())
                    {
                        dist[v].second.push_back(u);
                        predSet[v].insert(u);
                    }
                    updated = true;
                } 
                else if (dist.find(v) != dist.end() && newDist == dist[v].first) 
                {
                    // Multiple min paths
                    if (predSet[v].find(u) == predSet[v].end())
                    {
                        dist[v].second.push_back(u);
                        predSet[v].insert(u);
                    }
                }
            }
        }
        // Optional: break early if no update
        if (!updated) break;
    }

    // Check for negative-weight cycles
    for (auto &entry : m_adj) 
    {
        int u = entry.first;
        if (dist.find(u) == dist.end() || dist[u].first == INT_MAX) continue;
        for (auto &p : entry.second) 
        {
            int v = p.first;
            int w = p.second;
            if (dist.find(v) == dist.end()) continue;
            if (dist[u].first + w < dist[v].first) 
            {
                *error = true;
                return unordered_map<int, pair<int, vector<int>>>();
            }
        }
    }

    return dist;
}

// Retrieves all minimum paths from src to target based on the predecessor information.
// - Parameters:
//   - dist: unordered_map from a routing algorithm containing distances and predecessors
//   - src: source node index
//   - target: target node index
// - Returns a vector of paths, where each path is a vector of node indices from src to target.
//   returns it empty if target not found
// - Uses depth-first search to explore all possible minimum paths by traversing predecessors
// - Theoretical time big O is O(2^N) but in practical terms it's O(P · L)
vector<vector<int>> Graph::getPaths(unordered_map<int, pair<int,vector<int>>> &dist, int src, int target)
{
    vector<vector<int>> r;
    vector<int> currentPath;

    // Early exit if target is invalid or unreachable
    if (dist.find(target) == dist.end() || dist[target].first == INT_MAX) 
        return r;
    if (dist.find(src) == dist.end())
        return r;

    // Recursive DFS function (Inorder traversal)
    function<void(int)> dfs = [&](int node)
    {
        //BASE CASES
        // Prevent errors
        if (dist.find(node) == dist.end()) return;
        // Avoid cycles
        if (find(currentPath.begin(), currentPath.end(), node) != currentPath.end()) 
            return;

        
        currentPath.push_back(node);

        if (node == src)
        {
            // Node found
            r.push_back(vector<int>(currentPath.rbegin(), currentPath.rend()));
        }
        else
        {
            // Continue recursion
            for (int parent : dist[node].second)
                dfs(parent);
        }

        currentPath.pop_back();
    };

    dfs(target);

    return r;
}