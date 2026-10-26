#include <bits/stdc++.h>
using namespace std;

#define ll long long
#define nl '\n'
#define sp ' '
#define sz(v) v.size()
#define all(v) v.begin(), v.end()


struct TopoSort {
    int n;
    vector<vector<int>> adj;
    vector<int> vis, ans;
    bool bad;

    // Time Complexity: O(V)
    // Space Complexity: O(V)
    // Prepares the graph structures for topological sorting.
    TopoSort(){};
    TopoSort(int n) : n(n){
        adj.resize(n + 1);
        vis.resize(n + 1, 0);
    }

    // Time Complexity: O(1) amortized
    // Space Complexity: O(1)
    // Inserts a directed/undirected edge from vertex u to v, v to u.
    void add_edge(int u, int v) {adj[u].push_back(v);}
    void add_edges(int u, int v) {adj[u].push_back(v); adj[v].push_back(u);}

    // Time Complexity: O(V + E) overall
    // Space Complexity: O(V)
    // Recursive DFS to visit nodes and construct the topological order.
    void dfs(int v) {
        vis[v] = 1;
        for (int u : adj[v]) {
            if (vis[u] == 0)
                dfs(u);
            else if (vis[u] == 1)
                bad = true;
        }
        vis[v] = 2;
        ans.push_back(v);
    }

    // Time Complexity: O(V + E)
    // Space Complexity: O(V)
    // Computes the topological sort and returns true if the graph is a DAG.
    bool topo_sort() {
        fill(vis.begin(), vis.end(), 0);
        ans.clear();
        bad = false;
        for (int i = 1; i <= n; ++i)
            if (!vis[i]) dfs(i);
        reverse(ans.begin(), ans.end());
        return !bad;
    }
};


//----------------------------------------(NOTES)-------------------------------------//
/*
Topic: Topological Sorting
Description: Linearly orders a Directed Acyclic Graph (DAG) and detects cycles.
            Uses DFS to push nodes to answer array on exit time.

Important Facts:
- 1-based indexing for nodes by default.
- Time Complexity: O(V + E)
- Space Complexity: O(V + E)

*/