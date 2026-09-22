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



// ===========================================================================//
// -----------------------------(Topic Notes)---------------------------------//
// ===========================================================================//
/*
-General:
    -Complete Graph:
        -every node connected to all other nodes directly.
        -every node has (n - 1) edges if there is n vertices.

    -Bipartite Graph:
        -if we can divide all its vertices into two separate sets.
        -no edge is allowed between two vertices in the same set.
        -every edge must connect two nodes from diffrent sets;

    -Directed Graph (digraph): is a graph where each edge has a direction.
    -Undirected Graph: is a graph where edges have no direction.

    -Directed Cyclic Graph:
        -is a directed graph that contains at least one cycle.

    -Directed Acyclic Graph (DAG):
        -Every edge has a direction.
        -The graph contains no cycle.
        -You cannot start from a vertex and follow the directed edges 
        and eventually return to that same vertex.

    -Tree:
        -the tree is an undirected graph.
        -should has no cycles.
        -the number of edges of the tree of n vertices is (n - 1).

    

    
*/
// ===========================================================================//
// ===========================================================================//