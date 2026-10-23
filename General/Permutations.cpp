#include <bits/stdc++.h>
using namespace std;

// ============================================================
// PERMUTATION TOOLKIT
// 0-indexed: p[i] is the destination of index i.
// A valid permutation contains every value from 0 to n-1 once.
// ============================================================

// 1. Check whether p is a valid permutation
bool is_permutation(const vector<int>& p) {
    int n = p.size();
    vector<bool> vis(n, false);

    for (int x : p) {
        if (x < 0 || x >= n || vis[x])
            return false;
        vis[x] = true;
    }

    return true;
}

// 2. Find the inverse permutation
// If p[i] = j, then inverse[j] = i.
vector<int> inverse_permutation(const vector<int>& p) {
    int n = p.size();
    vector<int> inv(n);

    for (int i = 0; i < n; i++)
        inv[p[i]] = i;

    return inv;
}

// 3. Return all cycles of p
// Fixed points such as {3} are included.
vector<vector<int>> get_cycles(const vector<int>& p) {
    int n = p.size();
    vector<bool> vis(n, false);
    vector<vector<int>> cycles;

    for (int i = 0; i < n; i++) {
        if (vis[i]) continue;

        vector<int> cycle;
        int u = i;

        while (!vis[u]) {
            vis[u] = true;
            cycle.push_back(u);
            u = p[u];
        }

        cycles.push_back(cycle);
    }

    return cycles;
}


// 4. Count the number of cycles in a permutation
int num_of_cycles_in_permutation(const vector<int>& p) {
    int n = p.size();
    vector<bool> vis(n, false);

    int cycles = 0;

    for (int i = 0; i < n; i++) {
        if (!vis[i]) {
            cycles++;

            int u = i;

            while (!vis[u]) {
                vis[u] = true;
                u = p[u];
            }
        }
    }

    return cycles;
}

// 5. Return the length of each cycle
vector<int> get_cycle_lengths(const vector<int>& p) {
    vector<int> lengths;

    for (const auto& cycle : get_cycles(p))
        lengths.push_back(cycle.size());

    return lengths;
}

// 6. Minimum swaps to transform p into the identity permutation
// Answer = n - number of cycles.
int min_swaps_to_identity(const vector<int>& p) {
    return (int)p.size() - num_of_cycles_in_permutation(p);
}

// 7. Check whether p is the identity permutation
bool is_identity_permutation(const vector<int>& p) {
    for (int i = 0; i < (int)p.size(); i++) {
        if (p[i] != i)
            return false;
    }

    return true;
}

// 8. Compose two permutations
// Result[i] = q[p[i]]
// This means: apply p first, then q.
vector<int> compose_permutations(
    const vector<int>& p,
    const vector<int>& q
) {
    int n = p.size();
    vector<int> result(n);

    for (int i = 0; i < n; i++)
        result[i] = q[p[i]];

    return result;
}

// 9. Raise a permutation to a non-negative power
// Result[i] = p applied k times to i.
// p^0 is the identity permutation.
vector<int> permutation_power(
    const vector<int>& p,
    long long k
) {
    int n = p.size();
    vector<int> result(n);
    iota(result.begin(), result.end(), 0);

    vector<int> base = p;

    while (k > 0) {
        if (k & 1)
            result = compose_permutations(result, base);

        base = compose_permutations(base, base);
        k >>= 1;
    }

    return result;
}

// 10. Order of a permutation
// Smallest positive k such that p^k = identity.
// WARNING: LCM may overflow long long for large permutations.
long long permutation_order(const vector<int>& p) {
    long long ans = 1;

    for (int len : get_cycle_lengths(p)) {
        ans = ans / gcd(ans, (long long)len) * len;
    }

    return ans;
}



//-----------------------------------------------------------------------------//
//-----------------------------------------------------------------------------//

// ============================================================
// EXAMPLES
// ============================================================

int main() {
    vector<int> p = {1, 0, 3, 2, 4};

    cout << "Valid permutation: "
         << is_permutation(p) << '\n';

    cout << "Number of cycles: "
         << num_of_cycles_in_permutation(p) << '\n';

    cout << "Minimum swaps to identity: "
         << min_swaps_to_identity(p) << '\n';

    cout << "Identity permutation: "
         << is_identity_permutation(p) << '\n';

    cout << "Cycle decomposition:\n";
    for (const auto& cycle : get_cycles(p)) {
        for (int x : cycle)
            cout << x << ' ';
        cout << '\n';
    }

    cout << "Inverse permutation: ";
    for (int x : inverse_permutation(p))
        cout << x << ' ';
    cout << '\n';

    cout << "Cycle lengths: ";
    for (int x : get_cycle_lengths(p))
        cout << x << ' ';
    cout << '\n';

    cout << "Permutation order: "
         << permutation_order(p) << '\n';

    cout << "p^2: ";
    for (int x : permutation_power(p, 2))
        cout << x << ' ';
    cout << '\n';

    return 0;
}


//-----------------------------------(Permutaion Notes)---------------------------------//
/*
==================== TIME COMPLEXITY ========================
1.  is_permutation(p)                  : O(n)
2.  inverse_permutation(p)             : O(n)
3.  get_cycles(p)                      : O(n)
4.  num_of_cycles_in_permutation(p)    : O(n)
5.  get_cycle_lengths(p)               : O(n)
6.  min_swaps_to_identity(p)           : O(n)
7.  is_identity_permutation(p)         : O(n)
8.  compose_permutations(p, q)         : O(n)
9.  permutation_power(p, k)            : O(n * log(k))
10. permutation_order(p)               : O(n * log(n))
=============================================================


- in the permutation problem:
    we use the next_permutation fun to see the pattern of the code like this,
    and from the pattern we can solve the problem,
    this code is constant, we just change the "can" function up to the problem.
    in this problem he asked to print any permutation of any subarray of length <= n
    but the summtion of any subarray (L to R , and L != R) in this permutation not divisable by its length

- Code:
    void MoRa_Solve()
    {

        int n;
        cin >> n;
        vector<int> v(n);
        for(int i = 0; i < n; i++) v[i] = i + 1;

        auto can = [&](){
            for(int i = 0; i < n; i++){
                int sum = v[i];
                for(int j = i + 1; j < n; j++){
                    sum += v[j];
                    if(sum % (j - i + 1) == 0) return 0;
                }
            }
            return 1;
        };

        do{
            if(can()){
                cout(v);
                cout << nl;
            }
        }while(next_permutation(all(v)));

    }
---------------------------------------------------------------------------


*/