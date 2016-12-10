#include <iostream>
#include <vector>
#include <utility>
#include <algorithm>

using namespace std;
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
int main()
{
    vector < pair <int, pair <int,int> > > EdgeList;
    int E, V;
    scanf("%d%d",&E,&V);
    int mst_cost = 0;
    for (int i = 0 ; i < E ; i++)
    {
        int u,v,w;
        scanf("%d %d %d", &u,&v,&w);
        EdgeList.push_back(make_pair(w,make_pair(u,v)));
    }
    sort (EdgeList.begin(),EdgeList.end());
    UnionFind UF(V);
    for (int i = 0 ; i < E; i++)
    {
        pair <int, pair <int, int > > frontt = EdgeList[i];
        if (!UF.isSameSet(frontt.second.first, frontt.second.second))
        {
            mst_cost+=frontt.first;
            UF.unionSet(frontt.second.first, frontt.second.second);
        }
    }
    printf("MST cost = %d (Kruskals)\n", mst_cost);
    return 0;
}
