int ch[MAXNODE][SIGMA];
int val[MAXNODE];
int sz;
void init_trie() {
    sz = 1;
    memset(ch, 0, sizeof ch);
    memset(val, 0, sizeof val);
}
int getidx(char c) {
    return c - 'a';
}
void add_word(string &s, int v) {
    int u = 0;
    for (int i = 0; i < s.size(); i++) {
        int cc = getidx(s[i]);
        if (!ch[u][cc]) {
            ch[u][cc] = sz++;
        }
        u = ch[u][cc];
    }
    val[u] = v;
}
