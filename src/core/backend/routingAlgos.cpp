#include <set>
#include "Graph.h"

// Dijkstra's algorithm as a member function of Graph.
// - Uses m_adj as adjacency list
// - Sets *error to true if src is invalid or a negative weight edge is found
// - Returns vector of pairs: .first = shortest distance from src, .second = vector of predecessors
// - On error, returns vector filled with INT_MAX and empty vectors
vector<pair<int,vector<int>>> Graph::dijkstra(int src, bool *error)
{
    int V = m_adj.size();

    priority_queue<
        pair<int, int>,
        vector<pair<int, int>>,
        greater<pair<int, int>>
    > pq;

    *error = false;
    vector<pair<int,vector<int>>> dist(V, {INT_MAX, vector<int>()});

    // If there isn't the search node return now
    if (src >= m_adj.size()) {*error = true; return dist;}

    dist[src] = {0, vector<int>()};
    pq.emplace(0, src);

    // Process the queue until all reachable vertices are finalized
    while (!pq.empty()) {
        auto top = pq.top();
        pq.pop();

        int d = top.first;
        int u = top.second;

        // If this distance not the latest shortest one, skip it
        if (d > dist[u].first)
            continue;

        // Explore all neighbors of the current vertex
        for (auto &p : m_adj[u]) {
            int v = p.first;
            int w = p.second;

            // If a negative weight is found, return immediately
            if (w < 0)
            {
                *error = true;
                return vector<pair<int,vector<int>>>(V, {INT_MAX, vector<int>()});
            }

            int newDist = dist[u].first + w;

            if (newDist < dist[v].first) {
                dist[v].first = newDist;
                dist[v].second.clear();
                dist[v].second.push_back(u);
                pq.emplace(dist[v].first, v);
            }
            else if (newDist == dist[v].first) {
                dist[v].second.push_back(u);
            }
        }
    }

    return dist;
}

//TODO check and refactor
// Bellman-Ford algorithm as a member function of Graph.
// - Uses m_adj as adjacency list
// - Sets *error to true if src is invalid or a negative cycle is detected
// - Returns vector of pairs: .first = distance, .second = vector of predecessors
// - On error, returns vector filled with INT_MAX and empty vectors
vector<pair<int,vector<int>>> Graph::bellmanFord(int src, bool *error)
{
    int V = m_adj.size();
    *error = false;
    vector<pair<int,vector<int>>> dist(V, {INT_MAX, vector<int>()});

    // If src node is invalid
    if (src < 0 || src >= V) {
        *error = true;
        return dist;
    }

    dist[src].first = 0;

    // Bellman-Ford main loop (V-1 times)
    for (int i = 0; i < V - 1; ++i) {
        bool updated = false;
        for (int u = 0; u < V; ++u) {
            if (dist[u].first == INT_MAX) continue;
            for (auto &p : m_adj[u]) {
                int v = p.first;
                int w = p.second;
                int newDist = dist[u].first + w;
                if (newDist < dist[v].first) {
                    dist[v].first = newDist;
                    dist[v].second.clear();
                    dist[v].second.push_back(u);
                    updated = true;
                } else if (newDist == dist[v].first) {
                    // Multiple min paths
                    dist[v].second.push_back(u);
                }
            }
        }
        // Optional: break early if no update
        if (!updated) break;
    }

    // Check for negative-weight cycles
    for (int u = 0; u < V; ++u) {
        if (dist[u].first == INT_MAX) continue;
        for (auto &p : m_adj[u]) {
            int v = p.first;
            int w = p.second;
            if (dist[u].first + w < dist[v].first) {
                *error = true;
                return vector<pair<int,vector<int>>>(V, {INT_MAX, vector<int>()});
            }
        }
    }

    return dist;
}

// Retrieves all minimum paths from src to target based on the predecessor information.
// - Parameters:
//   - dist: vector of pairs from a routing algorithm containing distances and predecessors
//   - src: source node index
//   - target: target node index
// - Returns a vector of paths, where each path is a vector of node indices from src to target
// - Uses depth-first search to explore all possible minimum paths by traversing predecessors
// - Checks unicity of paths with a set cause bellman ford could have duplicate paths
// - Theoretical time big O is O(2^N · N) but in practical terms it's O(P · L · log(P))
vector<vector<int>> Graph::getPaths(vector<pair<int,vector<int>>> &dist, int src, int target)
{
    vector<vector<int>> r;
    set<vector<int>> uniquePaths;
    vector<int> currentPath;

    // Early exit if target is invalid or unreachable
    if (target < 0 || target >= dist.size() || dist[target].first == INT_MAX) 
        return r;
    if (src < 0 || src >= dist.size())
        return r;

    // Recursive DFS function (Inorder traversal)
    function<void(int)> dfs = [&](int node)
    {
        //BASE CASES
        // Prevent errors
        if (node < 0 || node >= dist.size()) return;
        // Avoid cycles
        if (find(currentPath.begin(), currentPath.end(), node) != currentPath.end()) 
            return;

        
        currentPath.push_back(node);

        if (node == src)
        {
            // Node found
            uniquePaths.insert(vector<int>(currentPath.rbegin(), currentPath.rend()));
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

    // Check unicity of paths
    for (const auto &p : uniquePaths)
        r.push_back(p);

    return r;
}