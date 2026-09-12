#include <bits/stdc++.h>

using namespace std;

#define ll long long
#define nl '\n'
#define sp ' '
#define sz(v) v.size()

//======================================(Difference Array 1D)=========================================//
/**
    [1] Definition
        Difference Array -> fast range updates.
        For update [l, r] by val:
            diff[l] += val;
            diff[r + 1] -= val;
        After all updates:
            arr[i] += diff[i] using prefix sum.

    [2] Time & Space Complexity
        Update: O(1)
        Build:  O(n)
        Space:  O(n)

    [3] Tips
        Use 1-based indexing for easier updates.
        Handle l > r.
        Use ll for large values.
*/

// returns updated array
vector<ll> difference_array(vector<ll> arr, int q){
    int n = arr.size();
    vector<ll> diff(n + 2, 0);
    while (q--){
        int l, r;
        ll val;
        cin >> l >> r >> val;
        if (l > r)
            swap(l, r);

        diff[l] += val;
        diff[r + 1] -= val;
    }

    // Build difference array
    for (int i = 1; i <= n; i++)
        diff[i] += diff[i - 1];

    // Apply updates
    for (int i = 1; i <= n; i++)
        arr[i - 1] += diff[i];

    return arr;
}

//======================================(Difference Array 2D)=========================================//

/**
    [1] Definition
        Difference Array -> fast rectangle updates.
        For rectangle:
            (x1, y1) -> (x2, y2)
        We update 4 corners:
            diff[x1][y1]         += val;
            diff[x2+1][y1]       -= val;
            diff[x1][y2+1]       -= val;
            diff[x2+1][y2+1]     += val;
        Then apply 2D prefix accumulation.

    [2] Time & Space Complexity
        Update: O(1)
        Build:  O(n * m)
        Space:  O(n * m)

    [3] Tips
        Use 1-based indexing.
        D dimensions -> 2^D corner updates.
*/

// returns updated matrix
vector<vector<ll>> difference_array(vector<vector<ll>> arr, int q){
    int n = arr.size();
    int m = arr[0].size();
    vector<vector<ll>> diff(
        n + 2,
        vector<ll>(m + 2, 0)
    );

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

    // Prefix in rows
    for (int i = 1; i <= n; i++){
        for (int j = 1; j <= m; j++)
            diff[i][j] += diff[i - 1][j];
    }

    // Prefix in columns
    for (int i = 1; i <= n; i++){
        for (int j = 1; j <= m; j++)
            diff[i][j] += diff[i][j - 1];
    }

    // Apply updates
    for (int i = 1; i <= n; i++){
        for (int j = 1; j <= m; j++)
            arr[i - 1][j - 1] += diff[i][j];
    }

    return arr;
}

//======================================(Difference Array 3D)=========================================//

/**
    [1] Definition
        Difference Array -> fast cuboid updates.
        For cuboid:
            (x1, y1, z1) -> (x2, y2, z2)
        We update 8 corners.

    [2] Time & Space Complexity
        Update: O(1)
        Build:  O(n * m * k)
        Space:  O(n * m * k)

    [3] Tips
    Use 1-based indexing.
    D dimensions -> 2^D corner updates.
*/

// returns updated 3D array
vector<vector<vector<ll>>> difference_array(vector<vector<vector<ll>>> arr,int q){
    int n = arr.size();
    int m = arr[0].size();
    int k = arr[0][0].size();

    vector<vector<vector<ll>>> diff(n + 2, vector<vector<ll>>(m + 2, vector<ll>(k + 2, 0)));
    while (q--){
        int x1, y1, z1;
        int x2, y2, z2;
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

    // Prefix in X
    for (int i = 1; i <= n; i++){
        for (int j = 1; j <= m; j++){
            for (int z = 1; z <= k; z++)
                diff[i][j][z] += diff[i - 1][j][z];
        }
    }

    // Prefix in Y
    for (int i = 1; i <= n; i++){
        for (int j = 1; j <= m; j++){
            for (int z = 1; z <= k; z++)
                diff[i][j][z] += diff[i][j - 1][z];
        }
    }

    // Prefix in Z
    for (int i = 1; i <= n; i++){
        for (int j = 1; j <= m; j++){
            for (int z = 1; z <= k; z++)
                diff[i][j][z] += diff[i][j][z - 1];
        }
    }

    // Apply updates
    for (int i = 1; i <= n; i++){
        for (int j = 1; j <= m; j++){
            for (int z = 1; z <= k; z++)
                arr[i - 1][j - 1][z - 1] += diff[i][j][z];
        }
    }

    return arr;
}

//==============================================(Main)==============================================//

int main(){

    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    return 0;
}