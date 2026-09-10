//---------(بسم الله الرحمن الرحيم)---------//
#include <bits/stdc++.h>
using namespace std;
void MoRa()
{
    ios_base::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);
}

#define int long long
#define ll long long
#define nl '\n'
#define sp ' '
#define all(v) v.begin(), v.end()
#define sz(v) v.size()
#define cin(v)        \
    for (auto &x : v) \
    cin >> x;
#define cout(v)       \
    for (auto &x : v) \
        cout << x;

//=========================================(POWER-SETS)=============================================//
struct PowerSets{
private:    
    vector<int> cur;
public:
    vector<vector<int>> ans;
    // to get all power sets using Recursion & BacTracking
    void rec(int n, vector<int> & v, int i){
        // base case
        if(i >= n){
            ans.push_back(cur);
            return;
        }

        // recursion case
        cur.push_back(v[i]);
        rec(n, v, i + 1);
        cur.pop_back();
        rec(n, v, i + 1);
    }

    // The number of all subsets of an array of size n is (2^n), The way by mask:
    void masks(int n, vector<int> & v){
        for (int mask = 0; mask < (1 << n); mask++){
            vector<int> cur;
            for (int i = 0; i < n; i++)
            {
                if ((mask >> i) & 1)
                    cur.push_back(v[i]);
            }
            ans.push_back(cur);
        }
    }
};



void Solve()
{

    int n;
    cin >> n;
    vector<int> v(n);
    cin(v);

    PowerSets p1, p2;
    p1.masks(n, v);
    vector<vector<int>> res1 = p1.ans;
    sort(all(res1));
    
    p2.rec(n, v, 0);
    vector<vector<int>> res2 = p2.ans;
    sort(all(res2));

    cout << "All Power Sets Using Recursion: \n";
    for(auto & c : res2){cout(c); cout << nl;}
    cout << "All Power Sets Using Masks: \n";
    for(auto & c : res1){cout(c); cout << nl;}

}

signed main()
{
    MoRa();
    Solve();
    return 0;
}