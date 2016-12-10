#include <iostream>
#include <vector>
class UnionFind
{
    private:
        vector < int > p;
        vector <int> rankx;
    public:
        UnionFind(int N) { rankx.assign(N, 0); p.assign(N, 0); for (int i = 0; i < N; i++) p[i] = i; }
        int findSet(int i) { return (p[i] == i) ? i : (p[i] = findSet(p[i])); }
        bool isSameSet(int i, int j) { return findSet(i) == findSet(j); }
        void unionSet(int i, int j)
        {
            if (!isSameSet(i,j))
            {
                int x = findSet(i), y = findSet(j);
                if (rankx[x] > rankx[y])
                    p[y] = x;
                else
                {
                    p[x] = y;
                    if (rankx[x] == rankx[y])
                        rankx[y]++;
                }
            }
        }
};
//a better non-oop version
int p[MAXN], rnk[MAXN];
void init(int N)
{
    for (int i = 0; i <= N; i++)
        p[i] = i, rnk[i] = 1;
}
int findp(int x)
{
    return p[x] == x ? x : (p[x] = findp(p[x]));
}
bool sameset(int x, int y)
{
    return findp(x) == findp(y);
}
void mergeset(int x, int y)
{
    if (!sameset(x, y))
    {
        x = findp(x), y = findp(y); // EXTREMELY IMPORTANT !!!!!!!!!
        if (rnk[x] > rnk[y])
            rnk[x] += rnk[y], p[y] = x;
        else
            rnk[y] += rnk[x], p[x] = y;
    }
}
