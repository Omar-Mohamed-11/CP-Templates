#include <bits/stdc++.h>
using namespace std;

#define int long long
#define ll long long
#define nl '\n'
#define sp ' '
#define sz(v) v.size()
#define all(v) v.begin(), v.end()
#define MOD 1000000007

const int N = 1e5 + 5;
const int OO = 2e18;
// Adjacency list: adj[u] contains {neighbor, edge_cost}
vector<vector<pair<int, int>>> adj(N);
// Shortest distance from the source to each node
vector<int> dis(N, OO);
// Parent of each node in one shortest path
vector<int> par(N, -1);
// Number of shortest paths from the source to each node
vector<int> mnPaths(N, 0);
// {minimum number of edges, maximum number of edges} among all minimum-cost paths
vector<pair<int, int>> mn_mx_paths(N, {OO, -OO});

// Finds the shortest distance from src to every node
// and finds the minimum/maximum number of edges among them.
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
vector<int> get_path(int end){
    if(dis[end] == OO) return {-1};
    
    vector<int> path;
    for(int p = end; p != -2; p = par[p]) path.push_back(p);

    reverse(all(path));
    return path;
}

// Prints the shortest distance from node 1 to every node.
void print_distances(int n){
    for(int i = 1; i <= n; i++) cout << dis[i] << sp;
}


signed main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);
    
    return 0;
}