#include <bits/stdc++.h>
#define MAXN 1000
using namespace std;

int N, M;
int match[MAXN], bpg[MAXN][MAXN];
bool visited[MAXN];
bool bpm(int u) {
    for (int v = 1; v <= M; v++) {
        // if edge exist from u to v and v is not used
        if (bpg[u][v] && !visited[v]) {
            visited[v] = true;
            // if v is not already matched or
            // the original partner of v can find a new pair
            if (match[v] == -1 || bpm(match[v])) {
                match[v] = u;
                return true;
            }
        }
    }
    return false;
}
int maxbpm() {
    memset(match, -1, sizeof match);
    int cnt = 0;
    for (int u = 1; u <= N; u++) {
        memset(visited, 0, sizeof visited);
        if (bpm(u))
            cnt++;
    }
    return cnt;
}

int main() {

}
