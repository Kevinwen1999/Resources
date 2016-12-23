#include <bitset>
#include <iostream>
#include <vector>
using namespace std;

typedef long long ll;
typedef vector <int> vi;

ll sieve_size;
bitset <1000010> bs;
vi primes;
// Sieve of E
void sieve(ll upper)
{
    sieve_size = upper;
    bs.set();
    for (ll i = 2; i <= sieve_size; i++)
        if (bs[i])
        {
            for (ll j = i*i; j < sieve_size; j+=i)
                bs[j] = 0;
            primes.push_back((int)i);
        }
}
void segmented_sieve(ll upper)
{
    ll limit = floor(sqrt(upper)) + 1;
    sieve(limit);
    ll low = limit, high = 2*limit;
    while (low < upper)
    {
        bs.set();
        ll lomin;
        for (int i = 0; i < primes.size(); i++)
        {
            lomin = floor(low/primes[i])*primes[i];
            while (lomin < low)
                lomin += primes[i];
            for (int j = lomin; j <high; j+=primes[i])
                bs[j-low] = false;
        }
        for (int i = low; i < high; i++)
        {
            if (bs[i-low])
            {
                //if (i <= N) sp1++;
                //if (i <= M) sp2++;
            }
        }
        low = low + limit;
        high = min(upper, high + limit);
    }
}

bool isprime(ll N)
{
    if (N <= sieve_size) return bs[N];
    for (int i = 0; i < (int)primes.size(); i++)
    {
        if (N % primes[i]==0)return false;
    }
    return true;
}
// GCD and LCM
int gcd(int a, int b) { return b == 0 ? a : gcd(b, a % b); }
int lcm(int a, int b) { return a * (b / gcd(a, b)); }
// Prime Factors
vi primefactors(ll N)
{
    vi factors;
    ll idx = 0, PF = primes[idx]; // sieve first
    while (PF * PF <= N) //stop at sqrt(N)
    {
        while (N % PF ==0)
        {
            N/= PF;
            factors.push_back(PF);
        }
        PF = primes[++idx];
    }
    if (N != 1) factors.push_back(N);
    return factors;
}
//Modified Sieve
/*
memset(nDiffPM, 0, sizeof nDiffPM);
for (int i = 0; i < MAXN; i++)
    if (nDiffPM[i]==0)
        for (int j = i; j < MAXN; j+=i)
            nDiffPM[j]++;
*/
//Extended Euclid
//if (d%c != 0) no solution
//x = x0 + (b/d)n, y = y0 - (a/d)n
int x, y, d;
void extendedeuclid(int a, int b, int &x, int &y, int &d)
{
    if (b==0) {x = 1; y = 0; d = a; return;}
    extendedeuclid(b,a%b, x, y, d);
    int x1 = y;
    int y1 = x - (a/b)*y;
    x = x1;
    y = y1;
}
//Euler Phi
//Single number version:
int eulerphi(int n)
{
    int m = (int)sqrt(n+0.5);
    int ans = n;
    for (int i = 2; i <= m; i++)
    {
        if (n%i==0)
        {
            ans = ans / i * (i-1);
            while (n % i == 0) n /= i;
        }
    }
    if (n > 1) ans = ans / n * (n-1);
    return ans;
}
//sieve-ish table version:
void phitable(int n, int *phi)
{
    for (int i = 2; i <= n; i++)
        phi[i] = 0;
    phi[1] = 1;
    for (int i = 2; i <= n; i++)
    {
        if (!phi[i])
        {
            for (int j = i; j <= n; j += i)
            {
                if (!phi[j]) phi[j] = j;
                phi[j] = phi[j] / i * (i-1);
            }
        }
    }
}

//modular arithmetic
int mul_mod(int a, int b, int n)
{
    a %= n; b %= n;
    return (int)((long long)a*b%n);
}
//big int n % m
/*
scanf("%s%d", n, &m);
int len = strlen(n);
int ans = 0;
for (int i = 0; i < len; i++)
	ans = (int)(((long long)ans*10+n[i]-'0')%m);
printf("%d\n", ans);
*/
unsigned long long pow_mod(unsigned long long a, unsigned long long b, unsigned long long n)
{
    if (b == 0) return 1;
    unsigned long long ans = pow_mod(a, b/2, n);
    ans = ans * ans % n;
    if (b%2 == 1) ans = ans * a % n;
    return ans;
}
bool Miller (long long p, int ite)
{
    if (p<2)
        return false;
    if (p!=2 && p%2==0)
        return false;
    long long s = p-1;
    while (s%2==0)
        s/=2;
    long long a, tmp, mod;
    for (int i = 0; i < ite; i++)
    {
        a = rand()%(p-1) + 1; tmp = s;
        mod = pow_mod(a,tmp,p);
        while (tmp!=p-1 && mod!=1 && mod!= p-1)
        {
            mod = mul_mod(mod, mod, p);
            tmp*=2;
        }
        if (mod!=p-1 && tmp%2==0)
            return false;
    }
    return true;
}
// a faster Miller-Rabin, taken from https://github.com/jeffrey-xiao/Competitive-Programming/blob/master/src/codebook/math/Miller_Rabin.cpp
typedef unsigned long long ULL;

ULL mulmod (ULL a, ULL b, ULL c)
{
    ULL x = 0, y = a % c;
    for (; b > 0; b >>= 1)
    {
        if (b & 1) x = (x + y) % c;
        y = (y << 1) % c;
    }
    return x % c;
}

ULL powmod (ULL a, ULL b, ULL c)
{
    ULL x = 1, y = a;
    for (; b > 0; b >>= 1)
    {
        if (b & 1) x = mulmod(x, y, c);
        y = mulmod(y, y, c);
    }
    return x % c;
}

inline ULL rand64U ()
{
    return ((ULL)rand() << 48) | ((ULL)rand() << 32) | ((ULL)rand() << 16) | ((ULL)rand());
}

bool isPrime (long long N, int k = 5)
{
    if (N < 2 || (N != 2 && !(N & 1)))
        return 0;

    ULL s = N - 1, p = N - 1, x, R;

    while (!(s & 1))
        s >>= 1;

    for (int i = 0; i <= k-1; i++)
    {
        R = powmod(rand64U() % p + 1, s, N);
            for (x = s; x != p && R != 1 && R != p; x <<= 1)
                R = mulmod(R, R, N);
            if (R != p && !(x & 1))
                return 0;
    }
    return 1;
}
int main()
{
    sieve(1000000);
    printf("%d\n", isprime(23));
    printf("%d\n", isprime(33));
    vi r = primefactors(999);
    for (vi::iterator i = r.begin(); i != r.end(); i++) printf("> %d\n", *i);
}
