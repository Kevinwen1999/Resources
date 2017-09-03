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
// Left Child Right Siblings Version
int sz = 0, root;
struct TrieNode {
    char chr;
    int lchild; // pointing to first child
    int rchild; // pointing to adjacent siblings
};
TrieNode trie[MAXNODE];
int NewNode(char c) {
    trie[sz].lchild = trie[sz].rchild = -1;
    trie[sz++].chr = c;
    return sz - 1;
}
void init_trie() {
    sz = 0;
    root = NewNode(0);
}
void TrieInsert(char *s) {
    int slen = strlen(s);
    int cur = trie[root].lchild; // current node
    int par = root; // parent of cur
    bool same = true;
    for (int i = 0; i <= slen; i++) {
        if (cur == -1) { // current node for s[i] DNE
            trie[par].lchild = cur = NewNode(s[i]);
            // modify value associated with cur here
        } else {
            // modify value associated with cur here
            while (trie[cur].rchild != -1 && trie[cur].chr != s[i]) // keep going right to siblings
                cur = trie[cur].rchild;
            if (trie[cur].chr != s[i]) { // if corresponding node is not found
                trie[cur].rchild = NewNode(s[i]);
                cur = trie[cur].rchild;
            }
        }
        par = cur;
        cur = trie[par].lchild; // keep going down
    }
}
