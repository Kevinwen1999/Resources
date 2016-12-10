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
