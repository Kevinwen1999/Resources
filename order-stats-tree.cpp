/*
Order-statistics Tree
Basic idea: sort all values in advance.
When updating, insert a value to sorted position
When querying, check for value under accepted order range
All operations are O(logN), similar to segment tree
Following is code for this problem: https://dmoj.ca/problem/coci06c4p6
*/
#include <bits/stdc++.h>
#pragma GCC optimize ("Ofast")
#define INF 0x3f3f3f3f
#define MAXN 200010
#define pii pair <int, int>
#define ld long double
#define ll long long
using namespace std;
int N, n;
struct stu {
    int a, b;
    int idx, sidx;
} as[MAXN];
bool cmpp(stu &a, stu &b) {
    if (a.b == b.b) return a.a < b.a;
    return a.b < b.b;
}
bool cmpi(stu &a, stu &b) {
    return a.idx < b.idx;
}
pii aq[MAXN];
int seg[MAXN * 4];
int pushup(int stidx) {
    int l = stidx * 2, r = l + 1;
    int p1 = seg[l], p2 = seg[r];
    if (p1 == -1) return p2;
    else if (p2 == -1) return p1;
    else {
        if (as[p1].a > as[p2].a) return p1;
        else return p2;
    }
}
void update(int stidx, int L, int R, int tg) {
    if (L == R) {
        seg[stidx] = tg;
        return;
    }
    int l = stidx * 2, r = l + 1, mid = (L + R) / 2;
    if (mid >= as[tg].sidx) update(l, L, mid, tg);
    else update(r, mid + 1, R, tg);
    seg[stidx] = pushup(stidx);
}
int query(int stidx, int L, int R, int tg) {
    if (R <= as[tg].sidx) return -1;
    if (seg[stidx] == -1) return -1;
    if (as[seg[stidx]].a < as[tg].a) return -1;
    if (L == R) return seg[stidx];
    int l = stidx * 2, r = l + 1, mid = (L + R) / 2;
    int ta = query(l, L, mid, tg);
    if (~ta) return ta;
    return query(r, mid + 1, R, tg);
}
int main() {
    scanf("%d", &N);
    for (int i = 0; i < N; i++) {
        char op; scanf(" %c", &op);
        if (op == 'D') {
            int a, b; scanf("%d %d", &a, &b); a--, b--;
            as[n] = (stu){a, b, n, n};
            aq[i] = {0, n++};
        } else {
            int b; scanf("%d", &b); b--;
            aq[i] = {1, b};
        }
    }
    sort(as, as + n, cmpp);
    for (int i = 0; i < n; i++) as[i].sidx = i;
    sort(as, as + n, cmpi); 
    memset(seg, -1, sizeof seg);
    for (int i = 0; i < N; i++) {
        if (aq[i].first) {
            int ta = query(1, 0, n - 1, aq[i].second);
            if (~ta) printf("%d\n", ta + 1);
            else printf("NE\n");
        } else {
            update(1, 0, n - 1, aq[i].second);
        }
    }
}
