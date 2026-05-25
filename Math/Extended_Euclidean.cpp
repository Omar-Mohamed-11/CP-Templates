#include<bits/stdc++.h>
using namespace std;
#define ll long long

/*
    it solves 
    ax + by = gcd( a , b )
    to get x , y valid
    it can be used with Bézout's identity
    to solve ax + by + c = 0 
    if ans is found ( k = (-c / Gcd)) ==> x * k , y * k
*/ 
ll extended_euclid(ll a, ll b, ll &x, ll &y)
{
    if (b == 0) {
        x = 1;
        y = 0;
        return a;
    }
    ll x1, y1;
    ll d = extended_euclid(b, a % b, x1, y1);
    x = y1;
    y = x1 - y1 * (a / b);
    return d;
}