#include <bits/stdc++.h>
using namespace std;

#define ll long long
#define nl '\n'
#define sp ' '
#define sz(v) v.size()
#define all(v) v.begin(), v.end()

int N = 1e5 + 5;
vector<vector<int>> adj(N);
vector<int> in(N), ans;

// If you whabt the minimum lexicographical order
// Use: priority_queue<int, vector<int>, greater<int>> pq;
// Insted of: queue<int> q;
void kahns(int n){
    queue<int> q;
    for(int i = 1; i <= n; i++)
        if(in[i] == 0) q.push(i);

    while(!q.empty()){
        int p = q.front();
        q.pop();
        ans.push_back(p);

        for(auto & ch : adj[p]){
            in[ch]--;
            if(in[ch] == 0) q.push(ch);
        }
    }

    reverse(all(ans));
}




int main()
{
    int n, m;
    cin >> n >> m;
    while(m--){
        int u, v;
        cin >> u >> v;
        adj[u].push_back(v);
        in[v]++; // important
    }

    return 0;
}