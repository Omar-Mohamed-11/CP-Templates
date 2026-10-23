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
public:
    vector<vector<int>> adj;
    vector<bool> vis;
    vector<int> par;
    vector<int> dist; // Depth of vertex from root
    vector<int> color; // BFS State

    BFS(){};
    BFS(int n) : n(n) {
        adj.resize(n + 1);
        vis.resize(n + 1, 0);
        par.resize(n + 1, -1);
        dist.resize(n + 1, -1);
        color.resize(n + 1, -1);
    }

    void add_edge(int u, int v) {adj[u].push_back(v);}
    void add_edges(int u, int v){adj[u].push_back(v); adj[v].push_back(u);}

    // Time: O(n + m)
    void bfs(int src){
        queue<int> q;
        q.push(src);
        vis[src] = 1;
        dist[src] = 0;

        while(!q.empty()){
            int v = q.front();
            q.pop();

            for(auto &u : adj[v]){
                if(!vis[u]){
                    vis[u] = 1;
                    par[u] = v;
                    dist[u] = dist[v] + 1;
                    q.push(u);
                }
            }
        }
    }

    // Time: O(n + m) + O(h)
    vector<int> get_path(int src){
        vector<int> path;

        while(src != -1){
            path.push_back(src);
            src = par[src];
        }

        return path;
    }

    // Time: O(n + m)
    int count_connected_comp(){
        int ans = 0;

        for(int i = 1; i <= n; i++){
            if(!vis[i]){
                ans++;

                queue<int> q;
                q.push(i);
                vis[i] = 1;

                while(!q.empty()){
                    int v = q.front();
                    q.pop();

                    for(auto &u : adj[v]){
                        if(!vis[u]){
                            vis[u] = 1;
                            q.push(u);
                        }
                    }
                }
            }
        }

        return ans;
    }

    // Time: O(n + m)
    bool is_bipartite(int src){
        queue<int> q;
        q.push(src);

        vis[src] = 1;
        color[src] = 0;

        while(!q.empty()){
            int v = q.front();
            q.pop();

            for(auto &u : adj[v]){
                if(!vis[u]){
                    vis[u] = 1;
                    color[u] = color[v] ^ 1;
                    q.push(u);
                }
                else{
                    if(color[u] == color[v])
                        return 0;
                }
            }
        }

        return 1;
    }

    // Time: O(n + m)
    bool contains_cycle(int src){
        queue<int> q;
        q.push(src);

        vis[src] = 1;

        while(!q.empty()){
            int v = q.front();
            q.pop();

            for(auto &u : adj[v]){
                if(!vis[u]){
                    vis[u] = 1;
                    par[u] = v;
                    q.push(u);
                }
                else{
                    if(u != par[v])
                        return 1;
                }
            }
        }

        return 0;
    }

    // Time: O(n + m)
    int get_farthest(int src){
        bfs(src);

        int node = src;

        for(int i = 1; i <= n; i++){
            if(dist[i] > dist[node])
                node = i;
        }

        return node;
    }

    // Time: O(n + m)
    int tree_diameter(int src){
        int x = get_farthest(src);

        fill(vis.begin(), vis.end(), 0);
        fill(dist.begin(), dist.end(), -1);
        fill(par.begin(), par.end(), -1);

        bfs(x);

        return *max_element(all(dist));
    }
};

//----------------------------------------(NOTES)-------------------------------------//
/*
- Time: O(n + m)
────────────────────────────────────

BFS Properties:
    - dist[v] = shortest distance from source to v.
    - par[v] = parent of v in the BFS tree.
    - BFS gives shortest paths in an unweighted graph.
───────────────────────────────────────────────────────────────────────────────────────

BFS Template Applications:
    - Graph Traversal and Reachability
    - Parent Tracking and Path Reconstruction
    - Shortest Path in Unweighted Graph
    - Distance / Level Calculation
    - Connected Components
    - Bipartite Graph Checking
    - Multi-Source BFS
    - Grid BFS
    - Tree Diameter

───────────────────────────────────────────────────────────────────────────────────────

Shortest Path:
    - BFS finds the shortest path when all edges have equal weight.
    - dist[v] = minimum number of edges from source to v.

───────────────────────────────────────────────────────────────────────────────────────

Connected Components:
    - Run BFS from every unvisited vertex.
    - Every BFS traversal represents one connected component.

───────────────────────────────────────────────────────────────────────────────────────

Is Bipartite:
    - Color each vertex with one of two colors.
    - Every edge must connect vertices with different colors.
    - BFS can assign colors level by level.

───────────────────────────────────────────────────────────────────────────────────────

Multi-Source BFS:
    - Put all sources into the queue initially.
    - Set dist[source] = 0 for all sources.
    - Then run normal BFS.
    - Gives the distance from every vertex to its nearest source.

───────────────────────────────────────────────────────────────────────────────────────

Tree Diameter:
    - Run BFS from any node.
    - Find the farthest node x.
    - Run BFS from x.
    - The maximum distance is the diameter.

*/