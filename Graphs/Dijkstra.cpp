#include <bits/stdc++.h>
using namespace std;

#define int long long
#define ll long long
#define nl '\n'
#define sp ' '
#define sz(v) v.size()
#define all(v) v.begin(), v.end()

const int N = 1e5 + 5;
const int OO = 2e18;
vector<vector<pair<int, int>>> adj(N);
vector<int> dis(N, OO);
vector<int> par(N, -1);

void dijkstra(int src){
    //{cost, node}
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
    pq.push({0, src});
    dis[src] = 0;
    par[src] = -2;

    while(!pq.empty()){
        auto cur = pq.top(); // p = {cost, node}
        pq.pop();
        int p = cur.second, d = cur.first;

        if(d != dis[p]) continue;

        for(auto &[ch, cost] : adj[p]){
            if(d + cost < dis[ch]){
                par[ch] = p;
                dis[ch] = d + cost;
                pq.push({dis[ch], ch});
            }
        }
    }
}

void print_path(int end){
    if(dis[end] == OO) return void(cout << -1);
    
    vector<int> path;
    for(int p = end; p != -2; p = par[p]) path.push_back(p);

    reverse(all(path));
    for(auto & p : path) cout << p << sp;
}

void print_distance(int n){
    for(int i = 1; i <= n; i++) cout << dis[i] << sp;
}


signed main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);
    
    return 0;
}