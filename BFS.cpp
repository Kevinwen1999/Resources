
int dist[MAXN], pa[MAXN];
void bfs(int st, int ed)
{
    memset(dist, 63, sizeof dist);
    memset(pa,-1,sizeof pa);
    queue <int> buff;
    buff.push(st);
    dist[st] = 0;
    while (!buff.empty())
    {
        int cur = buff.front();
        buff.pop();
        if (cur == ed) break;
        for (int i = 0; i < (int)adj[cur].size(); i++)
        {
            int v = adj[cur][i];
            if (dist[cur] + 1 < dist[v])
            {
                dist[v] = dist[cur] + 1;
                pa[v] = cur;
                buff.push(v);
            }
        }
    }
}
void print(int cur)
{
    if (cur == -1) return;
    print(pa[cur]);
    cout<<N[cur];
}
