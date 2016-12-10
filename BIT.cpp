#include <bits/stdc++.h>
using namespace std;
const int MAXN = 100001;
//1D:
int bit[MAXN];
void update(int x, int v)
{
    for (;x < MAXN; x += (x & -x))
        bit[x]+=v;
}
int query(int a)
{
    int sum  = 0;
    for (; a > 0; a-=(a & -a))
        sum+=bit[a];
    return sum;
}
// 2D:
int bit[MAXN][MAXN];
void update(int x, int y, int v)
{
    for (; x < MAXN; x+=(x & -x))
    {
        for (int y1 = y; y1 < MAXN; y1 += (y1 & -y1))
            bit[x][y1] += v;
    }
}
int query(int x, int y)
{
    int sum = 0;
    for (; x > 0; x-=(x & -x))
    {
        for (int y1 = y; y1 > 0; y1 -= (y1 & -y1))
            sum += bit[x][y1];
    }
    return sum;
}
//(range x1, y1, x2, y2) = query(x2,y2) - query(x2,y1-1) - query(x1-1, y2) + query(x1-1, y1-1)
