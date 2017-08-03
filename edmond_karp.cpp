#include <bits/stdc++.h>
#define MAXN 1000
#define INF 0x3f3f3f3f
int s = 0, t, f, mf;
int dist[MAXN], parent[MAXN];
int res[MAXN][MAXN];
queue <int> buff;

void augment(int cur, int minedge) {
    if (cur == s) {
        f = minedge;
        return;
    }
    else if (parent[cur] != -1) {
        augment(parent[cur], min (minedge, res[parent[cur]][cur]));
        res[parent[cur]][cur] -= f;
        res[cur][parent[cur]] += f;
    }
}
void edmond_karp() {

    while(1) {
        f = 0;
        memset(dist, 0x3f, sizeof dist);
        memset(parent, -1, sizeof parent);
        dist[s] = 0;
        parent[s] = -1;
        while(!buff.empty())
            buff.pop();
        buff.push(s);
        while(!buff.empty()) {
            int cur = buff.front();
            buff.pop();
            if (cur == t)
                break;
            for (int nex = 0; nex <= t; nex++) {
                if (dist[nex] == INF && res[cur][nex] > 0) {
                    dist[nex] = dist[cur] + 1;
                    buff.push(nex);
                    parent[nex] = cur;
                }
            }
        }
        augment(t, INF);
        if (f == 0)
            break;
        mf += f;
    }
}

int main() {

}
