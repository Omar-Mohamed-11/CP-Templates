#include <bits/stdc++.h>
using namespace std;

#define ll long long
#define nl '\n'
#define sp ' '
#define sz(v) v.size()
#define all(v) v.begin(), v.end()
#define MOD 1000000007

// TIME: O(n)
struct DFS{
private:
    int n;
    int timer;
public:
    vector<vector<int>> adj;
    vector<bool> vis;
    vector<int> par;
    vector<int> in, out; // Entry / Exit Time
    vector<int> depth; // Depth of vertex from root
    vector<int> subtree; // Counts the num of vertices in the subtree for each vertex
    vector<int> color; // DFS State

    DFS(){};
    DFS(int n) : n(n) {
        adj.resize(n + 1);
        vis.resize(n + 1, 0);
        par.resize(n + 1, -1);
        in.resize(n + 1, 0);
        out.resize(n + 1, 0);
        depth.resize(n + 1, 0);
        subtree.resize(n + 1, 1);
        color.resize(n + 1, 0);
        timer = 0;
    }

    void add_edge(int u, int v) {adj[u].push_back(v);}
    void add_edges(int u, int v){adj[u].push_back(v); adj[v].push_back(u);}

    // Time: O(n + m) where 'n' is the number of vertices and 'm is the number of edges.
    void dfs(int v){
        vis[v] = 1;
        for(auto & u : adj[v]){
            if(!vis[u]) dfs(u);
        }
    }

    // Time: O(n + m) where 'n' is the number of vertices and 'm is the number of edges.
    void dfs_visit(int v){
        in[v] = timer++;
        color[v] = 1;
        for(auto & u : adj[v]){
            if(!color[u]){
                par[u] = v;
                depth[u] = depth[v] + 1;;
                dfs_visit(u);
                subtree[v] += subtree[u];
            }
        }
        
        color[v] = 2;
        out[v] = timer++;
    }

    // Time: O(n + m) + O(h)
    vector<int> get_path(int src){
        vector<int> path;
        while (src != -1) {
            path.push_back(src);
            src = par[src];
        }
        return path;
    }

    // Time: O(n + m)
    bool is_ancestor(int u, int v){
        return (in[u] <= in[v] && out[v] <= out[u]);
    }

    // Time: O(n + m)
    int count_connected_comp(){
        int ans = 0;
        for(int i = 1; i <= n; i++){
            if(!vis[i]){
                ans++;
                dfs(i);
            }
        }
        return ans;
    }
};

//----------------------------------------(NOTES)-------------------------------------//
/*
Ancestor:
─────────
- u is an ancestor of v if u lies on the path from the root to v.
- Parent = direct ancestor.

- If u is ancestor of v:
    in[u] < in[v]
    out[v] < out[u]

Therefore:
    u is ancestor of v iff
    in[u] <= in[v] && out[v] <= out[u]

───────────────────────────────────────────────────────────────────────────────────────
DFS Template Applications:
    - Graph Traversal and Reachability
    - Parent Tracking and Path Reconstruction
    - Entry / Exit Times (in / out)
    - Ancestor Checking
    - Depth Calculation
    - Subtree Size Calculation
    - Directed Graph Cycle Detection (using colors)

───────────────────────────────────────────────────────────────────────────────────────

*/