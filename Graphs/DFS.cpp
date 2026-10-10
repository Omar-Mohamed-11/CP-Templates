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
    int diameter;

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
        diameter = 0;
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

    // Time: O(n + m)
    bool is_bipartite(int node, int c){
        vis[node] = 1;
        color[node] = c;
        for(auto & ch : adj[node]){
            if(!vis[ch]){
                if(is_bipartite(ch, c ^ 1) == 0)
                    return 0;
            }
            else{
                if(color[node] == color[ch])
                    return 0;
            }
        }
        return 1;
    }

    // Time: O(n + m)
    bool contains_cycle(int node, int par){
        vis[node] = 1;
        for(auto & ch : adj[node]){
            if(!vis[ch]){
                if(contains_cycle(ch, node))
                    return 1;
            }
            else{
                if(ch != par) return 1;
            }
        }
        return 0;
    }

    // Time: O(n + m)
    int treeDdiameter(int v){
        vis[v] = 1;
        int mx1 = 0, mx2 = 0;
        for(auto & u : adj[v]){
            if(!vis[u]){
                int h = treeDdiameter(u) + 1;
                if(h > mx1) mx2 = mx1, mx1 = h;
                else if(h > mx2) mx2 = h;
            }
        }
        diameter = max(diameter, mx1 + mx2);
        return mx1;
    }
};

//----------------------------------------(NOTES)-------------------------------------//
/*
Ancestor:
─────────
- u is an ancestor of v if u lies on the path from the root to v.
- Parent = direct ancestor.

- If u is ancestor of v:
    - in[u] < in[v]
    - out[v] < out[u]
    - then v lies in the subtree of ux

Therefore:
    u is ancestor of v iff
    (in[u] <= in[v] && out[u] >= out[v])

───────────────────────────────────────────────────────────────────────────────────────
DFS Template Applications:
    - Graph Traversal and Reachability
    - Parent Tracking and Path Reconstruction
    - Entry / Exit Times (in / out)
    - Ancestor Checking
    - Depth Calculation -> (Single Source Shortest Path (on tree): (SSSP))
    - Subtree Size Calculation
    - Directed Graph Cycle Detection (using colors)

───────────────────────────────────────────────────────────────────────────────────────
Number of connected components:
    - It is the number of vertices you can dfs starting from it. (Trying to dfs all [1 -> n])

Is a tree?
    - the tree is an undirected graph.
    - should has no cycles.
    - the number of edges of the tree of n vertices is (n - 1).
    - if ((m == n - 1) && num_of_connected_components == 1)

Is Bipartite 
    - if we can divide all its vertices into two separate sets.
    - no edge is allowed between two vertices in the same set.
    - every edge must connect two nodes from diffrent sets.

Diameter of Tree:
    - it is defined as the longest path between any 2 nodes in the tree.
    - make a dfs from any node as a root and find the farthest node (x).
    - then make a dfs from x and find the maximum distance from this node to any other node.
    - Case 2: Root is not on the diameter:
    - Case 1: Root is on the diameter:


*/