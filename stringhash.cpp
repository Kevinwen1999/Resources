// O(NlogN) version
#include <bits/stdc++.h>
#define ll long long
#define MOD 1000000007
#define MAXN 5005
#define prm 307
using namespace std;
ll x, y, d;
ll f1[MAXN], f2[MAXN];
ll prex[MAXN];
ll e[MAXN];
int N;
void extendedeuclid(ll a, ll b, ll &x, ll &y, ll &d) {
    if (!b) {x = 1; y = 0; d = a; return;}
    extendedeuclid(b, a % b, x, y, d);
    ll x1 = y;
    ll y1 = x - (a/b)*y;
    x = x1;
    y = y1;
}
void precalc_exponents() {
    prex[0] = 1;
    extendedeuclid(MOD, 1, x, y, d);
    e[0] = y;
    for (int i = 1; i < MAXN; i++) {
        prex[i] = (prex[i - 1] * prm) % MOD;
        extendedeuclid(MOD, prex[i] % MOD, x, y, d);
        e[i] = y;
    }
}
void hash_string(string& in, ll F[], int p) {
    for (int i = 0; i < in.size(); i++) {
        F[i] = (((in[i] - 'a' + 1) % MOD) * (prex[i] % MOD)) % MOD;
        if (i) F[i] = (F[i] + F[i - 1]) % MOD;
    }
}
ll query_hash(ll F[], int p, int i, int j) {
    ll val = F[j] - (i ? F[i - 1] : 0);
    val %= MOD;
    y = e[i];
//    cout<<"MOD inv is "<<y<<"\n";
    y %= MOD;
    val = (val * y) % MOD;
    return (val + MOD) % MOD;
}
