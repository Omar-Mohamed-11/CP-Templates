#include <bits/stdc++.h>
using namespace std;

#define ll long long
#define nl '\n'
#define sp ' '
#define sz(v) v.size()
#define all(v) v.begin(), v.end()
#define MOD 1000000007

// TIME: O(n)
struct BFS{
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
    vector<int> color; // BFS State
    int diameter;

    BFS(){};
    BFS(int n) : n(n) {
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

    
};

//----------------------------------------(NOTES)-------------------------------------//
/*

─────────


───────────────────────────────────────────────────────────────────────────────────────


───────────────────────────────────────────────────────────────────────────────────────



*/