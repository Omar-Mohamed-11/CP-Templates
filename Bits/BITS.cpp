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
#define rall(v) v.rbegin(), v.rend()
#define sz(x) int(x.size())
#define OO 2e18
#define MOD 1000000007
#define PI acos(-1.0)

// If you want to use a function take it copy and paste it in the main //
//------------------------------Functions------------------------------//
bool know_bit(int n, int i) // to know the bit number i
{
    return (n >> i) & 1;
    // (or) return (n & (1 << i))
}

int set_bit(int n, int i) // to make the bit number i = 1
{
    return n | (1 << i);
}

int reset_bit(int n, int i) // to make the bit number i = 0
{
    return n & (~(1 << i));
    // (or) return n & (-1 ^ (1 << i));
}

int flip_bit(int n, int i) // to flip the bit number i
{
    return n ^ (1 << i);
}

bool is_power_of_two(int n) // checks if n is a number power of 2
{
    if (n <= 0)
        return 0;
    return !(n & (n - 1));
}

string printBinary(int n)
{
    string b = "";
    for (int i = 31; i >= 0; i--)
        b += to_string((n >> i) & 1);

    return b;
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
// -----------------------------(Topic Notes)--------------------------------//
// ===========================================================================//
/*
-NOTES:
    - First(right) digit (bit): (decimal % 10), (binary % 2)
    - Remove First(right) digit (bit): (decimal / 10), (binary / 2)

    +-------------------------+
    | Bits  | (&) | (|) | (^) |
    ---------------------------
    | 0 | 0 |  0  |  0  |  0  |
    | 0 | 1 |  0  |  1  |  1  |
    | 1 | 0 |  0  |  1  |  1  |
    | 1 | 1 |  1  |  1  |  0  |
    +-------------------------+

    - (~) Logical not operator: flip all bits
    - (a ^ b = c) , (a ^ c = b) , (b ^ c = a) ->(IMPORTANT!)
    - (a ^ b ^ c ^ d = x) -> (x ^ d = a ^ b ^ c)
    - The opposite of (XOR ^) is (XOR ^)

    - Right shift (>>): deleting the right bit (division by 2)
    - Left shift  (<<): delerint the left bit (msb) (multiblication by 2)

    - If the number x is power of two (2^x = n) this is mean n should have only 1 in binary representation.
    __builtin_popcount(n) = 1
    if the number n is power_of_tow like (8 -> 1000) if i subtract 1 of it,
    it will be it`s flip like (7 -> 0111) thats mean (n&(n-1) = 0)

    - (-1) all bits = 1 in binary representation.

    - __builtin_popcount(n) -> returns the number of ones in it`s binary representation.
    - __builtin_clz(n) -> returns the number of zeros from left (leading zeros)
    - __builtin_ctz(n) -> returns thr number of zeros from right (trailing zeros)
    - __lg(n) -> returns the index of (msb)->first one from left
    - bit_width(n) -> returns number of bits that n needs without leading zeros
    - The value of (MSB for n) = pow(2, __lg(n))
    - To know the index of (LSB) first one from right = (n & -n)
    - To know the number of zeros in int x = ((32 - __builtin_clz(z)) - __builtin_popcountll(z)); witout leading zeros
    - (1 << x) = pow(2, x)

    - (n&1) to check if the number even=0, or odd=1
    - n = n & (n - 1); to (reset) the last 1 bit اخر بت شغال
    - last bit = (n & -n) اقل بت شغال(اقل اس لل 2 موجود في الطرح )

    - (1 << n) - 1 = n of ones
    - (1 << 5) = 100000 , (1 << 5) - 1 = 11111 

    ------------------------------------------------------------------------
    - The number of all subsets of an array of size n is (2^(n-1)), The way by mask:
    vector<vector<int>> ans;
    for (int mask = 0; mask < (1 << n); mask++)
    {
        vector<int> v;
        for (int i = 0; i < n; i++)
        {
            if ((mask >> i) & 1)
                v.push_back(arr[i]);
        }
        ans.push_back(v);
    }
    ------------------------------------------------------------------------

    ----------------------------------(Bitsets)-----------------------------
    - Used only with positive intigers!
    - is dinamic i can store any numbers in it, it is looks like vector
    - bitset<8> b(5);
    - cout << b; prints the binary represintation of 5 in 8 bits
    - b.count(); returns the number of ones
    - b.set(); sets all bits to 1
    - b.set(i);  to make the bit number i = 1
    - b.reset(); resets all bits to 0
    - b.reset(i); to make the bit number i = 0
    - b.flip(); flips all bits
    - b.flip(i)l flips bit number i
    - b[i] , b.test(i); to access the bit number i
    - b.to_ulong(); b.to_ullong(); returns the decimal number
    - b.to_string(); returns the binary representation as a string;
    - b.any(); checks if there is any one
    - b.none(); checks if all bits = 0
    - b.all(); checks if all bits = 1
    -------------------------------------------------------------------------

*/
// ===========================================================================//
// ===========================================================================//