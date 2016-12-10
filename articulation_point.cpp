#include <iostream>
#include <cstring>
#include <vector>
#include <utility>
#include <algorithm>
#define UNVISITED 0
using namespace std;

vector <int> adjlist[100010];
int a, b, dfsnum[100010], dfslow[100010], dfsparent[100010],dfsnumcnt,dfsroot,rootchild,artitotal;
bool isarti[100010];
int V,E;
void arti(int u)
{
    dfslow[u] = dfsnum[u] = ++dfsnumcnt;
    for (int i = 0 ; i < (int)adjlist[u].size(); i++)
    {
        int v = adjlist[u][i];
        if (dfsnum[v]==UNVISITED)
        {
            dfsparent[v] = u;
            if (u==dfsroot) rootchild++;
            arti(v);
            if (dfslow[v]>=dfsnum[u])
                isarti[u] = true;
            dfslow[u] = min(dfslow[u], dfslow[v]);
        }
        else if (v!=dfsparent[u])
            dfslow[u] = min(dfslow[u], dfsnum[v]);
    }
}
int main()
{
    ios::sync_with_stdio(0); cin.tie(0);
    cin>>V>>E;
    for (int i = 0 ; i < E; i++)
    {
        cin>>a>>b;
        adjlist[a].push_back(b);
        adjlist[b].push_back(a);
    }
    for (int i = 1 ; i <= V; i++)
    {
        if (dfsnum[i]==UNVISITED)
        {
            dfsroot = i; rootchild = 0;
            arti(i);
            isarti[dfsroot] = (rootchild>1);
        }
    }
    for (int i = 1 ; i <= V; i++)
    {
        if (isarti[i])
            artitotal++;
    }
    cout<<artitotal<<endl;
    for (int i = 1 ; i <= V; i++)
    {
        if (isarti[i])
            cout<<i<<endl;
    }
    /*cout<<endl;
    for (int i = 1 ; i <= V; i++)
    {
        cout<<dfsnum[i]<<" "<<dfslow[i]<<endl;
    }*/
}
