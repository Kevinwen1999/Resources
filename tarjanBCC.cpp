#include <bits/stdc++.h>
#define MAXN 1010
using namespace std;

struct Edge {
    int u, v;
};

int dfs_num[MAXN], iscut[MAXN], bccno[MAXN], dfs_clock, bcc_cnt;
vector <int> adj[MAXN], bcc[MAXN];
stack <Edge> stk;

int dfs(int u, int pa) {
    int lowu = dfs_num[u] = ++dfs_clock;
    int total_child = 0;
    for (int v : adj[u]) {
        Edge ce = (Edge){u,v};
        if (!dfs_num[v]) {
            stk.push(ce);
            total_child++;
            int lowv = dfs(v, u);
            lowu = min(lowv, lowu);
            if (lowv >= lowu) {
                iscut[u] = true;
                bcc_cnt++;
                bcc[bcc_cnt].clear();
                while(1) {
                    Edge x = stk.top(); stk.pop();
                    if (bccno[x.u] != bcc_cnt) {
                        bcc[bcc_cnt].push_back(x.u);
                        bccno[x.u] = bcc_cnt;
                    }
                    if (bccno[x.v] != bcc_cnt) {
                        bcc[bcc_cnt].push_back(x.v);
                        bccno[x.v] = bcc_cnt;
                    }
                    if (x.u == u && x.v == v)
                        break;
                }
            }
        }
        else if (dfs_num[v] < dfs_num[u] && v != pa) {
            stk.push(ce);
            lowu = min(lowu, dfs_num[v]);
        }
    }
    if (pa == -1 && total_child == 1) iscut[u] = false;
    return lowu;
}

void BCC(int V) {
    memset(dfs_num, 0, sizeof dfs_num);
    memset(iscut, 0, sizeof iscut);
    memset(bccno, 0, sizeof bccno);
    dfs_clock = bcc_cnt = 0;
    for (int i = 0; i < V; i++) {
        if (!dfs_num[i]) {
            dfs(i,-1);
        }
    }
}
