#include <bits/stdc++.h>
using namespace std;

#define ll long long
#define nl '\n'
#define sp ' '
#define sz(v) v.size()

//======================================(Prefix/Partial 1D)=========================================//
/*
    [1] Definition
    Prefix Sum -> fast range-sum queries.
    Difference Array -> fast range updates.
    [2] Time & Space Complexity
    Prefix: Build O(n), Query O(1), Space O(n).
    Difference: Update O(1), Build O(n), Space O(n).
    [3] Tips
    Use 1-based indexing for easier queries.
    Use ll for large sums and always handle l > r.
*/

// returns 1-based prefix
vector<ll> prefix_sum(vector<int> arr){
    int n = arr.size();
    vector<ll> prefix(n + 1, 0);
    for (int i = 1; i <= n; i++)
        prefix[i] = prefix[i - 1] + arr[i - 1];
    return prefix;
}
ll query(int l, int r, const vector<ll> &pre){
    if (l > r)
        swap(l, r);
    return pre[r] - pre[l - 1];
}

vector<ll> partial_sum(vector<ll> arr, int q){
    int n = arr.size();
    vector<ll> diff(n + 1, 0);
    while (q--){
        int l, r;
        ll val;
        cin >> l >> r >> val;
        if (l > r)
            swap(l, r);
        diff[l] += val;
        diff[r + 1] -= val;
    }
    for (int i = 1; i <= n; i++)
        diff[i] += diff[i - 1];
    for (int i = 1; i <= n; i++)
        arr[i - 1] += diff[i];

    return arr;
}

//======================================(Prefix/Partial 2D)=========================================//
/*
    [1] Definition
    Prefix Sum -> fast rectangle-sum queries.
    Difference Array -> fast rectangle updates.
    [2] Time & Space Complexity
    Prefix: Build O(n*m), Query O(1), Space O(n*m).
    Difference: Update O(1), Build O(n*m), Space O(n*m).
    [3] Tips
    Use 1-based indexing for easier queries.
    Use ll for large sums and handle x1 > x2 / y1 > y2.
*/

// returns 1-based prefix
vector<vector<ll>> prefix_sum(const vector<vector<int>> &arr){
    int n = arr.size();
    int m = arr[0].size();
    vector<vector<ll>> prefix(n + 1, vector<ll>(m + 1, 0));
    for (int i = 1; i <= n; i++){
        for (int j = 1; j <= m; j++){
            prefix[i][j] =
                arr[i - 1][j - 1] + prefix[i - 1][j] + prefix[i][j - 1] -
                prefix[i - 1][j - 1];
        }
    }
    return prefix;
}
ll query(int x1, int y1, int x2, int y2, const vector<vector<ll>> &pre){
    if (x1 > x2)
        swap(x1, x2);
    if (y1 > y2)
        swap(y1, y2);

    return pre[x2][y2] - pre[x1 - 1][y2] - pre[x2][y1 - 1] + pre[x1 - 1][y1 - 1];
}

// returns 0-based difference array
vector<vector<ll>> partial_sum(vector<vector<ll>> arr, int q){
    int n = arr.size();
    int m = arr[0].size();
    vector<vector<ll>> diff(n + 2, vector<ll>(m + 2, 0));
    while (q--){
        int x1, y1, x2, y2;
        ll val;
        cin >> x1 >> y1 >> x2 >> y2 >> val;
        if (x1 > x2)
            swap(x1, x2);
        if (y1 > y2)
            swap(y1, y2);
        diff[x1][y1] += val;
        diff[x2 + 1][y1] -= val;
        diff[x1][y2 + 1] -= val;
        diff[x2 + 1][y2 + 1] += val;
    }

    for (int i = 1; i <= n; i++){
        for (int j = 1; j <= m; j++)
            diff[i][j] += diff[i - 1][j];
    }
    for (int i = 1; i <= n; i++){
        for (int j = 1; j <= m; j++)
            diff[i][j] += diff[i][j - 1];
    }
    for (int i = 1; i <= n; i++){
        for (int j = 1; j <= m; j++)
            arr[i - 1][j - 1] += diff[i][j];
    }

    return arr;
}

//======================================(Prefix/Partial 3D)=========================================//
/*
    [1] Definition
    Prefix Sum -> fast cuboid-sum queries.
    Difference Array -> fast cuboid updates.
    [2] Time & Space Complexity
    Prefix: Build O(n*m*k), Query O(1), Space O(n*m*k).
    Difference: Update O(1), Build O(n*m*k), Space O(n*m*k).
    [3] Tips
    Use 1-based indexing for easier queries.
    Use ll and remember: D dimensions -> 2^D corners.
*/

// returns 1-based prefix
vector<vector<vector<ll>>> build_prefix_sum(const vector<vector<vector<ll>>> &arr){
    int n = arr.size();
    int m = arr[0].size();
    int k = arr[0][0].size();
    vector<vector<vector<ll>>> prefix(n + 1, vector<vector<ll>>(m + 1, vector<ll>(k + 1, 0)));
    for (int i = 1; i <= n; i++){
        for (int j = 1; j <= m; j++){
            for (int z = 1; z <= k; z++){
                prefix[i][j][z] = arr[i - 1][j - 1][z - 1] + prefix[i - 1][j][z] + prefix[i][j - 1][z] + prefix[i][j][z - 1] - prefix[i - 1][j - 1][z] - prefix[i - 1][j][z - 1] - prefix[i][j - 1][z - 1] + prefix[i - 1][j - 1][z - 1];
            }
        }
    }
    return prefix;
}
ll query(int x1, int y1, int z1, int x2, int y2, int z2, const vector<vector<vector<ll>>> &pre){
    if (x1 > x2)
        swap(x1, x2);
    if (y1 > y2)
        swap(y1, y2);
    if (z1 > z2)
        swap(z1, z2);
    return pre[x2][y2][z2] - pre[x1 - 1][y2][z2] - pre[x2][y1 - 1][z2] - pre[x2][y2][z1 - 1] + pre[x1 - 1][y1 - 1][z2] + pre[x1 - 1][y2][z1 - 1] + pre[x2][y1 - 1][z1 - 1] - pre[x1 - 1][y1 - 1][z1 - 1];
}

// returns 0-based difference array
void partial_sum(vector<vector<vector<ll>>> &arr, int q){
    int n = arr.size();
    int m = arr[0].size();
    int k = arr[0][0].size();
    vector<vector<vector<ll>>> diff(n + 2, vector<vector<ll>>(m + 2, vector<ll>(k + 2, 0)));
    while (q--){
        int x1, y1, z1, x2, y2, z2;
        ll val;
        cin >> x1 >> y1 >> z1 >> x2 >> y2 >> z2 >> val;
        if (x1 > x2)
            swap(x1, x2);
        if (y1 > y2)
            swap(y1, y2);
        if (z1 > z2)
            swap(z1, z2);
        diff[x1][y1][z1] += val;
        diff[x2 + 1][y1][z1] -= val;
        diff[x1][y2 + 1][z1] -= val;
        diff[x1][y1][z2 + 1] -= val;
        diff[x2 + 1][y2 + 1][z1] += val;
        diff[x2 + 1][y1][z2 + 1] += val;
        diff[x1][y2 + 1][z2 + 1] += val;
        diff[x2 + 1][y2 + 1][z2 + 1] -= val;
    }
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= m; j++)
            for (int z = 1; z <= k; z++)
                diff[i][j][z] += diff[i - 1][j][z];
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= m; j++)
            for (int z = 1; z <= k; z++)
                diff[i][j][z] += diff[i][j - 1][z];
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= m; j++)
            for (int z = 1; z <= k; z++)
                diff[i][j][z] += diff[i][j][z - 1];
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= m; j++)
            for (int z = 1; z <= k; z++)
                arr[i - 1][j - 1][z - 1] += diff[i][j][z];
}

//=========================================(Sum of Sum)============================================//
/*
    [1] Definition
    Find the sum of sums of all subarrays inside [l, r].
    [2] Time & Space Complexity
    Preprocessing: O(n), Query: O(1), Space: O(n).
    Uses prefix sums + weighted prefix sums.
    [3] Tips
    First prefix -> sum of a[i].
    Second prefix -> sum of prefix sums.
    Key formula: a[i] * (i-l+1) * (r-i+1).
*/

int main()
{
    int n;
    cin >> n;
    vector<ll> v(n + 1);
    for (int i = 1; i <= n; i++)
        cin >> v[i];
    // First prefix sum
    for (int i = 1; i <= n; i++)
        v[i] += v[i - 1];
    vector<ll> pre1(n + 1), pre2(n + 1);
    for (int i = 1; i <= n; i++)
    {
        pre1[i] = v[i] * (i + 1);
        pre2[i] = v[i] * i;
        pre1[i] += pre1[i - 1];
        pre2[i] += pre2[i - 1];
    }
    // Second prefix sum
    for (int i = 1; i <= n; i++)
        v[i] += v[i - 1];
    int q;
    cin >> q;
    while (q--)
    {
        int l, r;
        cin >> l >> r;

        ll ans = pre1[r] - pre1[l - 1];
        ans -= (v[r] - v[l - 1]) * l;
        ll tmp = (v[r - 1] - (l == 1 ? 0 : v[l - 2])) * r;
        tmp -= (pre2[r - 1] - (l == 1 ? 0 : pre2[l - 2]));
        cout << ans - tmp << nl;
    }

    return 0;
}