int node[4*MAXN], l[2*MAXN], E[2*MAXN], H[MAXN], idx;
void dfs(int cur, int dep, int pa)
{
    H[cur] = idx; // position of current node in E array
    E[idx] = cur; // sequence of visiting 
    l[idx++] = dep; // depth of each node visit
    for (int i = 0; i < adj[cur].size(); i++)
    {
        int v = adj[cur][i];
        if (v==pa) continue;
        dfs(v, dep+1, cur);
        E[idx] = cur;
        l[idx++] = dep;
    }
}
//run RMQ on l array

//DP METHOD, used in https://dmoj.ca/problem/dmopc15c7p5
void process()
{
    memset(pa,-1,sizeof pa);
    for (int i = 0, a, b; i < N; i++)
    {
        cin>>a;
        for (int j = 0; j < a; j++)
        {
            cin>>b;
            adj[i].push_back(--b);
            pa[0][b] = i;
        }
    }
    for (int i = 1; i < LOG; i++)
        for (int j = 0; j < N; j++)
            if (pa[i-1][j]!=-1)
                pa[i][j] = pa[i-1][pa[i-1][j]];
}
int LCA(int u, int v)
{
    if (depth[u]<depth[v]) swap(u,v);
    for (int i  = LOG - 1; i >=0; i--)
        if (pa[i][u]!=-1 && depth[pa[i][u]] >= depth[v])
            u = pa[i][u];
    if (u==v) return v;
    for (int i = LOG - 1; i >= 0; i--)
    {
        if (pa[i][v]!=-1&&pa[i][u]!=-1&&pa[i][u]!=pa[i][v])
            u = pa[i][u], v = pa[i][v];
    }
    return pa[0][u];
}
