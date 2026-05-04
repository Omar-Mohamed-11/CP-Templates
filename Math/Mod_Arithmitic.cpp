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

// git a mod for (a ^ b), fast power
ll mod_pow(ll a, ll b, ll m = MOD) {
    ll res = 1;
    while (b) {
        if (b & 1) res = res * a % m;
        a = a * a % m;
        b >>= 1;
    }
    return res;
}

// (a / b) % m = (a * (b ^ -1)) % m
// Fermat little theorem:
// if m is prime and gcd(a, m) = 1, then (a ^ -1) = (a ^ (m-2))
ll mod_inv(ll a, ll m = MOD) {
    return mod_pow(a, m - 2, m); 
}

// To calculate (a / b) % m -> if m is prime, then (a * b) % m :
ll div_mod(ll a, ll b, ll m){
    return mul_mod(a, mod_inv(b, m), m);
}




// More safe than (lcm), for overflow
ll LCM(ll a, ll b){
    if(a == 0 || b == 0) return 0;
    return (a / gcd(a, b) * b);
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
-Congruent: 
    - a ≅ (b % n)  -->  (a % n) = (b % n)
    - a ≅ (b % n) --> (a - b) ≅ (0 % n) --> (a - b) % n = 0
    - (a - b) = (k * n)
    - Ex: 19 ≅ (34 % 15)  -->  (19 % 15) = (34 % 15) --> (34 - 19) = (1 * 15)
    
    - Note: if p[j] % k == p[i] % k , then sum(i+1 → j) % k == 0
    - This theory used to get a longest subarray whose sum is divisible by k
      By make an array (the mod for k on the prefix sum array).
      If the (sum % k) for any two subarrays are equal
      then their summition is divisable by k.
      thats mean for each two diffrent mod we want to know:
      the first and last occurence from left, and the longest subarray is
      -> max(ans, (last - first)) -> for all diffrent mods

        

*/
// ===========================================================================//
// ===========================================================================//