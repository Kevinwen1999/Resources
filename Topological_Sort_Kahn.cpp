#include <bits/stdc++.h>
#define MAXN 110
using namespace std;
int N;
int deg[MAXN], visited[MAXN], adj[MAXN][MAXN];
vector <int> L;
queue <int> S;
bool topo() {
    while(true) {
        bool OK = true;
        for (int i = 0; i < N; i++)
            if (!visited[i])
                OK = false;
        if (OK) return OK;

        for (int i = 0; i < N; i++) {
            if (!visited[i] && deg[i] == 0) {
                S.push(i);
                break; // if lexicographically
            }
        }

        if (S.empty()) return false;

        while(!S.empty()) {
            int cur = S.front();
            S.pop();
            visited[cur] = true;
            L.push_back(cur);
            for (int i = 0; i < N; i++) {
                if (adj[cur][i]) {
                    adj[cur][i] = 0;
                    deg[i]--;
                    if (deg[i] < 0) return false;
                }
            }
        }
    }
    return true;
}

int main() {
    cin>>N;
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            cin>>adj[i][j];
            if (adj[i][j]) deg[j]++;
        }
    }
    if (topo())
        for (int i : L)
            cout<<i+1<<"\n";
    else
        cout<<"impossible\n";
}
