#include <bits/stdc++.h>
using namespace std;

#define int long long
#define ll long long
#define nl '\n'
#define sp ' '
#define sz(v) v.size()
#define all(v) v.begin(), v.end()
#define MOD 1000000007

const int OO = 2e18;

// TIME: O((n + m) log n)
struct Dijkstra{
private:
    int n;
public:
    // Adjacency list: adj[u] contains {neighbor, edge_cost}
    vector<vector<pair<int, int>>> adj;
    // Shortest distance from the source to each node
    vector<int> dis;
    // Parent of each node in one shortest path
    vector<int> par;
    // Number of shortest paths from the source to each node
    vector<int> mnPaths;
    // {minimum number of edges, maximum number of edges} among all minimum-cost paths
    vector<pair<int, int>> mn_mx_paths;

    Dijkstra(){};
    Dijkstra(int n) : n(n) {
        adj.resize(n + 1);
        dis.resize(n + 1, OO);
        par.resize(n + 1, -1);
        mnPaths.resize(n + 1, 0);
        mn_mx_paths.resize(n + 1, {OO, -OO});
    }

    void add_edge(int u, int v, int cost) {adj[u].push_back({v, cost});}
    void add_edges(int u, int v, int cost){adj[u].push_back({v, cost}); adj[v].push_back({u, cost});}

    // Finds the shortest distance from src to every node
    // and finds the minimum/maximum number of edges among them.
    // Time: O((n + m) log n)
    void dijkstra(int src){
        //{cost, node}
        priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
        pq.push({0, src});
        dis[src] = 0;
        par[src] = -2;
        mnPaths[src] = 1;
        mn_mx_paths[src] = {0, 0};
        
        while(!pq.empty()){
            auto cur = pq.top(); // p = {cost, node}
            pq.pop();
            int p = cur.second, d = cur.first;

            if(d != dis[p]) continue;

            for(auto &[ch, cost] : adj[p]){
                if(d + cost < dis[ch]){
                    par[ch] = p;
                    dis[ch] = d + cost;
                    mnPaths[ch] = mnPaths[p];
                    mn_mx_paths[ch].first = mn_mx_paths[p].first + 1;
                    mn_mx_paths[ch].second = mn_mx_paths[p].second + 1;

                    pq.push({dis[ch], ch});
                }
                else if(d + cost == dis[ch]){
                    mnPaths[ch] = (mnPaths[ch] + mnPaths[p]) % MOD;

                    mn_mx_paths[ch].first = min(mn_mx_paths[ch].first, mn_mx_paths[p].first + 1);
                    mn_mx_paths[ch].second = max(mn_mx_paths[ch].second, mn_mx_paths[p].second + 1);
                }
            }
        }
    }

    // Returns one shortest path from node 1 to end.
    // Time: O(n)
    vector<int> get_path(int end){
        if(dis[end] == OO) return {-1};

        vector<int> path;
        for(int p = end; p != -2; p = par[p]) path.push_back(p);

        reverse(all(path));
        return path;
    }

    // Prints the shortest distance from node 1 to every node.
    // Time: O(n)
    void print_distances(){
        for(int i = 1; i <= n; i++) cout << dis[i] << sp;
    }
};

//----------------------------------------(NOTES)-------------------------------------//
/*
Dijkstra's Algorithm:
─────────────────────
- Finds the shortest distance from a source to every reachable vertex.
- Uses a priority queue (min-heap).
- Works with non-negative edge weights.
- Time: O((n + m) log n) using an adjacency list and a binary heap.
- Memory: O(n + m), including the graph and stored arrays.

───────────────────────────────────────────────────────────────────────────────────────

Dijkstra Template Applications:
    - Shortest Distance from a Source
    - Parent Tracking and Path Reconstruction
    - Counting Shortest Paths
    - Minimum Number of Edges Among Shortest Paths
    - Maximum Number of Edges Among Shortest Paths

───────────────────────────────────────────────────────────────────────────────────────

Shortest Distance:
    - dis[v] = minimum cost from the source to v.
    - dis[v] = OO means v is unreachable.
    - Relaxation:
        if (dis[v] + cost < dis[u])
            dis[u] = dis[v] + cost;

───────────────────────────────────────────────────────────────────────────────────────

Parent Tracking and Path Reconstruction:
    - par[v] stores the previous vertex on one shortest path.
    - par[src] = -2 marks the source.
    - Reconstruct the path by following parent pointers backwards.
    - Reverse the resulting path to obtain source -> destination.

───────────────────────────────────────────────────────────────────────────────────────

Counting Shortest Paths:
    - mnPaths[v] = number of shortest paths from the source to v.
    - mnPaths[src] = 1.
    - If a strictly shorter path is found:
        mnPaths[u] = mnPaths[v].
    - If another path with the same shortest distance is found:
        mnPaths[u] = (mnPaths[u] + mnPaths[v]) % MOD.

───────────────────────────────────────────────────────────────────────────────────────

Minimum / Maximum Number of Edges:
    - mn_mx_paths[v].first = minimum number of edges among shortest paths.
    - mn_mx_paths[v].second = maximum number of edges among shortest paths.
    - When a shorter path is found:
        Both values are updated from the predecessor + 1.
    - When an equally short path is found:
        Take the minimum of the first values and maximum of the second values.

───────────────────────────────────────────────────────────────────────────────────────

Important Conditions:
    - Dijkstra requires non-negative edge weights for shortest distances.
    - This template's shortest-path counting and edge-count updates assume
      strictly positive edge weights.
    - Zero-weight edges can require additional handling because equal-distance
      paths may be discovered after a vertex has been processed.
    - For graphs with negative edge weights, use an appropriate alternative,
      such as Bellman-Ford.

───────────────────────────────────────────────────────────────────────────────────────

Dijkstra vs BFS:
    - BFS finds shortest paths when all edges have equal weight.
    - Dijkstra handles non-negative edges with different weights.
    - BFS: O(n + m).
    - Dijkstra: O((n + m) log n) with a binary heap.

───────────────────────────────────────────────────────────────────────────────────────

Directed / Undirected Graph:
    - add_edge(u, v, cost): adds u -> v.
    - add_edges(u, v, cost): adds both u -> v and v -> u.

*/