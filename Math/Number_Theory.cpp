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

// If you want to use a function take it copy and paste it in the main //
//-----------------------------------------------------------------------------------//
//--------------------------------------(Math-0)-------------------------------------//
//-----------------------------------------------------------------------------------//
ll fix_mod(ll n, ll m) // fot (+ and -) integers
{
    return ((n % m) + m) % m;
}

ll factorial(ll n)
{
    ll res = 1;
    for (int i = 2; i <= n; i++)
        res *= i;
    return res;
}

ll nPr(ll n, ll r)
{
    return factorial(n) / factorial(n - r);
}
ll nCr(ll n, ll r)
{
    return nPr(n, r) / factorial(r);
}
ll nC2(ll n)
{
    return (n * (n - 1) / 2);
}

ll range_sum(ll l, ll r)
{
    if (l > r)
        swap(l, r);
    return ((r * (r + 1) / 2) - (l * (l - 1) / 2));
}
ll even_range_sum(ll l, ll r)
{
    if (l > r)
        swap(l, r);

    l += (l % 2);
    r -= (r % 2);
    return ((r - l) / 2 + 1) * (l + r) / 2;
}
ll odd_range_sum(ll l, ll r)
{
    return range_sum(l, r) - even_range_sum(l, r);
}

ll divisable_range_sum(ll l, ll r, ll x)
{
    if (l > r)
        swap(l, r);
    ll left = ((l + x - 1) / x) * x;
    ll right = (r / x) * x;

    return ((right - left) / x + 1) * (left + right) / 2;
}

bool is_power_of(ll n, ll x)
{
    // Checks if (x^any_number == n)
    if (n <= 0)
        return 0;
    ll p = log(n) / log(x);
    return (pow(x, p) == n);
}

string big_add(string s, ll n)
{
    string res = "";
    ll carry = n;

    for (int i = s.size() - 1; i >= 0; i--)
    {
        ll sum = (s[i] - '0') + carry;
        res += char((sum % 10) + '0');
        carry = sum / 10;
    }
    while (carry)
    {
        res += char((carry % 10) + '0');
        carry /= 10;
    }

    reverse(all(res));
    return res;
}

string big_multiply(string s, ll n)
{
    string res = "";
    ll carry = 0;

    for (int i = s.size() - 1; i >= 0; i--)
    {
        ll temp = (s[i] - '0') * n + carry;
        res += char(temp % 10 + '0');
        carry = temp / 10;
    }

    while (carry)
    {
        res += char(carry % 10 + '0');
        carry /= 10;
    }

    reverse(all(res));
    return res;
}

ld distance(ld x1, ld y1, ld x2, ld y2)
{
    return sqrtl(powl(abs(x2 - x1), 2) + powl(abs(y2 - y1), 2));
}

//------------------------------------(Divisors)-------------------------------------//
vector<ll> divisors(ll n)
{
    vector<ll> res;
    for (ll i = 1; i * i <= n; i++)
    {
        if (n % i == 0)
        {
            res.push_back(i);
            if (i * i != n)
                res.push_back(n / i);
        }
    }

    return res;
}
//-----------------------------------------------------------------------------------//

//---------------------------(Primes and Prime Factors)------------------------------//
bool isPrime(ll n)
{
    if (n == 2 || n == 3)
        return 1;
    else if (n % 2 == 0 || n % 3 == 0 || n <= 1)
        return 0;

    for (int i = 5; i * i <= n; i++)
    {
        if (n % i == 0)
            return 0;
    }

    return 1;
}

map<ll, ll> primeFactors(ll n)
{
    map<ll, ll> mp;
    for (ll i = 2; i * i <= n; i++)
    {
        while (n % i == 0)
        {
            mp[i]++;
            n /= i;
        }
    }
    if (n != 1)
        mp[n]++;

    return mp;
}
//-----------------------------------------------------------------------------------//

//-----------------------------------------------------------------------------------//
//-----------------------------------(Number Theory)---------------------------------//
//-----------------------------------------------------------------------------------//
bool is_sqrt(ll n)
{
    ll s = sqrt(n);
    return (s * s == n);
}

bool tPrime(ll n)
{
    ll s = sqrt(n);
    if (s * s != n)
        return 0;

    return isPrime(s);
}

ll num_of_factorial_digits(ll n)
{
    double sum = 0;
    for (int i = 1; i <= n; i++)
    {
        sum += log10(i);
    }

    ll res = floor(sum) + 1;
    return res;
}

ll num_of_trailling_zeros_for_factorial(ll n) // trailing zeros in (n!)
{
    ll cnt = 0;
    while (n)
    {
        cnt += (n / 5);
        n /= 5;
    }

    return cnt;
}

//-----------------------------------(Sieve-Primes)----------------------------------//
const int N = 1e6 + 5;

vector<bool> is_prime(N, 1); // The size = MAX(n) in problem, Time = (n log(log(n)))
vector<int> primes;
void sieve()
{
    is_prime[0] = is_prime[1] = 0;

    for (int i = 4; i < N; i += 2)
        is_prime[i] = 0;

    for (int i = 3; i * i < N; i += 2)
    {
        if (is_prime[i])
        {
            for (int j = i * i; j < N; j += i)
                is_prime[j] = 0;
        }
    }

    for (int i = 2; i < N; i++)
    {
        if (is_prime[i])
            primes.push_back(i);
    }
}

// ----------(Linear Sieve)---------- //
vector<int> lp(N);
vector<int> pr;
void linearSieve()
{
    // Time = o(N)
    for (int i = 2; i < N; i++)
    {
        if (lp[i] == 0)
        {
            lp[i] = i;
            pr.push_back(i);
        }
        for (int j = 0; i * pr[j] < N; j++)
        {
            lp[i * pr[j]] = pr[j];
            if (pr[j] == lp[i])
            {
                break;
            }
        }
    }
}

vector<int> spf(N);
void spf_sieve()
{
    for (int i = 1; i < N; i++)
        spf[i] = i;
    for (int i = 4; i < N; i += 2)
        spf[i] = 2;
    for (int i = 3; i * i < N; i += 2)
    {
        if (spf[i] == i)
        {
            for (int j = i * i; j < N; j += i)
            {
                if (spf[j] == j)
                    spf[j] = i;
            }
        }
    }
}

vector<pair<int, int>> prime_factors(int n)
{
    vector<pair<int, int>> freq;
    while (n != 1)
    {
        int p = spf[n], cnt = 0;
        while (p == spf[n])
        {
            n /= spf[n];
            cnt++;
        }
        freq.push_back({p, cnt});
    }

    return freq;
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

//----------------------------------------------------------------------------//

// ===========================================================================//
// -----------------------------(Topic Notes)---------------------------------//
// ===========================================================================//
/*
-NOTES:
    -The count of range = (right - left) + 1

    -To know that a big number is divisable by 2 -> last digit should be even
    -To know that a big number is divisable by 3 -> summition of its digits should be
     divisable by 3
    -To know that a big number is divisable by 5 -> last digit should be (0 or 5)

    -GCD: greatest common divisors of (a,b) = (a / lcm(a, b) * b)
        : the biggest number can divide (a and b)
    -LCM: lowest common multiplication = (a / gcd(a, b) * b)
        : the lowest number can be divided by (a and b)

    -log(n) = ln(n)
    -log2(n) , log10(n)
    -a = b^x  -> x = logb(a) (x is the number of divisions for (a/b))
    -log(a*b) = log(a)+log(b)
    -log(a/b) = log(a)-log(b)
    -log(a^n) = n*log(a)

    -Number of digits of a decimal number X = floor(log10(X)) + 1  for->(decimal)
    -Number of digits of a binary number X = floor(log2(X)) + 1  for->(binary)

    -Arethmatic sequance: Nth = a + (n-1)*d   ,  Sn = n*(a+al)/2
    -Geometric sequance: Nth = a * (r^(n-1))  ,  Sn = a * (1-(r^n)) / (1-r)

    -Heron's Formula = to calculates the area of any triangle using only its three side lengths (a,b,c)
                     = sqrtl(s * (s - a) * (s - b) * (s - c));
        when s = (a + b + c)

    -Circle Equation: powl((x-h),2) + powl((y-h), 2) = r*r
        center(h, k) , raduis=r
    -If the distance between the center(h,k) and point(x,y) is <= r
    then this point belongs to the circle

    -Straight line between three point condition is if((x2-x1)*(y3-y1)==(y2-y1)*(x3-x1))
    -Two lines are parallel if((y2-y1)*(x4-x3) == (y4-y3)*(x2-x1))
    -Two circles are intersect if(the distance between the centers <= (r1 + r2))  ,r1,r2 are the radiuses of the circles

    -floor(2.7) = 2 , floor(2.3)= 2  ,-floor(n/a) = n/a
    -ceil(2.3) = 3 , ceil(2.7) = 3   ,-ceil(n/a) = (n+a-1)/a
    -round(2.3) = 2 , round(2.5) = 3
    -trunc(2.999) = 2 ->(deletes the decimal points)
    -abs(2) = abs(-2) = 2

--------------------------------------------------------------------------------------------------

    - a * b = x , then a, b are divisors for x
    - T-Prime is a number x has only 3 divisors then it should has devisors (1, x, sqrt(x))
    thats mean the sqrt(x) should be prime number
    - number of multipliers for x in range from l to r = (floor(r/x)-ceil(l/x) + 1)
    - number of trailing zero for x = number of multipliers for 5 in x
      = sum((x/(5^i))) for all i (i=1,2,......,(num of digits of x))

    -(If there is quiries if yoy can do pre_compute for the required ,then do it.)

    - If you have (a prime factors(pf) of any number(x) and the frequancy(f) for each prime factor):
        -> then you can get the number of divisors for this number(x)
        -> number if divisors = ((f1 + 1) * (f2 + 1) * ....... * (fn + 1))
        -> (n) the number of distincit prime factor, (f) the frequancy for each prime factor
    - For even divisors ((f[2] * (f1 + 1) * ....... * (fn + 1)))



*/
// ===========================================================================//
// ===========================================================================//

//--------------------------------(Big-Factorials)----------------------------//

static const int MAXN = 200000; // big enough for n + S shifts

long long fact[MAXN + 1], invFact[MAXN + 1];

// (1) Fast exponentiation to compute a^p % MOD
long long modexp(long long a, long long p)
{
    long long res = 1;
    while (p > 0)
    {
        if (p & 1)
            res = (res * a) % MOD;
        a = (a * a) % MOD;
        p >>= 1;
    }
    return res;
}

// (2) Precompute factorials and inverse factorials
void initFactorials()
{
    fact[0] = 1;
    for (int i = 1; i <= MAXN; i++)
    {
        fact[i] = (fact[i - 1] * i) % MOD;
    }
    invFact[MAXN] = modexp(fact[MAXN], MOD - 2);
    for (int i = MAXN; i >= 1; i--)
    {
        invFact[i - 1] = (invFact[i] * i) % MOD;
    }
}

// (3) Binomial coefficient nCr % MOD
long long nCr(int n, int r)
{
    if (r < 0 || r > n)
        return 0;
    return ((fact[n] * invFact[r]) % MOD * invFact[n - r]) % MOD;
}

// (4) Inclusion-Exclusion formula for 0 ≤ xi ≤ U, sum = S
long long countBounded(int n, int S, int U)
{
    // If S out of [0, nU], no solutions
    if (S < 0 || S > 1LL * n * U)
        return 0;
    int rmax = S / (U + 1);
    long long ans = 0;
    for (int r = 0; r <= rmax; r++)
    {
        // Choose which r variables exceed U
        long long choose = nCr(n, r);
        int rem = S - r * (U + 1);
        // Distribute rem among n without bound:
        long long ways = nCr(n + rem - 1, rem);
        long long term = (choose * ways) % MOD;
        if (r & 1)
        {
            term = (MOD - term) % MOD; // subtract if r is odd
        }
        ans = (ans + term) % MOD;
    }
    return ans;
}