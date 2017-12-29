vector <int> adj[MAXN], cadj[MAXN];
bool visited[MAXN], marked[MAXN];
int subsz[MAXN];
int ntotal;
void calc_sz(int src, int pa) {
    ntotal ++;
    subsz[src] = 1;
    for (int i : adj[src]) {
        if (i == pa || marked[i]) continue;
        calc_sz(i, src);
        subsz[src] += subsz[i];
    }
}
int findct(int src, int pa) {
    bool OK = true;
    int hvc = -1;
    for (int i : adj[src]) {
        if (i == pa || marked[i]) continue;
        if (subsz[i] > ntotal / 2) OK = false;
        if (hvc == -1 || subsz[hvc] < subsz[i])
            hvc = i;
    }
    if (OK && ntotal - subsz[src] <= ntotal / 2)
        return src;
    else
        return findct(hvc, src);
}
int ctdecomp(int src) {
    ntotal = 0;
    calc_sz(src, -1);
    int ct = findct(src, -1);
    marked[ct] = true;
    // dfs here
    for (int i : adj[ct]) {
        if (!marked[i]) {
            int cst = ctdecomp(i);
            cadj[ct].push_back(cst);
            cadj[cst].push_back(ct);
        }
    }
    return ct;
}
