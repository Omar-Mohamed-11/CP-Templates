#include <bits/stdc++.h>
using namespace std;

#define ll long long
#define nl '\n'
#define sp ' '
#define sz(v) v.size()

//================================(Representation using Adjacency List)===============================//
// For undirected graph
vector<vector<int>> AdjacencyList(int n, int m, vector<pair<int, int>> edges){
    vector<vector<int>> adj(n + 1);
    for(auto & [u, v] : edges){
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    
    return adj;
}

//================================(Representation using Adjacency Matrix)===============================//
// For undirected graph
vector<vector<bool>> AdjacencyMat(int n, int m, vector<pair<int, int>> edges){
    vector<vector<bool>> adj(n + 1, vector<bool>(n + 1, 0));
    for(auto & [u, v] : edges){
        adj[u][v] = adj[v][u] = 1;
    }

    return adj;
}

int main()
{
    

    return 0;
}