//---------(بسم الله الرحمن الرحيم)---------//
#include <bits/stdc++.h>
using namespace std;

void MoRa()
{
    ios_base::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin), freopen("output.txt", "w", stdout);
#endif
}

#define ll long long
#define ld long double
#define ull unsigned long long
#define nl '\n'
#define sp ' '
#define all(v) v.begin(), v.end()
#define MOD 1000000007


// get mod for arthimitic operations
#define add_mod(a, b, m) (((a % m) + (b % m)) % m)
#define sub_mod(a, b, m) (((a % m) - (b % m) + m) % m)
#define mul_mod(a, b, m) (((a % m) * (b % m)) % m)
#define fix_mod(n, m) (((n % m) + m) % m)


// get a mod for big int
ll big_mod(string s, ll mod) {
    ll res = 0;
    for (auto &c : s) res = (res * 10 + (c - '0')) % mod;
    return res;
}

// git a mod for (a ^ b)
ll mod_pow(ll a, ll b, ll m = MOD) {
    ll res = 1;
    while (b) {
        if (b & 1) res = res * a % m;
        a = a * a % m;
        b >>= 1;
    }
    return res;
}

ll mod_inv(ll a, ll m = MOD) {
    return mod_pow(a, m - 2, m); // Fermat
}


// ===========================================================================//
// -----------------------------(Main & Solve)--------------------------------//
// ===========================================================================//

void MoRa_Solve()
{

}

signed main()
{
    MoRa();
    MoRa_Solve();
    return 0;
}

// ===========================================================================//
// ===========================================================================//

// ===========================================================================//
// ----------------------------------(Notes)----------------------------------//
// ===========================================================================//
/*
    int n,k;
    cin >> n >> k;
    vector<int> v(n), p(n, 0), mod(n);
    cin(v);
    p[0] = v[0];
    for(int i = 1; i < n; i++) p[i] = p[i-1] + v[i];

    for(int i = 0; i < n; i++) mod[i] = fix_mod(p[i], k);

    map<int, vector<int>> mp;
    mp[0].push_back(-1);
    for(int i = 0; i < n; i++) mp[mod[i]].push_back(i);

    int ans = 0;
    for(auto &[x, v] : mp) ans = max(ans, v.back() - v[0]);

    cout << ans;
    


*/
// ===========================================================================//
// ===========================================================================//
