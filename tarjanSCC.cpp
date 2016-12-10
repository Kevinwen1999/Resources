#define UNVISITED 0
vector <int> buff; // for SCC
vector <int> adj[MAXN];
int dfs_num[MAXN], dfs_low[MAXN];
bool in_stack[MAXN];
int dfsnumcount;
void SCC(int cur)
{
    dfs_num[cur] = dfs_low[cur] = ++dfsnumcount;
    buff.push_back(cur); // push onto SCC stack
    in_stack[cur] = true;
    for (int i = 0; i < adj[cur].size(); i++)
    {
        int v = adj[cur][i];
        if (dfs_num[v] == UNVISITED)
            SCC(v);
        if (in_stack[v]) // condition for update
            dfs_low[cur] = min(dfs_low[cur], dfs_low[v]);
    }
    if (dfs_num[cur] == dfs_low[cur]) // if cur is the start of a SCC
    {
        while (1)
        {
            int v = buff.back(); buff.pop_back(); in_stack[v] = false;
            // do sth here
            if (v == cur) break;
        }
    }
}
